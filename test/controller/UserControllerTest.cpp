#include "UserControllerTest.hpp"

#include "controller/UserController.hpp"

#include "app/MyApiTestClient.hpp"
#include "app/TestComponent.hpp"

#include "oatpp/web/client/HttpRequestExecutor.hpp"

#include "oatpp-test/web/ClientServerTestRunner.hpp"

void UserControllerTest::onRun() {

    /* Register test components */
    TestComponent component;

    /* Create client-server test runner */
    oatpp::test::web::ClientServerTestRunner runner;

    /* Add UserController endpoints to the router of the test server */
    runner.addController(std::make_shared<UserController>());

    /* Run test */
    runner.run([] {

        /* Get client connection provider for Api Client */
        OATPP_COMPONENT(std::shared_ptr<oatpp::network::ClientConnectionProvider>, clientConnectionProvider);

        /* Get object mapper component */
        OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper);

        /* Create http request executor for Api Client */
        auto requestExecutor = oatpp::web::client::HttpRequestExecutor::createShared(clientConnectionProvider);

        /* Create Test API client */
        auto client = MyApiTestClient::createShared(requestExecutor, objectMapper);

        {
            auto dto = UserDTO::createShared();
            auto response = client->createUser(dto);
            // TODO Test validations
        }

        {
            auto dto = UserDTO::createShared();
            auto dtos = oatpp::Vector<oatpp::Object<UserDTO>>({});
            dtos->push_back(dto);
            auto response = client->createUsersWithArrayInput(dtos);
            // TODO Test validations
        }

        {
            auto dto = UserDTO::createShared();
            auto dtos = oatpp::Vector<oatpp::Object<UserDTO>>({});
            dtos->push_back(dto);
            dtos->push_back(dto);
            auto response = client->createUsersWithListInput(dtos);
            // TODO Test validations
        }

        {
            auto response = client->getUserByName("username");
            // TODO Test validations
        }

    }, std::chrono::minutes(10) /* test timeout */);

  /* wait all server threads finished */
  std::this_thread::sleep_for(std::chrono::seconds(1));
}
