#pragma once

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class CategoryDTO : public oatpp::DTO {

    DTO_INIT(CategoryDTO, DTO)

    DTO_FIELD(Int64, id);

    DTO_FIELD(String, name);
};

#include OATPP_CODEGEN_END(DTO)

inline
bool operator==(const CategoryDTO &lhs, const CategoryDTO &rhs) {
    auto order = [](const CategoryDTO &value) {
        return std::tie(value.id, value.name);
    };
    return order(lhs) == order(rhs);
}
