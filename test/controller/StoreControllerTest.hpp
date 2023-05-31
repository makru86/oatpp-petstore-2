#pragma once

#include "oatpp-test/UnitTest.hpp"

class StoreControllerTest : public oatpp::test::UnitTest
{
  constexpr static const char* TAG = "StoreControllerTest";

public:
  StoreControllerTest();
  void onRun() override;
};
