#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class OrderDTO : public oatpp::DTO
{
  DTO_INIT(OrderDTO, DTO)

  DTO_FIELD(Int64, id);
  DTO_FIELD(Int64, petId);
  DTO_FIELD(Int32, quantity);
  DTO_FIELD(String, shipDate);
  DTO_FIELD(String, status);
  DTO_FIELD(Boolean, complete) = false;

  DTO_HC_EQ(id, petId, quantity, shipDate, status, complete);
};

#include OATPP_CODEGEN_END(DTO)
