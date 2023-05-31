#include "StoreControllerTest.hpp"

#include "app/MyApiTestClient.hpp"
#include "app/TestComponent.hpp"
#include "controller/StoreController.hpp"
#include "oatpp-test/web/ClientServerTestRunner.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"

StoreControllerTest::StoreControllerTest() : UnitTest("TEST[StoreControllerTest]") {}

void StoreControllerTest::onRun()
{
  /* Register test components */
  TestComponent component;

  /* Create client-server test runner */
  oatpp::test::web::ClientServerTestRunner runner;

  {
    /* Add StoreController endpoints to the router of the test server */
    auto service = std::make_shared<MyStoreService>();
    runner.addController(std::make_shared<StoreController>(service));
  }

  /* Run test */
  runner.run(
      [] {
        /* Get client connection provider for Api Client */
        OATPP_COMPONENT(std::shared_ptr<oatpp::network::ClientConnectionProvider>,
                        clientConnectionProvider);

        /* Get object mapper component */
        OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper);

        /* Create http request executor for Api Client */
        auto requestExecutor =
            oatpp::web::client::HttpRequestExecutor::createShared(clientConnectionProvider);

        /* Create Test API client */
        auto client = MyApiTestClient::createShared(requestExecutor, objectMapper);

        oatpp::String apiKey = "special_key";
        oatpp::String petstoreAuth = "870bbe18-0969-47b2-9b31-ddf1e6aa9e55";

        {
          OATPP_LOGI(TAG, "test getInventory (GET /store/inventory)...")
          auto response = client->getInventory(apiKey);
          OATPP_ASSERT(response->getStatusCode() == 200)
          auto responseBody = response->readBodyToString();
          OATPP_ASSERT(responseBody)
          OATPP_ASSERT(responseBody == "{}")
          auto responseFields =
              objectMapper->readFromString<oatpp::UnorderedFields<oatpp::Int32>>(responseBody);
          OATPP_ASSERT(responseFields)
          // TODO Test validations
          OATPP_LOGI(TAG, "OK")
        }

        {
          OATPP_LOGI(TAG, "test placeOrder POST:/store/order...")
          auto dto = OrderDTO::createShared();
          auto response = client->placeOrder(dto);
          OATPP_ASSERT(response->getStatusCode() == 200)
          auto responseDto = response->readBodyToDto<oatpp::Object<OrderDTO>>(objectMapper);
          OATPP_ASSERT(responseDto)
          OATPP_LOGD(TAG, "responseDto='%s'", objectMapper->writeToString(responseDto)->c_str())
          // TODO Test validations
          OATPP_LOGI(TAG, "OK")
        }

        {
          OATPP_LOGI(TAG, "test getOrderById GET:/store/order/{orderId}...")
          auto response = client->getOrderById("0");
          OATPP_ASSERT(response->getStatusCode() == 200)
          auto responseDto = response->readBodyToDto<oatpp::Object<OrderDTO>>(objectMapper);
          OATPP_ASSERT(responseDto)
          OATPP_LOGD(TAG, "responseDto='%s'", objectMapper->writeToString(responseDto)->c_str())
          // TODO Test validations
          OATPP_LOGI(TAG, "OK")
        }

        {
          OATPP_LOGI(TAG, "test deleteOrder DELETE:/store/order/{orderId}...")
          auto response = client->deleteOrder("orderId");
          OATPP_ASSERT(response->getStatusCode() == 200)
          // TODO Test validations
          OATPP_LOGI(TAG, "OK")
        }
      },
      std::chrono::minutes(10) /* test timeout */);

  /* wait all server threads finished */
  std::this_thread::sleep_for(std::chrono::seconds(1));
}
