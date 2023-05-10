#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class ApiResponseDTO : public oatpp::DTO
{
  DTO_INIT(ApiResponseDTO, DTO)

  DTO_FIELD(Int32, code);
  DTO_FIELD(String, type);
  DTO_FIELD(String, message);

  DTO_HC_EQ(code, type, message);
};

#include OATPP_CODEGEN_END(DTO)
