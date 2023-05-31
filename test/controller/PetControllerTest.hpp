#pragma once

#include "oatpp-test/UnitTest.hpp"

class PetControllerTest : public oatpp::test::UnitTest
{
  constexpr static const char* TAG = "PetControllerTest";

public:
  PetControllerTest();
  void onRun() override;
};
