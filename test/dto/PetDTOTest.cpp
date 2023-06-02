#include "PetDTOTest.hpp"

#include "generated/dto/PetDTO.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

void PetDTOTest::onRun()
{
  auto object = PetDTO::createShared();
  object->id = 1;
  object->category = CategoryDTO::createShared();
  object->category->id = 1;
  object->category->name = "name";
  object->name = "name";
  object->photoUrls = {"photoUrls"};
  object->tags = {TagDTO::createShared()};
  object->tags[0]->id = 1;
  object->tags[0]->name = "name";
  object->status = "status";

  oatpp::String jsonString =
      "{\"id\":1,"
      "\"category\":{\"id\":1,\"name\":\"name\"},"
      "\"name\":\"name\","
      "\"photoUrls\":[\"photoUrls\"],"
      "\"tags\":[{\"id\":1,\"name\":\"name\"}],"
      "\"status\":\"status\"}";

  /* Assert that serialized object as expected */
  OATPP_ASSERT(jsonString == objectMapper->writeToString(object));

  /* Assert that deserialized object as expected */
  OATPP_ASSERT(object == objectMapper->readFromString<oatpp::Object<PetDTO>>(jsonString));
}

PetDTOTest::PetDTOTest() : UnitTest("TEST[PetDTO]"), objectMapper(ObjectMapper::createShared()) {}
