#pragma once

#include "dto/OrderDTO.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/server/api/ApiController.hpp"
#include "service/StoreService.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

class StoreController : public oatpp::web::server::api::ApiController
{
  std::shared_ptr<StoreService> m_service;

public:
  explicit StoreController(std::shared_ptr<StoreService> storeService,
                           OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper), m_service(storeService)
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
  ENDPOINT("GET", "store/inventory", getInventory, BUNDLE(String, userId))
  {
    OATPP_LOGD("getInventory", "userId=%s", userId->c_str())
    oatpp::UnorderedFields<oatpp::Int32> responseDto = m_service->getInventory(userId);
    return createDtoResponse(Status::CODE_200, responseDto);
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
    OATPP_LOGD("placeOrder", "")
    auto responseDto = m_service->placeOrder(orderDto);
    return createDtoResponse(Status::CODE_200, responseDto);
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
    OATPP_LOGD("getOrderById", "")
    auto responseDto = m_service->getOrderById(orderId);
    return createDtoResponse(Status::CODE_200, responseDto);
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
    return m_service->deleteOrder(orderId);
  }

};  // class StoreController

#include OATPP_CODEGEN_END(ApiController)
