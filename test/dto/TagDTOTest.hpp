#pragma once

#include "oatpp-test/UnitTest.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

class TagDTOTest : public oatpp::test::UnitTest
{
public:
  using ObjectMapper = oatpp::parser::json::mapping::ObjectMapper;

private:
  std::shared_ptr<ObjectMapper> objectMapper;

public:
  TagDTOTest();

  void onRun() override;
};
