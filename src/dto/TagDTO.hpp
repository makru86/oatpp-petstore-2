#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class TagDTO : public oatpp::DTO {
  DTO_INIT(TagDTO, DTO)

  DTO_FIELD(Int64, id);
  DTO_FIELD(String, name);
};

#include OATPP_CODEGEN_END(DTO)

inline bool operator==(const TagDTO& lhs, const TagDTO& rhs) {
  auto order = [](const TagDTO& value) { return std::tie(value.id, value.name); };
  return order(lhs) == order(rhs);
}