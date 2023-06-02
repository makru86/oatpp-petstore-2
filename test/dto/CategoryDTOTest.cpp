#include "CategoryDTOTest.hpp"

#include "generated/dto/CategoryDTO.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

void CategoryDTOTest::onRun()
{
  auto object = CategoryDTO::createShared();
  object->id = 1;
  object->name = "name";

  oatpp::String jsonString =
      "{\"id\":1,"
      "\"name\":\"name\"}";

  /* Assert that serialized object as expected */
  OATPP_ASSERT(jsonString == objectMapper->writeToString(object));

  /* Assert that deserialized object as expected */
  OATPP_ASSERT(object == objectMapper->readFromString<oatpp::Object<CategoryDTO>>(jsonString));
}

CategoryDTOTest::CategoryDTOTest()
  : UnitTest("TEST[CategoryDTO]"), objectMapper(ObjectMapper::createShared())
{
}
