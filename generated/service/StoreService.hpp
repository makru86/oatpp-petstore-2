#pragma once

#include "generated/dto/OrderDTO.hpp"
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

