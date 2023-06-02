#pragma once

#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/web/server/HttpRouter.hpp"
#include "oatpp/web/server/handler/AuthorizationHandler.hpp"
#include "oatpp/web/server/interceptor/RequestInterceptor.hpp"

struct OAuth2Object : oatpp::web::server::handler::AuthorizationObject {
  static constexpr const char* TAG = "OAuth2Object";

  explicit OAuth2Object(const oatpp::String& pUserId, bool scopeReadPets, bool scopeWritePets)
    : userId(pUserId), scopeReadPets(scopeReadPets), scopeWritePets(scopeWritePets)
  {
    OATPP_LOGD(TAG, "userId: %s: read:pets: %d write:pets: %d", userId->c_str(), scopeReadPets,
               scopeWritePets);
  }

  oatpp::String userId;
  oatpp::Boolean scopeReadPets;
  oatpp::Boolean scopeWritePets;
};

class OAuth2Handler : public oatpp::web::server::handler::BearerAuthorizationHandler
{
private:
  static constexpr const char* TAG = "OAuth2Handler";

public:
  /**
   * Constructor.
   * @param realm - realm. &id:oatpp::String;.
   */
  explicit OAuth2Handler(const oatpp::String& realm) : BearerAuthorizationHandler(realm) {}

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
   * @param token - `Authorization` token. &id:oatpp::String;.
   * @return - `std::shared_ptr` to &id:oatpp::web::server::handler::AuthorizationObject;.
   */
  std::shared_ptr<AuthorizationObject> authorize(const oatpp::String& token) override
  {
    OATPP_LOGD(TAG, "token: %s", protectByAsterisks(token)->c_str())

    if (!token) {
      OATPP_LOGD(TAG, "deny access: authorization not provided");
      return nullptr;
    }

    // TODO Add your implementation here.

    return std::make_shared<OAuth2Object>("uid-admin", true, true);
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
