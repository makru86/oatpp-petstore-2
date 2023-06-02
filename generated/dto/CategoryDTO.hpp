#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class CategoryDTO : public oatpp::DTO
{
  DTO_INIT(CategoryDTO, DTO)

  DTO_FIELD(Int64, id);
  DTO_FIELD(String, name);

  DTO_HC_EQ(id, name);
};

#include OATPP_CODEGEN_END(DTO)
