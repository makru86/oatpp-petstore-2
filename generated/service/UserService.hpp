#pragma once

#include "generated/dto/UserDTO.hpp"
#include "oatpp/web/protocol/http/Http.hpp"

class UserService
{
protected:
  typedef oatpp::web::protocol::http::outgoing::Response OutgoingResponse;
  typedef oatpp::web::protocol::http::outgoing::ResponseFactory ResponseFactory;
  typedef oatpp::web::protocol::http::Status Status;

public:
  virtual std::shared_ptr<OutgoingResponse> createUser(const oatpp::String& userId,
                                                       const oatpp::Object<UserDTO>& dto) = 0;
  virtual oatpp::Vector<oatpp::Object<UserDTO>> createUsersWithArrayInput(
      const oatpp::String& userId, const oatpp::Vector<oatpp::Object<UserDTO>>& dto) = 0;
  virtual oatpp::Vector<oatpp::Object<UserDTO>> createUsersWithListInput(
      const oatpp::String& userId, const oatpp::Vector<oatpp::Object<UserDTO>>& dto) = 0;
  virtual std::shared_ptr<OutgoingResponse> loginUser(const oatpp::String& username,
                                                      const oatpp::String& password) = 0;
  virtual oatpp::Object<UserDTO> getUserByName(const oatpp::String& username) = 0;
  virtual oatpp::Object<UserDTO> updateUser(const oatpp::String& userId,
                                            const oatpp::String& username,
                                            const oatpp::Object<UserDTO>& user) = 0;
  virtual std::shared_ptr<OutgoingResponse> deleteUser(const oatpp::String& userId,
                                                       const oatpp::String& username) = 0;
  virtual std::shared_ptr<OutgoingResponse> logoutUser(const oatpp::String& userId) = 0;
};

