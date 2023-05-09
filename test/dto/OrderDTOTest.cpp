#include "OrderDTOTest.hpp"

#include "dto/OrderDTO.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

void OrderDTOTest::onRun()
{
  auto object = OrderDTO::createShared();
  object->id = 1;
  object->petId = 1;
  object->quantity = 1;
  object->shipDate = "shipDate";
  object->status = "status";
  object->complete = true;

  oatpp::String jsonString =
      "{\"id\":1,"
      "\"petId\":1,"
      "\"quantity\":1,"
      "\"shipDate\":\"shipDate\","
      "\"status\":\"status\","
      "\"complete\":true}";

  /* Assert that serialized object as expected */
  OATPP_ASSERT(jsonString == objectMapper->writeToString(object));

  /* Assert that deserialized object as expected */
  OATPP_ASSERT(object == objectMapper->readFromString<oatpp::Object<OrderDTO>>(jsonString));
}

OrderDTOTest::OrderDTOTest()
  : UnitTest("TEST[OrderDTO]"), objectMapper(ObjectMapper::createShared())
{
}
