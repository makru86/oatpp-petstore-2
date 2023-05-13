#pragma once

#include "dto/OrderDTO.hpp"
#include "oatpp/core/async/Coroutine.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

class StoreController : public oatpp::web::server::api::ApiController
{
public:
  explicit StoreController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper)
  {
  }

  ENDPOINT_INFO(getInventory)
  {
    info->summary = "Returns pet inventories by status";
    info->description = "Returns a map of status codes to quantities";
    //    info->addResponse<Object<oatpp::UnorderedFields<Int32>>>(Status::CODE_200,
    //    "application/json");
    info->addSecurityRequirement("api_key");
  }
  ENDPOINT("GET", "store/inventory", getInventory)
  {
    OATPP_LOGD("getInventory", "")
    // TODO Add your implementation here.
    return createDtoResponse(Status::CODE_200, oatpp::UnorderedFields<Int32>::createShared());
  }

  // Place an order
  ENDPOINT_INFO(placeOrder)
  {
    // general information about the endpoint
    info->summary = "Place an order for a pet";
    info->addConsumes<Object<OrderDTO>>("application/json");
    info->addResponse<Object<OrderDTO>>(Status::CODE_200, "application/json");
    info->addResponse<String>(Status::CODE_400, "text/plain");
  }
  ENDPOINT("POST", "/store/order", placeOrder, BODY_DTO(Object<OrderDTO>, orderDto))
  {
    // implementation of the endpoint
    OATPP_LOGD("placeOrder", "")
    // TODO Add your implementation here.
    return createDtoResponse(Status::CODE_200, orderDto);
  }

  // Get an order by ID
  ENDPOINT_INFO(getOrderById)
  {
    info->summary = "Find purchase order by ID";
    info->addResponse<Object<OrderDTO>>(Status::CODE_200, "application/json");
    info->addResponse<String>(Status::CODE_400, "text/plain");
    info->addResponse<String>(Status::CODE_404, "text/plain");
    info->pathParams.add<Int64>("orderId");
  }
  ENDPOINT("GET", "/store/order/{orderId}", getOrderById, PATH(Int64, orderId))
  {
    auto dto = Object<OrderDTO>::createShared();
    OATPP_LOGD("getOrderById", "")
    // TODO Add your implementation here.
    return createDtoResponse(Status::CODE_200, dto);
  }

  // Delete an order by ID
  ENDPOINT_INFO(deleteOrder)
  {
    info->summary = "Delete purchase order by ID";
    info->addResponse<String>(Status::CODE_400, "text/plain");
    info->addResponse<String>(Status::CODE_404, "text/plain");
    info->pathParams.add<Int64>("orderId");
  }
  ENDPOINT("DELETE", "/store/order/{orderId}", deleteOrder, PATH(String, orderId))
  {
    OATPP_LOGD("deleteOrder", "")
    // TODO Add your implementation here.
    return createResponse(Status::CODE_200, "OK");
  }

};  // class StoreController

#include OATPP_CODEGEN_END(ApiController)
