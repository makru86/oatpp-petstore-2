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
    return std::make_shared<ApiKeyAuthObject>(apiKeyUserId);
  }
};

class ApiKeyInHeaderInterceptor : public oatpp::web::server::interceptor::RequestInterceptor
{
private:
  static constexpr const char* TAG = "ApiKeyInHeaderInterceptor";
  ApiKeyAuthHandler m_apiKeyAuthHandler;
  oatpp::web::server::HttpRouterTemplate<bool> m_authEndpoints;
  const oatpp::String m_apiKeyHeaderName;

public:
  ApiKeyInHeaderInterceptor(const oatpp::String& apiKeyHeaderName)
    : m_apiKeyAuthHandler("My realm"), m_apiKeyHeaderName(apiKeyHeaderName)
  {
    m_authEndpoints.route("GET", "/pet/{petId}", true);
    m_authEndpoints.route("GET", "/store/inventory", true);

    m_authEndpoints.route("GET", "*", false);
    m_authEndpoints.route("POST", "*", false);
    m_authEndpoints.route("PUT", "*", false);
    m_authEndpoints.route("DELETE", "*", false);
  }

  std::shared_ptr<OutgoingResponse> intercept(
      const std::shared_ptr<IncomingRequest>& request) override
  {
    auto startingLine = request->getStartingLine();
    OATPP_LOGD(TAG, "endpoint: %s %s", startingLine.method.toString()->c_str(),
               startingLine.path.toString()->c_str());

    auto r = m_authEndpoints.getRoute(startingLine.method, startingLine.path);
    if (r && !r.getEndpoint()) {
      OATPP_LOGD(TAG, "authorization not required");
      return nullptr;
    }

    auto authHeader = request->getHeader(m_apiKeyHeaderName);
    auto authObject = std::static_pointer_cast<ApiKeyAuthObject>(
        m_apiKeyAuthHandler.handleAuthorization(authHeader));
    if (authObject) {
      OATPP_LOGD(TAG, "authorization granted: %s", authObject->userId->c_str());
      request->putBundleData("apiKeyUserId", authObject->userId);
      return nullptr;  // Continue - token is valid.
    }

    OATPP_LOGD(TAG, "authorization denied");
    throw oatpp::web::protocol::http::HttpError(oatpp::web::protocol::http::Status::CODE_401,
                                                "Unauthorized", {});
  }
};
