#pragma once

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class ApiResponseDTO : public oatpp::DTO {

    DTO_INIT(ApiResponseDTO, DTO)

    DTO_FIELD(Int32, code);
    DTO_FIELD(String, type);
    DTO_FIELD(String, message);
};

#include OATPP_CODEGEN_END(DTO)

inline bool operator==(const ApiResponseDTO& lhs, const ApiResponseDTO& rhs) {
    auto order = [](const ApiResponseDTO& value) {
        return std::tie(value.code, value.type, value.message);
    };
    return order(lhs) == order(rhs);
}