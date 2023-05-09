#include "TagDTOTest.hpp"

#include "dto/TagDTO.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

void TagDTOTest::onRun()
{
  auto object = TagDTO::createShared();
  object->id = 1;
  object->name = "name";

  oatpp::String jsonString =
      "{\"id\":1,"
      "\"name\":\"name\"}";

  /* Assert that serialized object as expected */
  OATPP_ASSERT(jsonString == objectMapper->writeToString(object));

  /* Assert that deserialized object as expected */
  OATPP_ASSERT(object == objectMapper->readFromString<oatpp::Object<TagDTO>>(jsonString));
}

TagDTOTest::TagDTOTest() : UnitTest("TEST[TagDTO]"), objectMapper(ObjectMapper::createShared()) {}
