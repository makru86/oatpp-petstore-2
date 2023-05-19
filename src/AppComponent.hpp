#ifndef AppComponent_hpp
#define AppComponent_hpp

#include "auth/ApiKeyAuth.hpp"
#include "auth/OAuth2.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/web/server/HttpConnectionHandler.hpp"

/**
 *  Class which creates and holds Application components and registers components in
 * oatpp::base::Environment Order of components initialization is from top to bottom
 */
class AppComponent
{
public:
  /**
   *  Create ConnectionProvider component which listens on the port
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>,
                         serverConnectionProvider)
  ([] {
    return oatpp::network::tcp::server::ConnectionProvider::createShared(
        {"0.0.0.0", 8000, oatpp::network::Address::IP_4});
  }());

  /**
   *  Create Router component
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)
  ([] { return oatpp::web::server::HttpRouter::createShared(); }());

  /**
   *  Create ConnectionHandler component which uses Router component to route requests
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>,
                         serverConnectionHandler)
  ([] {
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>,
                    router);  // get Router component

    auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);

    // api_key Handler
    auto apiKeyAuthHandler = std::make_shared<ApiKeyAuthHandler>("My realm");
    oatpp::String apiKeyHeaderName = "api_key";

    connectionHandler->addRequestInterceptor(
        std::make_shared<ApiKeyInterceptor>(apiKeyAuthHandler, apiKeyHeaderName));

    // petstore_auth Handler
    auto oauth2Handler = std::make_shared<OAuth2Handler>("My realm");
    connectionHandler->addRequestInterceptor(std::make_shared<OAuth2Interceptor>(oauth2Handler));

    return connectionHandler;
  }());

  /**
   *  Create ObjectMapper component to serialize/deserialize DTOs in Contoller's API
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper)
  ([] { return oatpp::parser::json::mapping::ObjectMapper::createShared(); }());
};

#endif /* AppComponent_hpp */
