#pragma once

#include "dto/UserDTO.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/core/async/Coroutine.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

class UserController : public oatpp::web::server::api::ApiController {
    typedef UserController __ControllerType;

public:
    explicit UserController(
            OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
            : oatpp::web::server::api::ApiController(objectMapper) {}

    ENDPOINT_INFO(createUser) {
        info->summary = "Create user";
        info->addConsumes < Object < UserDTO >> ("application/json");
    };
    ENDPOINT_ASYNC("POST", "/user", createUser) {
    ENDPOINT_ASYNC_INIT(createUser)

        Action act() override {
            return request->readBodyToDtoAsync<oatpp::Object<UserDTO>>(
                    controller->getDefaultObjectMapper()
            ).callbackTo(&createUser::returnResponse);
        }

        Action returnResponse(const oatpp::Object<UserDTO> &dto) {
            return _return(controller->createResponse(Status::CODE_200, "OK"));
        }
    };

    ENDPOINT_INFO(createUsersWithArrayInput) {
        info->summary = "Creates list of users with given input array";
        info->addConsumes < Object < UserDTO >> ("application/json");
    };
    ENDPOINT_ASYNC("POST", "/user/createWithArray", createUsersWithArrayInput) {
    ENDPOINT_ASYNC_INIT(createUsersWithArrayInput)

        Action act() override {
            return request->readBodyToDtoAsync<oatpp::Object<UserDTO>>(
                    controller->getDefaultObjectMapper()
            ).callbackTo(&createUsersWithArrayInput::returnResponse);
        }

        Action returnResponse(const oatpp::Object<UserDTO> &dto) {
            return _return(controller->createResponse(Status::CODE_200, "OK"));
        }
    };

    ENDPOINT_INFO(createUsersWithListInput) {
        info->summary = "Creates list of users with given input array";
        info->addConsumes < Object < UserDTO >> ("application/json");
    };
    ENDPOINT_ASYNC("POST", "/user/createWithList", createUsersWithListInput) {
    ENDPOINT_ASYNC_INIT(createUsersWithListInput)

        Action act() override {
            return request->readBodyToDtoAsync<oatpp::Object<UserDTO>>(
                    controller->getDefaultObjectMapper()
            ).callbackTo(&createUsersWithListInput::returnResponse);
        }

        Action returnResponse(const oatpp::Object<UserDTO> &dto) {
            return _return(controller->createResponse(Status::CODE_200, "OK"));
        }
    };

    ENDPOINT_INFO(loginUser) {
        info->summary = "Logs user into the system";
        info->queryParams.add<String>("username");
        info->queryParams.add<String>("password");
    };
    ENDPOINT_ASYNC("GET", "/user/login", loginUser) {
    ENDPOINT_ASYNC_INIT(loginUser)

        String username;
        String password;

        Action act() override {
            username = request->getQueryParameter("username", "");
            password = request->getQueryParameter("password", "");
            OATPP_LOGD("OpenAPI Petstore", "username=%s", username->c_str());
            OATPP_LOGD("OpenAPI Petstore", "password=%s", password->c_str());
            return _return(controller->createResponse(Status::CODE_200, "OK"));
        }
    };

    ENDPOINT_INFO(logoutUser) {
        info->summary = "Logs out current logged in user session";
    };
    ENDPOINT_ASYNC("GET", "/user/logout", logoutUser) {
    ENDPOINT_ASYNC_INIT(logoutUser)

        Action act() override {
            return _return(controller->createResponse(Status::CODE_200, "OK"));
        }
    };

    ENDPOINT_INFO(getUserByName) {
        info->summary = "Get user by user name";
        info->addResponse < Object < UserDTO >> (Status::CODE_200, "application/json");
    };
    ENDPOINT_ASYNC("GET", "/user/{username}", getUserByName) {
    ENDPOINT_ASYNC_INIT(getUserByName)

        Action act() override {
            return request->readBodyToDtoAsync<oatpp::Object<UserDTO>>(
                    controller->getDefaultObjectMapper()
            ).callbackTo(&getUserByName::returnResponse);
        }

        Action returnResponse(const oatpp::Object<UserDTO> &dto) {
            return _return(controller->createResponse(Status::CODE_200, "OK"));
        }
    };

    ENDPOINT_INFO(updateUser) {
        info->summary = "Updated user";
        info->addConsumes < Object < UserDTO >> ("application/json");
    };
    ENDPOINT_ASYNC("PUT", "/user/{username}", updateUser) {
    ENDPOINT_ASYNC_INIT(updateUser)

        Action act() override {
            return request->readBodyToDtoAsync<oatpp::Object<UserDTO>>(
                    controller->getDefaultObjectMapper()
            ).callbackTo(&updateUser::returnResponse);
        }

        Action returnResponse(const oatpp::Object<UserDTO> &dto) {
            return _return(controller->createResponse(Status::CODE_200, "OK"));
        }
    };

    ENDPOINT_INFO(deleteUser) {
        info->summary = "Delete user";
    };
    ENDPOINT_ASYNC("DELETE", "/user/{username}", deleteUser) {
    ENDPOINT_ASYNC_INIT(deleteUser)

        Action act() override {
            return request->readBodyToDtoAsync<oatpp::Object<UserDTO>>(
                    controller->getDefaultObjectMapper()
            ).callbackTo(&deleteUser::returnResponse);
        }

        Action returnResponse(const oatpp::Object<UserDTO> &dto) {
            return _return(controller->createResponse(Status::CODE_200, "OK"));
        }
    };
};

#include OATPP_CODEGEN_END(ApiController)