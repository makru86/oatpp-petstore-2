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

    oatpp::String userId = "uid-admin";
    OATPP_LOGD(TAG, "allow access: %s", userId->c_str());
    return std::make_shared<ApiKeyAuthObject>(userId);
  }
};
