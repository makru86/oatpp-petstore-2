#include "auth/ApiKeyAuth.hpp"
#include "auth/OAuth2.hpp"
#include "oatpp/web/server/interceptor/RequestInterceptor.hpp"

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
    // Route property is true if apiKey is required.
    bool apiKey = true;

    // In oatpp the most specific routes should come first.
    // The order matters:
    //    GET /pet/findByStatus
    //    GET /pet/{petId}
    //    GET /*            <- this should be the last one

    m_authEndpoints.route("GET", "/pet/findByStatus", not apiKey);
    m_authEndpoints.route("GET", "/pet/findByTags", not apiKey);
    m_authEndpoints.route("GET", "/pet/{petId}", apiKey);
    m_authEndpoints.route("GET", "/store/inventory", apiKey);
    m_authEndpoints.route("GET", "/store/order/{orderId}", not apiKey);
    m_authEndpoints.route("GET", "/user/login", not apiKey);
    m_authEndpoints.route("GET", "/user/logout", apiKey);
    m_authEndpoints.route("GET", "/user/{username}", not apiKey);

    m_authEndpoints.route("POST", "/pet/{petId}/uploadImage", not apiKey);
    m_authEndpoints.route("POST", "/pet/{petId}", not apiKey);
    m_authEndpoints.route("POST", "/pet", not apiKey);
    m_authEndpoints.route("POST", "/store/order", not apiKey);
    m_authEndpoints.route("POST", "/user/createWithArray", apiKey);
    m_authEndpoints.route("POST", "/user/createWithList", apiKey);
    m_authEndpoints.route("POST", "/user", apiKey);

    m_authEndpoints.route("PUT", "/pet", not apiKey);
    m_authEndpoints.route("PUT", "/user/{username}", apiKey);

    m_authEndpoints.route("DELETE", "/pet/{petId}", not apiKey);
    m_authEndpoints.route("DELETE", "/store/order/{orderId}", not apiKey);
    m_authEndpoints.route("DELETE", "/user/{username}", apiKey);
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
class OAuth2Interceptor : public oatpp::web::server::interceptor::RequestInterceptor
{
private:
  static constexpr const char* TAG = "OAuth2Interceptor";
  std::shared_ptr<OAuth2Handler> m_oauth2Handler;
  oatpp::web::server::HttpRouterTemplate<bool> m_authEndpoints;

public:
  OAuth2Interceptor(std::shared_ptr<OAuth2Handler> authHandler) : m_oauth2Handler(authHandler)
  {
    //    // Skip endpoints that does not require oauth2 authorization.
    //    m_authEndpoints.route("POST", "/store/order", false);
    //    m_authEndpoints.route("GET", "/store/order/{orderId}", false);
    //    m_authEndpoints.route("DELETE", "/store/order/{orderId}", false);
    //    m_authEndpoints.route("GET", "/user/login", false);
    //    m_authEndpoints.route("GET", "/user/{username}", false);
    //
    //    m_authEndpoints.route("GET", "/pet/{petId}", false);
    //    m_authEndpoints.route("DELETE", "/pet/{petId}", false);
    //    m_authEndpoints.route("GET", "/store/inventory", false);
    //    m_authEndpoints.route("POST", "/user", false);
    //    m_authEndpoints.route("POST", "/user/createWithArray", false);
    //    m_authEndpoints.route("POST", "/user/createWithList", false);
    //    m_authEndpoints.route("GET", "/user/logout", false);
    //    m_authEndpoints.route("PUT", "/user/{username}", false);
    //    m_authEndpoints.route("DELETE", "/user/{username}", false);

    // Set endpoints that require oauth2 authorization.
    m_authEndpoints.route("POST", "/pet", true);
    m_authEndpoints.route("PUT", "/pet", true);
    m_authEndpoints.route("GET", "/pet/findByStatus", true);
    m_authEndpoints.route("GET", "/pet/findByTags", true);
    m_authEndpoints.route("POST", "/pet/{petId}", true);
    m_authEndpoints.route("DELETE", "/pet/{petId}", true);
    m_authEndpoints.route("POST", "/pet/{petId}/uploadImage", true);

    // Set all other endpoints not require oauth2 authorization.
    m_authEndpoints.route("GET", "/*", false);
    m_authEndpoints.route("POST", "/*", false);
    m_authEndpoints.route("PUT", "/*", false);
    m_authEndpoints.route("DELETE", "/*", false);
    m_authEndpoints.route("PATCH", "/*", false);
    m_authEndpoints.route("OPTIONS", "/*", false);

    OATPP_LOGD(TAG, "petstore_auth endpoints:");
    m_authEndpoints.logRouterMappings();
  }

  std::shared_ptr<OutgoingResponse> intercept(
      const std::shared_ptr<IncomingRequest>& request) override
  {
    auto method = request->getStartingLine().method.toString();
    auto path = request->getStartingLine().path.toString();
    OATPP_LOGD(TAG, "endpoint: %s %s", method->c_str(), path->c_str());

    auto route = m_authEndpoints.getRoute(method, path);
    if (!route) {
      OATPP_LOGD(TAG, "authorization not required: no route");
      return nullptr;
    }
    if (!route.getEndpoint()) {
      OATPP_LOGD(TAG, "authorization not required: skip endpoint");
      return nullptr;
    }

    auto authHeader = request->getHeader("Authorization");
    auto oauth2Object =
        std::static_pointer_cast<OAuth2Object>(m_oauth2Handler->handleAuthorization(authHeader));
    if (!oauth2Object) {
      OATPP_LOGD(TAG, "authorization denied");
      throw oatpp::web::protocol::http::HttpError(oatpp::web::protocol::http::Status::CODE_401,
                                                  "Unauthorized", {});
    }

    request->putBundleData("userId", oauth2Object->userId);
    request->putBundleData("scopeReadPets", oauth2Object->scopeReadPets);
    request->putBundleData("scopeWritePets", oauth2Object->scopeWritePets);
    OATPP_LOGD(TAG, "authorization granted");
    return nullptr;  // Continue - token is valid.
  }
};
