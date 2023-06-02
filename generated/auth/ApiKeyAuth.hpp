#pragma once

#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/web/server/HttpRouter.hpp"
#include "oatpp/web/server/handler/AuthorizationHandler.hpp"
#include "oatpp/web/server/interceptor/RequestInterceptor.hpp"

class ApiKeyAuthObject : public oatpp::web::server::handler::AuthorizationObject
{
public:
  explicit ApiKeyAuthObject(const oatpp::String& pUserId) : userId(pUserId) {}
  oatpp::String userId;
};

class ApiKeyAuthHandler : public oatpp::web::server::handler::AuthorizationHandler
{
private:
  static constexpr const char* TAG = "ApiKeyAuthHandler";

public:
  /**
   * Constructor.
   * @param realm - realm. &id:oatpp::String;.
   */
  explicit ApiKeyAuthHandler(const oatpp::String& realm) : AuthorizationHandler("apiKey", realm) {}

  // FIXME move somewhere, like Common.hpp
  oatpp::String protectByAsterisks(const oatpp::String& secret)
  {
    if (!secret) {
      return "null";
    }
    oatpp::String result("");
    for (auto i = 0; i != secret->size(); i++) {
      result = result + "*";
    }
    return result;
  }

  /**
   * Implement this method! Return nullptr if authorization should be denied.
   * @param authHeader - `Authorization` authHeader. &id:oatpp::String;.
   * @return - `std::shared_ptr` to &id:oatpp::web::server::handler::AuthorizationObject;.
   */
  std::shared_ptr<AuthorizationObject> handleAuthorization(const oatpp::String& authHeader) override
  {
    OATPP_LOGD(TAG, "authHeader: %s", protectByAsterisks(authHeader)->c_str())

    if (!authHeader) {
      OATPP_LOGD(TAG, "deny access: authorization not provided");
      return nullptr;
    }

    // TODO Add your implementation here.

    oatpp::String userId = "uid-admin";
    OATPP_LOGD(TAG, "allow access: %s", userId->c_str());
    return std::make_shared<ApiKeyAuthObject>(userId);
  }
};

class ApiKeyInterceptor : public oatpp::web::server::interceptor::RequestInterceptor
{
private:
  static constexpr const char* TAG = "ApiKeyInterceptor";
  std::shared_ptr<ApiKeyAuthHandler> m_apiKeyAuthHandler;
  oatpp::web::server::HttpRouterTemplate<bool> m_authEndpoints;
  const oatpp::String m_apiKeyHeaderName;

public:
  ApiKeyInterceptor(std::shared_ptr<ApiKeyAuthHandler> authHandler,
                    const oatpp::String& apiKeyHeaderName)
    : m_apiKeyAuthHandler(authHandler), m_apiKeyHeaderName(apiKeyHeaderName)
  {
    // Route property is true if apiKeyAuth is required.
    bool apiKeyAuth = true;

    // In oatpp the most specific routes should come first.
    // The order matters:
    //    GET /pet/findByStatus
    //    GET /pet/{petId}
    //    GET /*            <- this should be the last one

    m_authEndpoints.route("GET", "/pet/findByStatus", false);
    m_authEndpoints.route("GET", "/pet/findByTags", false);
    m_authEndpoints.route("GET", "/pet/{petId}", apiKeyAuth);
    m_authEndpoints.route("GET", "/store/inventory", apiKeyAuth);
    m_authEndpoints.route("GET", "/store/order/{orderId}", false);
    m_authEndpoints.route("GET", "/user/login", false);
    m_authEndpoints.route("GET", "/user/logout", apiKeyAuth);
    m_authEndpoints.route("GET", "/user/{username}", false);

    m_authEndpoints.route("POST", "/pet/{petId}/uploadImage", false);
    m_authEndpoints.route("POST", "/pet/{petId}", false);
    m_authEndpoints.route("POST", "/pet", false);
    m_authEndpoints.route("POST", "/store/order", false);
    m_authEndpoints.route("POST", "/user/createWithArray", apiKeyAuth);
    m_authEndpoints.route("POST", "/user/createWithList", apiKeyAuth);
    m_authEndpoints.route("POST", "/user", apiKeyAuth);

    m_authEndpoints.route("PUT", "/pet", false);
    m_authEndpoints.route("PUT", "/user/{username}", apiKeyAuth);

    m_authEndpoints.route("DELETE", "/pet/{petId}", false);
    m_authEndpoints.route("DELETE", "/store/order/{orderId}", false);
    m_authEndpoints.route("DELETE", "/user/{username}", apiKeyAuth);
  }

  std::shared_ptr<OutgoingResponse> intercept(
      const std::shared_ptr<IncomingRequest>& request) override
  {
    auto startingLine = request->getStartingLine();
    OATPP_LOGD(TAG, "endpoint: %s %s", startingLine.method.toString()->c_str(),
               startingLine.path.toString()->c_str());

    auto r = m_authEndpoints.getRoute(startingLine.method, startingLine.path);
    if (!r) {
      OATPP_LOGD(TAG, "authorization not required: route not found");
      return nullptr;
    }
    if (r && !r.getEndpoint()) {
      OATPP_LOGD(TAG, "authorization not required: skip endpoint");
      return nullptr;
    }

    auto authHeader = request->getHeader(m_apiKeyHeaderName);
    auto authObject = std::static_pointer_cast<ApiKeyAuthObject>(
        m_apiKeyAuthHandler->handleAuthorization(authHeader));
    if (!authObject) {
      OATPP_LOGD(TAG, "authorization denied");
      throw oatpp::web::protocol::http::HttpError(oatpp::web::protocol::http::Status::CODE_401,
                                                  "Unauthorized", {});
    }

    OATPP_LOGD(TAG, "authorization granted: %s", authObject->userId->c_str());
    request->putBundleData("userId", authObject->userId);
    return nullptr;  // Continue - token is valid.
  }
};
