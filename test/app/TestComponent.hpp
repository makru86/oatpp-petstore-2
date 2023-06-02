#ifndef TestComponent_htpp
#define TestComponent_htpp

#include "generated/auth/ApiKeyAuth.hpp"
#include "generated/auth/OAuth2.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/network/virtual_/Interface.hpp"
#include "oatpp/network/virtual_/client/ConnectionProvider.hpp"
#include "oatpp/network/virtual_/server/ConnectionProvider.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/web/server/HttpConnectionHandler.hpp"

/**
 * Test Components config
 */
class TestComponent
{
public:
  /**
   * Create oatpp virtual network interface for test networking
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::virtual_::Interface>, virtualInterface)
  ([] { return oatpp::network::virtual_::Interface::obtainShared("virtualhost"); }());

  /**
   * Create server ConnectionProvider of oatpp virtual connections for test
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>,
                         serverConnectionProvider)
  ([] {
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::virtual_::Interface>, interface);
    return oatpp::network::virtual_::server::ConnectionProvider::createShared(interface);
  }());

  /**
   * Create client ConnectionProvider of oatpp virtual connections for test
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ClientConnectionProvider>,
                         clientConnectionProvider)
  ([] {
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::virtual_::Interface>, interface);
    return oatpp::network::virtual_::client::ConnectionProvider::createShared(interface);
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

#endif  // TestComponent_htpp
