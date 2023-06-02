#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class UserDTO : public oatpp::DTO
{
  DTO_INIT(UserDTO, DTO)

  DTO_FIELD(Int64, id);
  DTO_FIELD(String, username);
  DTO_FIELD(String, firstName);
  DTO_FIELD(String, lastName);
  DTO_FIELD(String, email);
  DTO_FIELD(String, password);
  DTO_FIELD(String, phone);
  DTO_FIELD(Int32, userStatus);

  DTO_HC_EQ(id, username, firstName, lastName, email, password, phone, userStatus);
};

#include OATPP_CODEGEN_END(DTO)
