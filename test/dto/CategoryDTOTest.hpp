#pragma once

#include "oatpp-test/UnitTest.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

class CategoryDTOTest : public oatpp::test::UnitTest
{
public:
  using ObjectMapper = oatpp::parser::json::mapping::ObjectMapper;

private:
  std::shared_ptr<ObjectMapper> objectMapper;

public:
  CategoryDTOTest();

  void onRun() override;
};
