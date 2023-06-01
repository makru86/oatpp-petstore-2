#include "PetControllerTest.hpp"

#include "app/MyApiTestClient.hpp"
#include "app/TestComponent.hpp"
#include "controller/PetController.hpp"
#include "oatpp-test/web/ClientServerTestRunner.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"

PetControllerTest::PetControllerTest() : UnitTest("TEST[PetControllerTest]") {}

void PetControllerTest::onRun()
{
  /* Register test components */
  TestComponent component;

  /* Create client-server test runner */
  oatpp::test::web::ClientServerTestRunner runner;

  {
    /* Add PetController endpoints to the router of the test server */
    auto service = std::make_shared<MyPetService>();
    runner.addController(std::make_shared<PetController>(service));
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
        auto dto = PetDTO::createShared();

        {
          OATPP_LOGD(TAG, "addPet POST:/pet")
          auto response = client->addPet(petstoreAuth, dto);
          OATPP_ASSERT(response->getStatusCode() == 200)
          auto responseDto = response->readBodyToDto<oatpp::Object<PetDTO>>(objectMapper);
          OATPP_ASSERT(responseDto)
          OATPP_LOGD(TAG, "responseDto='%s'", objectMapper->writeToString(responseDto)->c_str())
          // TODO Test validations
        }

        {
          OATPP_LOGD(TAG, "updatePet PUT:/pet")
          auto response = client->updatePet(petstoreAuth, dto);
          OATPP_ASSERT(response->getStatusCode() == 200)
          auto responseDto = response->readBodyToDto<oatpp::Object<PetDTO>>(objectMapper);
          OATPP_ASSERT(responseDto)
          OATPP_LOGD(TAG, "responseDto='%s'", objectMapper->writeToString(responseDto)->c_str())
          // TODO Test validations
        }

        {
          OATPP_LOGD(TAG, "findPetsByStatus GET:/pet/findByStatus")
          auto response = client->findPetsByStatus(petstoreAuth, "available");
          OATPP_ASSERT(response->getStatusCode() == 200)
          auto responseDto =
              response->readBodyToDto<oatpp::List<oatpp::Object<PetDTO>>>(objectMapper);
          OATPP_ASSERT(responseDto)
          OATPP_LOGD(TAG, "responseDto='%s'", objectMapper->writeToString(responseDto)->c_str())
          // TODO Test validations
        }

        {
          OATPP_LOGD(TAG, "findPetsByTags GET:/pet/findByTags")
          auto response = client->findPetsByTags(petstoreAuth, "tag1,tag2");
          OATPP_ASSERT(response->getStatusCode() == 200)
          auto responseDto =
              response->readBodyToDto<oatpp::List<oatpp::Object<PetDTO>>>(objectMapper);
          OATPP_ASSERT(responseDto)
          OATPP_LOGD(TAG, "responseDto='%s'", objectMapper->writeToString(responseDto)->c_str())
          // TODO Test validations
        }

        {
          OATPP_LOGD(TAG, "getPetById GET:/pet/{petId}")
          auto response = client->getPetById(apiKey, int64_t{1});
          OATPP_ASSERT(response->getStatusCode() == 200)
          auto responseDto = response->readBodyToDto<oatpp::Object<PetDTO>>(objectMapper);
          OATPP_ASSERT(responseDto)
          OATPP_LOGD(TAG, "responseDto='%s'", objectMapper->writeToString(responseDto)->c_str())
          // TODO Test validations
        }

        //       {
        //            OATPP_LOGD(TAG, "updatePetWithForm POST:/pet/{petId}")
        //                auto response = client->updatePetWithForm(apiKey, "id", "name", "status");
        //      }

        {
          OATPP_LOGD(TAG, "deletePet DELETE:/pet/{petId}")
          auto response = client->deletePet(petstoreAuth, int64_t{0});
          OATPP_ASSERT(response->getStatusCode() == 200)
          // TODO Test validations
        }
      },
      std::chrono::minutes(10) /* test timeout */);

  /* wait all server threads finished */
  std::this_thread::sleep_for(std::chrono::seconds(1));
}
