#pragma once

#include "CategoryDTO.hpp"
#include "TagDTO.hpp"
#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class PetDTO : public oatpp::DTO {
  DTO_INIT(PetDTO, DTO)

  DTO_FIELD(Int64, id);

  DTO_FIELD(Object<CategoryDTO>, category);

  DTO_FIELD_INFO(name) { info->required = true; }

  DTO_FIELD(String, name);

  DTO_FIELD_INFO(photoUrls) { info->required = true; }

  DTO_FIELD(Vector<String>, photoUrls);

  DTO_FIELD(Vector<Object<TagDTO>>, tags);

  DTO_FIELD(String, status);
};

#include OATPP_CODEGEN_END(DTO)

template <typename T>
bool operator==(const oatpp::Vector<T>& lhs, const oatpp::Vector<T>& rhs) {
  if (lhs->size() != rhs->size()) {
    return false;
  }
  for (size_t i = 0; i < lhs->size(); ++i) {
    if (lhs[i] != rhs[i]) {
      return false;
    }
  }
  return true;
}

inline bool operator==(const PetDTO& lhs, const PetDTO& rhs) {
  // TODO std::tie is not working with oatpp::Vector

  auto result = lhs.id == rhs.id && lhs.category == rhs.category && lhs.name == rhs.name &&
                lhs.photoUrls == rhs.photoUrls && lhs.tags == rhs.tags && lhs.status == rhs.status;
  return result;
}