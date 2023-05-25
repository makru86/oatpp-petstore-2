#pragma once

#include "dto/UserDto.hpp"
#include "oatpp/web/protocol/http/Http.hpp"

class UserService
{
public:
  virtual std::shared_ptr<OutgoingResponse> createUser(const oatpp::String& userId,
                                                       const oatpp::Object<UserDto>& dto) = 0;
  virtual std::shared_ptr<oatpp::Vector<oatpp::Object<UserDTO>>> createUsersWithArrayInput(
      const oatpp::String& userId, const oatpp::Vector<oatpp::Object<UserDTO>>& dto) = 0;
  virtual std::shared_ptr<oatpp::Vector<oatpp::Object<UserDTO>>> createUsersWithListInput(
      const oatpp::String& userId, const oatpp::Vector<oatpp::Object<UserDTO>>& dto) = 0;
  virtual std::shared_ptr<OutgoingResponse> loginUser(const oatpp::String& username,
                                                      const oatpp::String& password) = 0;
  virtual std::shared_ptr<oatpp::Object<UserDTO>> getUserByName(const oatpp::String& username) = 0;
  virtual std::shared_ptr<oatpp::Object<UserDTO>> updateUser(const oatpp::String& userId,
                                                             const oatpp::String& username,
                                                             const oatpp::Object<User>& user) = 0;
  virtual std::shared_ptr<OutgoingResponse> deleteUser(const oatpp::String& userId,
                                                       const oatpp::String& username) = 0;
  virtual std::shared_ptr<OutgoingResponse> logoutUser(const oatpp::String& userId) = 0;
};
