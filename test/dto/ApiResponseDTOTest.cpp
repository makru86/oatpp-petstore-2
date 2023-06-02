#include "ApiResponseDTOTest.hpp"

#include "generated/dto/ApiResponseDTO.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

void ApiResponseDTOTest::onRun()
{
  auto object = ApiResponseDTO::createShared();
  object->code = 1;
  object->type = "type";
  object->message = "message";

  oatpp::String jsonString =
      "{\"code\":1,"
      "\"type\":\"type\","
      "\"message\":\"message\"}";

  /* Assert that serialized object as expected */
  OATPP_ASSERT(jsonString == objectMapper->writeToString(object));

  /* Assert that deserialized object as expected */
  OATPP_ASSERT(object == objectMapper->readFromString<oatpp::Object<ApiResponseDTO>>(jsonString));
}

ApiResponseDTOTest::ApiResponseDTOTest()
  : UnitTest("TEST[ApiResponseDTO]"), objectMapper(ObjectMapper::createShared())
{
}
