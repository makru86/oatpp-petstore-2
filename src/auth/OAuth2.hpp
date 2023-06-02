#pragma once

#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/web/server/HttpRouter.hpp"
#include "oatpp/web/server/handler/AuthorizationHandler.hpp"

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
