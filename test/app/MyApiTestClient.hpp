#ifndef MyApiTestClient_hpp
#define MyApiTestClient_hpp

#include "dto/UserDTO.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/web/client/ApiClient.hpp"

/* Begin Api Client code generation */
#include OATPP_CODEGEN_BEGIN(ApiClient)

/**
 * Test API client.
 * Use this client to call application APIs.
 */
class MyApiTestClient : public oatpp::web::client::ApiClient
{
  API_CLIENT_INIT(MyApiTestClient)

  API_CALL("GET", "/hello", getHello)

  API_CALL("GET", "/", getRoot)

  API_CALL("POST", "/user", createUser, BODY_DTO(Object<UserDTO>, dto))

  API_CALL("POST", "/user/createWithArray", createUsersWithArrayInput,
           BODY_DTO(oatpp::Vector<Object<UserDTO>>, dto))

  API_CALL("POST", "/user/createWithList", createUsersWithListInput,
           BODY_DTO(oatpp::Vector<Object<UserDTO>>, dto))

  API_CALL("GET", "/user/{username}", getUserByName, PATH(String, username))

  API_CALL("PUT", "/user/{username}", updateUser, PATH(String, username),
           BODY_DTO(Object<UserDTO>, dto))

  API_CALL("DELETE", "/user/{username}", deleteUser, PATH(String, username))

  API_CALL("GET", "/user/login", loginUser, QUERY(String, username), QUERY(String, password))

  API_CALL("GET", "/user/logout", logoutUser)
};

/* End Api Client code generation */
#include OATPP_CODEGEN_END(ApiClient)

#endif  // MyApiTestClient_hpp
