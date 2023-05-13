#pragma once

#include "oatpp/web/server/handler/AuthorizationHandler.hpp"

class ApiKeyAuthorizationObject : public oatpp::web::server::handler::AuthorizationObject
{
public:
  explicit ApiKeyAuthorizationObject(const oatpp::String& pUserId) : userId(pUserId) {}
  oatpp::String userId;
};

class ApiKeyAuthorizationHandler : public oatpp::web::server::handler::AuthorizationHandler
{
public:
  /**
   * Constructor.
   * @param realm - realm. &id:oatpp::String;.
   */
  explicit ApiKeyAuthorizationHandler(const oatpp::String& realm)
    : AuthorizationHandler("apiKey", realm)
  {
  }

  /**
   * Implement this method! Return nullptr if authorization should be denied.
   * @param header - `Authorization` header. &id:oatpp::String;.
   * @return - `std::shared_ptr` to &id:oatpp::web::server::handler::AuthorizationObject;.
   */
  std::shared_ptr<AuthorizationObject> handleAuthorization(const oatpp::String& header) override
  {
    OATPP_LOGD("ApiKeyAuthorizationHandler", "header=%s", header ? header->c_str() : "null")
    if (header) {
      return std::make_shared<ApiKeyAuthorizationObject>("uid-admin");
    }
    Headers responseHeaders;
    addErrorResponseHeaders(responseHeaders);
    throw oatpp::web::protocol::http::HttpError(oatpp::web::protocol::http::Status::CODE_401,
                                                "Unauthorized", responseHeaders);

    // TODO Replace above with your implementation.
  }
};
