#pragma once

#include "oatpp-test/UnitTest.hpp"

class UserControllerTest : public oatpp::test::UnitTest {
public:

  UserControllerTest() : UnitTest("TEST[UserControllerTest]"){}
  void onRun() override;

};