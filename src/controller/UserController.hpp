#pragma once

#include "dto/UserDTO.hpp"
#include "oatpp/core/async/Coroutine.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/server/api/ApiController.hpp"
#include "service/UserService.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

class UserController : public oatpp::web::server::api::ApiController
{
  std::shared_ptr<UserService> m_service;

  // FIXME move somewhere, like src/Common.hpp
  oatpp::String protectByAsterisks(const oatpp::String& secret)
  {
    if (!secret) {
      return "null";
    }
    oatpp::String result("");
    for (auto i = 0; i != secret->size(); i++) {
      result = result + "*";
    }
    return result;
  }

public:
  explicit UserController(std::shared_ptr<UserService> userService,
                          OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper), m_service(userService)
  {
  }

  ENDPOINT_INFO(createUser)
  {
    info->summary = "Create user";
    info->addConsumes<Object<UserDTO>>("application/json");
  };
  ENDPOINT("POST", "/user", createUser, BODY_DTO(Object<UserDTO>, body), BUNDLE(String, userId))
  {
    OATPP_LOGD("createUser", "")
    return m_service->createUser(userId, body);
  }

  ENDPOINT_INFO(createUsersWithArrayInput)
  {
    info->summary = "Creates list of users with given input array";
    info->addConsumes<oatpp::Vector<Object<UserDTO>>>("application/json");
  };
  ENDPOINT("POST", "/user/createWithArray", createUsersWithArrayInput,
           BODY_DTO(oatpp::Vector<Object<UserDTO>>, body), BUNDLE(String, userId))
  {
    OATPP_LOGD("createUsersWithArrayInput", "")
    auto responseDto = m_service->createUsersWithArrayInput(userId, body);
    return createDtoResponse(Status::CODE_200, responseDto);
  }

  ENDPOINT_INFO(createUsersWithListInput)
  {
    info->summary = "Creates list of users with given input array";
    info->addConsumes<oatpp::Vector<Object<UserDTO>>>("application/json");
  };
  ENDPOINT("POST", "/user/createWithList", createUsersWithListInput,
           BODY_DTO(oatpp::Vector<Object<UserDTO>>, body), BUNDLE(String, userId))
  {
    OATPP_LOGD("createUsersWithListInput", "")
    auto responseDto = m_service->createUsersWithListInput(userId, body);
    return createDtoResponse(Status::CODE_200, responseDto);
  }

  ENDPOINT_INFO(loginUser)
  {
    info->summary = "Logs user into the system";
    info->queryParams.add<String>("username");
    info->queryParams.add<String>("password");
  };
  ENDPOINT("GET", "/user/login", loginUser, QUERY(String, username), QUERY(String, password))
  {
    OATPP_LOGD("loginUser", "username=%s passpword=%s", username->c_str(),
               protectByAsterisks(password)->c_str())
    return m_service->loginUser(username, password);
  };

  ENDPOINT_INFO(logoutUser) { info->summary = "Logs out current logged in user session"; };
  ENDPOINT("GET", "/user/logout", logoutUser, HEADER(String, api_key), BUNDLE(String, userId))
  {
    OATPP_LOGD("logoutUser", "api_key=%s", api_key->c_str())
    return m_service->logoutUser(userId);
  }

  ENDPOINT_INFO(getUserByName)
  {
    info->summary = "Get user by user name";
    info->addResponse<Object<UserDTO>>(Status::CODE_200, "application/json");
  };
  ENDPOINT("GET", "/user/{username}", getUserByName, PATH(String, username, "username"))
  {
    OATPP_LOGD("getUserByName", "username=%s", username->c_str())
    auto responseDto = m_service->getUserByName(username);
    return createDtoResponse(Status::CODE_200, responseDto);
  }

  ENDPOINT_INFO(updateUser)
  {
    info->summary = "Updated user";
    info->addConsumes<Object<UserDTO>>("application/json");
  };
  ENDPOINT("PUT", "/user/{username}", updateUser, PATH(String, username, "username"),
           HEADER(String, api_key), BODY_DTO(Object<UserDTO>, dto), BUNDLE(String, userId))
  {
    OATPP_LOGD("updateUser", "username=%s api_key=%s", username->c_str(), api_key->c_str())
    auto responseDto = m_service->updateUser(userId, username, dto);
    return createDtoResponse(Status::CODE_200, responseDto);
  }

  ENDPOINT_INFO(deleteUser) { info->summary = "Delete user"; };
  ENDPOINT("DELETE", "/user/{username}", deleteUser, PATH(String, username, "username"),
           HEADER(String, api_key), BUNDLE(String, userId))
  {
    OATPP_LOGD("deleteUser", "username=%s api_key=%s", username->c_str(), api_key->c_str())
    return m_service->deleteUser(userId, username);
  }

};  // class UserController

#include OATPP_CODEGEN_END(ApiController)
