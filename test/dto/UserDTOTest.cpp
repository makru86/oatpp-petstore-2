#include "UserDTOTest.hpp"

#include "generated/dto/UserDTO.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

void UserDTOTest::onRun()
{
  auto object = UserDTO::createShared();
  object->id = 1;
  object->username = "username";
  object->firstName = "firstName";
  object->lastName = "lastName";
  object->email = "email";
  object->password = "password";
  object->phone = "phone";
  object->userStatus = 1;

  oatpp::String jsonString =
      "{\"id\":1,"
      "\"username\":\"username\","
      "\"firstName\":\"firstName\","
      "\"lastName\":\"lastName\","
      "\"email\":\"email\","
      "\"password\":\"password\","
      "\"phone\":\"phone\","
      "\"userStatus\":1}";

  /* Assert that serialized object as expected */
  OATPP_ASSERT(jsonString == objectMapper->writeToString(object));

  /* Assert that deserialized object as expected */
  OATPP_ASSERT(object == objectMapper->readFromString<oatpp::Object<UserDTO>>(jsonString));
}

UserDTOTest::UserDTOTest() : UnitTest("TEST[UserDTO]"), objectMapper(ObjectMapper::createShared())
{
}
