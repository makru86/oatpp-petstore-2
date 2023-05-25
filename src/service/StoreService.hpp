#pragma once

#include "dto/UserDto.hpp"
#include "oatpp/web/protocol/http/Http.hpp"

class StoreService
{
public:
  virtual std::shared_ptr<oatpp::UnorderedFields<Int32>> getInventory(
      const oatpp::String& userId) = 0;
  virtual std::shared_ptr<oatpp::Object<oatpp::OrderDTO>> placeOrder(
      const oatpp::Object<Order>& order) = 0;
  virtual std::shared_ptr<oatpp::Object<oatpp::OrderDTO>> getOrderById(
      const oatpp::Int64& orderId) = 0;
  virtual std::shared_ptr<OutgoingResponse> deleteOrder(const oatpp::String& orderId) = 0;
};
