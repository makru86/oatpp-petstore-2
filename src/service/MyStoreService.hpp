#include "generated/service/StoreService.hpp"

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
