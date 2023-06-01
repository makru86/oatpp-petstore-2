#pragma once

#include "dto/DTOs.hpp"
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

  API_CALL("POST", "/pet", addPet, AUTHORIZATION(String, authorization, "Bearer"),
           BODY_DTO(Object<PetDTO>, dto))

  API_CALL("PUT", "/pet", updatePet, AUTHORIZATION(String, authorization, "Bearer"),
           BODY_DTO(Object<PetDTO>, dto))

  API_CALL("GET", "/pet/findByStatus", findPetsByStatus,
           AUTHORIZATION(String, authorization, "Bearer"), QUERY(String, status))

  API_CALL("GET", "/pet/findByTags", findPetsByTags, AUTHORIZATION(String, authorization, "Bearer"),
           QUERY(String, tags))

  API_CALL("GET", "/pet/{petId}", getPetById, HEADER(String, apiKey, "api_key"), PATH(Int64, petId))

  API_CALL("POST", "/pet/{petId}", updatePetWithForm,
           AUTHORIZATION(String, authorization, "Bearer"), PATH(Int64, petId))

  // API_CALL("POST", "/pet/{petId}/uploadImage", uploadFile, AUTHORIZATION(String, authorization,
  // "Bearer"),PATH_PARAM(petId, "integer"), BODY_DTO(Object<UploadImageDTO>, dto))

  API_CALL("DELETE", "/pet/{petId}", deletePet, AUTHORIZATION(String, authorization, "Bearer"),
           PATH(Int64, petId))

  API_CALL("GET", "/store/inventory", getInventory, HEADER(String, apiKey, "api_key"))

  API_CALL("POST", "/store/order", placeOrder, BODY_DTO(Object<OrderDTO>, dto))

  API_CALL("GET", "/store/order/{orderId}", getOrderById, PATH(Int64, orderId))

  API_CALL("DELETE", "/store/order/{orderId}", deleteOrder, PATH(String, orderId))

  API_CALL("POST", "/user", createUser, HEADER(String, apiKey, "api_key"),
           BODY_DTO(Object<UserDTO>, dto))

  API_CALL("POST", "/user/createWithArray", createUsersWithArrayInput,
           HEADER(String, apiKey, "api_key"), BODY_DTO(oatpp::Vector<Object<UserDTO>>, dto))

  API_CALL("POST", "/user/createWithList", createUsersWithListInput,
           HEADER(String, apiKey, "api_key"), BODY_DTO(oatpp::Vector<Object<UserDTO>>, dto))

  API_CALL("GET", "/user/{username}", getUserByName, PATH(String, username))

  API_CALL("PUT", "/user/{username}", updateUser, HEADER(String, apiKey, "api_key"),
           PATH(String, username), BODY_DTO(Object<UserDTO>, dto))

  API_CALL("DELETE", "/user/{username}", deleteUser, HEADER(String, apiKey, "api_key"),
           PATH(String, username))

  API_CALL("GET", "/user/login", loginUser, QUERY(String, username), QUERY(String, password))

  API_CALL("GET", "/user/logout", logoutUser, HEADER(String, apiKey, "api_key"))
};

/* End Api Client code generation */
#include OATPP_CODEGEN_END(ApiClient)
