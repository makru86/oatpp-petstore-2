#pragma once

#include "dto/UserDTO.hpp"
#include "oatpp/core/async/Coroutine.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

class UserController : public oatpp::web::server::api::ApiController
{
public:
  explicit UserController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper)
  {
  }

  ENDPOINT_INFO(createUser)
  {
    info->summary = "Create user";
    info->addConsumes<Object<UserDTO>>("application/json");
  };
  ENDPOINT("POST", "/user", createUser, BODY_DTO(Object<UserDTO>, body))
  {
    OATPP_LOGD("createUser", "")
    // TODO Add your implementation here.
    return createResponse(Status::CODE_200, "OK");
  }

  ENDPOINT_INFO(createUsersWithArrayInput)
  {
    info->summary = "Creates list of users with given input array";
    info->addConsumes<oatpp::Vector<Object<UserDTO>>>("application/json");
  };
  ENDPOINT("POST", "/user/createWithArray", createUsersWithArrayInput,
           BODY_DTO(oatpp::Vector<Object<UserDTO>>, body))
  {
    OATPP_LOGD("createUsersWithArrayInput", "")
    // TODO Add your implementation here.
    return createResponse(Status::CODE_200, "OK");
  }

  ENDPOINT_INFO(createUsersWithListInput)
  {
    info->summary = "Creates list of users with given input array";
    info->addConsumes<oatpp::Vector<Object<UserDTO>>>("application/json");
  };
  ENDPOINT("POST", "/user/createWithList", createUsersWithListInput,
           BODY_DTO(oatpp::Vector<Object<UserDTO>>, body))
  {
    OATPP_LOGD("createUsersWithListInput", "")
    // TODO Add your implementation here.
    return createResponse(Status::CODE_200, "OK");
  }

  ENDPOINT_INFO(loginUser)
  {
    info->summary = "Logs user into the system";
    info->queryParams.add<String>("username");
    info->queryParams.add<String>("password");
  };
  ENDPOINT("GET", "/user/login", loginUser, QUERY(String, username), QUERY(String, password))
  {
    OATPP_LOGD("loginUser", "username=%s passpword=%s", username->c_str(), password->c_str())

    // TODO Add your implementation here.

    auto response = createResponse(Status::CODE_200, "OK");
    response->putHeader("Set-Cookie", "AUTH_KEY=abcde12345; Path=/; HttpOnly");
    response->putHeader("X-Rate-Limit", std::to_string(60));
    response->putHeader("X-Expires-After", std::to_string(3600));
    return response;
  };

  ENDPOINT_INFO(logoutUser) { info->summary = "Logs out current logged in user session"; };
  ENDPOINT("GET", "/user/logout", logoutUser, HEADER(String, api_key))
  {
    OATPP_LOGD("logoutUser", "api_key=%s", api_key->c_str())
    // TODO Add your implementation here.
    return createResponse(Status::CODE_200, "OK");
  }

  ENDPOINT_INFO(getUserByName)
  {
    info->summary = "Get user by user name";
    info->addResponse<Object<UserDTO>>(Status::CODE_200, "application/json");
  };
  ENDPOINT("GET", "/user/{username}", getUserByName, PATH(String, username, "username"))
  {
    OATPP_LOGD("getUserByName", "username=%s", username->c_str())
    // TODO Add your implementation here.
    auto dto = UserDTO::createShared();
    return createDtoResponse(Status::CODE_200, dto);
  }

  ENDPOINT_INFO(updateUser)
  {
    info->summary = "Updated user";
    info->addConsumes<Object<UserDTO>>("application/json");
  };
  ENDPOINT("PUT", "/user/{username}", updateUser, PATH(String, username, "username"),
           HEADER(String, api_key), BODY_DTO(Object<UserDTO>, body))
  {
    OATPP_LOGD("updateUser", "username=%s api_key=%s", username->c_str(), api_key->c_str())
    // TODO Add your implementation here.
    auto dto = UserDTO::createShared();
    return createDtoResponse(Status::CODE_200, dto);
  }

  ENDPOINT_INFO(deleteUser) { info->summary = "Delete user"; };
  ENDPOINT("DELETE", "/user/{username}", deleteUser, PATH(String, username, "username"),
           HEADER(String, api_key))
  {
    OATPP_LOGD("deleteUser", "username=%s api_key=%s", username->c_str(), api_key->c_str())
    // TODO Add your implementation here.
    return createResponse(Status::CODE_200, "OK");
  }

};  // class UserController

#include OATPP_CODEGEN_END(ApiController)
