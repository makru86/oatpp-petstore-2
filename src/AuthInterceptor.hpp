
#ifndef EXAMPLE_JWT_AUTHINTERCEPTOR_HPP
#define EXAMPLE_JWT_AUTHINTERCEPTOR_HPP

#include "auth/AuthHandler.hpp"
#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/web/server/HttpRouter.hpp"
#include "oatpp/web/server/handler/AuthorizationHandler.hpp"
#include "oatpp/web/server/interceptor/RequestInterceptor.hpp"

class AuthInterceptor : public oatpp::web::server::interceptor::RequestInterceptor
{
private:
  AuthHandler m_authHandler;
  oatpp::web::server::HttpRouterTemplate<bool> authEndpoints;

public:
  AuthInterceptor(const std::shared_ptr<JWT>& jwt);

  std::shared_ptr<OutgoingResponse> intercept(
      const std::shared_ptr<IncomingRequest>& request) override;
};

AuthInterceptor::AuthInterceptor(const std::shared_ptr<JWT>& jwt) : m_authHandler(jwt)
{
  authEndpoints.route("POST", "users/signup", false);
  authEndpoints.route("POST", "users/signin", false);

  authEndpoints.route("GET", "swagger/*", false);
  authEndpoints.route("GET", "api-docs/oas-3.0.0.json", false);
}

std::shared_ptr<AuthInterceptor::OutgoingResponse> AuthInterceptor::intercept(
    const std::shared_ptr<IncomingRequest>& request)
{
  auto r =
      authEndpoints.getRoute(request->getStartingLine().method, request->getStartingLine().path);
  if (r && !r.getEndpoint()) {
    return nullptr;  // Continue without Authorization
  }

  auto authHeader = request->getHeader(oatpp::web::protocol::http::Header::AUTHORIZATION);

  auto authObject =
      std::static_pointer_cast<JWT::Payload>(m_authHandler.handleAuthorization(authHeader));
  if (authObject) {
    request->putBundleData("userId", authObject->userId);
    return nullptr;  // Continue - token is valid.
  }

  throw oatpp::web::protocol::http::HttpError(oatpp::web::protocol::http::Status::CODE_401,
                                              "Unauthorized", {});
}

#endif  // EXAMPLE_JWT_AUTHINTERCEPTOR_HPP
