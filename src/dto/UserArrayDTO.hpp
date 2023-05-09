#pragma once

#include "UserDTO.hpp"
#include "oatpp/core/Types.hpp"
#include "oatpp/core/data/mapping/type/Vector.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class UserDTO : public oatpp::DTO {
  DTO_INIT(UserDTO, DTO)

  DTO_FIELD(Int64, id);

  DTO_FIELD(String, username);

  DTO_FIELD(String, firstName);

  DTO_FIELD(String, lastName);

  DTO_FIELD(String, email);

  DTO_FIELD(String, password);

  DTO_FIELD(String, phone);

  DTO_FIELD(Int32, userStatus);
};

#include OATPP_CODEGEN_END(DTO)

inline bool operator==(const UserDTO& lhs, const UserDTO& rhs) {
  auto order = [](const UserDTO& value) {
    return std::tie(value.id, value.username, value.firstName, value.lastName, value.email,
                    value.password, value.phone, value.userStatus);
  };
  return order(lhs) == order(rhs);
}
