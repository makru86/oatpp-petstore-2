#pragma once

#include "dto/OrderDTO.hpp"
#include "oatpp/web/protocol/http/Http.hpp"

class StoreService
{
protected:
  typedef oatpp::web::protocol::http::outgoing::Response OutgoingResponse;
  typedef oatpp::web::protocol::http::outgoing::ResponseFactory ResponseFactory;
  typedef oatpp::web::protocol::http::Status Status;

public:
  virtual oatpp::UnorderedFields<oatpp::Int32> getInventory(const oatpp::String& userId) = 0;
  virtual oatpp::Object<OrderDTO> placeOrder(const oatpp::Object<OrderDTO>& order) = 0;
  virtual oatpp::Object<OrderDTO> getOrderById(const oatpp::Int64& orderId) = 0;
  virtual std::shared_ptr<OutgoingResponse> deleteOrder(const oatpp::String& orderId) = 0;
};

class MyStoreService : public StoreService
{
  static constexpr const char* TAG = "MyStoreService";

public:
  oatpp::UnorderedFields<oatpp::Int32> getInventory(const oatpp::String& userId) override
  {
    OATPP_LOGD(TAG, "getInventory userId='%s'", userId->c_str())
    return oatpp::UnorderedFields<oatpp::Int32>::createShared();
  }

  oatpp::Object<OrderDTO> placeOrder(const oatpp::Object<OrderDTO>& order) override
  {
    return OrderDTO::createShared();
  }

  oatpp::Object<OrderDTO> getOrderById(const oatpp::Int64& orderId) override
  {
    OATPP_LOGD(TAG, "getOrderById orderId='%d'", orderId.getValue(0))
    return OrderDTO::createShared();
  }

  std::shared_ptr<OutgoingResponse> deleteOrder(const oatpp::String& orderId) override
  {
    return ResponseFactory::createResponse(Status::CODE_200);
  }
};
