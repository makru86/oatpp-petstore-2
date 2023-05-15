#pragma once

#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/web/server/HttpRouter.hpp"
#include "oatpp/web/server/handler/AuthorizationHandler.hpp"
#include "oatpp/web/server/interceptor/RequestInterceptor.hpp"

class OAuth2AuthObject : public oatpp::web::server::handler::BearerAuthorizationObject
{
public:
  explicit OAuth2AuthObject(const oatpp::String& pUserId) : userId(pUserId) {}
  oatpp::String userId;
};

class OAuth2AuthHandler : public oatpp::web::server::handler::AuthorizationHandler
{
private:
  static constexpr const char* TAG = "OAuth2AuthHandler";

public:
  /**
   * Constructor.
   * @param realm - realm. &id:oatpp::String;.
   */
  explicit OAuth2AuthHandler(const oatpp::String& realm) : BearerAuthorizationHandler("apiKey", realm) {}

  // FIXME move somewhere, like src/Common.hpp
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

    oatpp::String apiKeyUserId = "uid-admin";
    OATPP_LOGD(TAG, "allow access: %s", apiKeyUserId->c_str());
    return std::make_shared<OAuth2AuthObject>(apiKeyUserId);
  }
};

class OAuth2InHeaderInterceptor : public oatpp::web::server::interceptor::RequestInterceptor
{
private:
  static constexpr const char* TAG = "OAuth2InHeaderInterceptor";
  std::shared_ptr<OAuth2AuthHandler> m_apiKeyAuthHandler;
  oatpp::web::server::HttpRouterTemplate<bool> m_skipAuthEndpoints;
  const oatpp::String m_apiKeyHeaderName;

public:
  OAuth2InHeaderInterceptor(std::shared_ptr<OAuth2AuthHandler> authHandler,
                            const oatpp::String& apiKeyHeaderName)
    : m_apiKeyAuthHandler(authHandler), m_apiKeyHeaderName(apiKeyHeaderName)
  {
    //  By default all requests are intercepted.
    //  Skip-list of endpoints NOT requiring authentication:
    m_skipAuthEndpoints.route("POST", "/pet", false);
    m_skipAuthEndpoints.route("PUT", "/pet", false);
    m_skipAuthEndpoints.route("GET", "/pet/findByStatus", false);
    m_skipAuthEndpoints.route("GET", "/pet/findByTags", false);
    m_skipAuthEndpoints.route("POST", "/pet/{petId}", false);
    m_skipAuthEndpoints.route("POST", "/pet/{petId}/uploadImage", false);
    m_skipAuthEndpoints.route("POST", "/store/order", false);
    m_skipAuthEndpoints.route("GET", "/store/order/{orderId}", false);
    m_skipAuthEndpoints.route("DELETE", "/store/order/{orderId}", false);
    m_skipAuthEndpoints.route("GET", "/user/login", false);
    m_skipAuthEndpoints.route("GET", "/user/{username}", false);
  }

  std::shared_ptr<OutgoingResponse> intercept(
      const std::shared_ptr<IncomingRequest>& request) override
  {
    auto startingLine = request->getStartingLine();
    OATPP_LOGD(TAG, "endpoint: %s %s", startingLine.method.toString()->c_str(),
               startingLine.path.toString()->c_str());

    auto r = m_skipAuthEndpoints.getRoute(startingLine.method, startingLine.path);
    if (r && !r.getEndpoint()) {
      OATPP_LOGD(TAG, "authorization not required");
      return nullptr;
    }

    auto authHeader = request->getHeader(m_apiKeyHeaderName);
    auto authObject = std::static_pointer_cast<OAuth2AuthObject>(
        m_apiKeyAuthHandler->handleAuthorization(authHeader));
    if (!authObject) {
    OATPP_LOGD(TAG, "authorization denied");
    throw oatpp::web::protocol::http::HttpError(oatpp::web::protocol::http::Status::CODE_401,
                                                "Unauthorized", {});
    }

      OATPP_LOGD(TAG, "authorization granted: %s", authObject->userId->c_str());
      request->putBundleData("apiKeyUserId", authObject->userId);
      return nullptr;  // Continue - token is valid.
  }
};
