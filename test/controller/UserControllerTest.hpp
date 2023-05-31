#pragma once

#include "oatpp-test/UnitTest.hpp"

class UserControllerTest : public oatpp::test::UnitTest
{
public:
  UserControllerTest();
  void onRun() override;
};
