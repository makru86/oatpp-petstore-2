#include "generated/service/UserService.hpp"

class MyUserService : public UserService
{
public:
  std::shared_ptr<OutgoingResponse> createUser(const oatpp::String& userId,
                                               const oatpp::Object<UserDTO>& dto) override
  {
    return ResponseFactory::createResponse(Status::CODE_200);
  }

  oatpp::Vector<oatpp::Object<UserDTO>> createUsersWithArrayInput(
      const oatpp::String& userId, const oatpp::Vector<oatpp::Object<UserDTO>>& dto) override
  {
    return {};
  }

  oatpp::Vector<oatpp::Object<UserDTO>> createUsersWithListInput(
      const oatpp::String& userId, const oatpp::Vector<oatpp::Object<UserDTO>>& dto) override
  {
    return {};
  }

  std::shared_ptr<OutgoingResponse> loginUser(const oatpp::String& username,
                                              const oatpp::String& password) override
  {
    auto response = ResponseFactory::createResponse(Status::CODE_200);
    response->putHeader("Set-Cookie", "AUTH_KEY=abcde12345; Path=/; HttpOnly");
    response->putHeader("X-Rate-Limit", std::to_string(60));
    response->putHeader("X-Expires-After", std::to_string(3600));
    return response;
  }

  std::shared_ptr<OutgoingResponse> logoutUser(const oatpp::String& userId) override
  {
    return ResponseFactory::createResponse(Status::CODE_200);
  }

  oatpp::Object<UserDTO> getUserByName(const oatpp::String& username) override { return {}; }

  oatpp::Object<UserDTO> updateUser(const oatpp::String& userId, const oatpp::String& username,
                                    const oatpp::Object<UserDTO>& user) override
  {
    return {};
  }

  std::shared_ptr<OutgoingResponse> deleteUser(const oatpp::String& userId,
                                               const oatpp::String& username) override
  {
    return ResponseFactory::createResponse(Status::CODE_200);
  }
};
