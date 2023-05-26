#pragma once

#include "dto/PetDTO.hpp"
#include "oatpp/core/data/stream/Stream.hpp"
#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/web/protocol/http/outgoing/ResponseFactory.hpp"

class PetService
{
protected:
  typedef oatpp::web::protocol::http::outgoing::Response OutgoingResponse;
  typedef oatpp::web::protocol::http::outgoing::ResponseFactory ResponseFactory;
  typedef oatpp::web::protocol::http::Status Status;

public:
  virtual oatpp::Object<PetDTO> addPet(const oatpp::String& userId,
                                       const oatpp::Object<PetDTO>& pet) = 0;
  virtual oatpp::Object<PetDTO> updatePet(const oatpp::String& userId,
                                          const oatpp::Object<PetDTO>& pet) = 0;
  virtual oatpp::Vector<oatpp::Object<PetDTO>> findPetsByStatus(const oatpp::String& userId,
                                                                const oatpp::String& status) = 0;
  virtual oatpp::Vector<oatpp::Object<PetDTO>> findPetsByTags(const oatpp::String& userId,
                                                              const oatpp::String& tags) = 0;
  virtual oatpp::Object<PetDTO> getPetById(const oatpp::String& userId,
                                           const oatpp::Int64& petId) = 0;
  //  virtual std::shared_ptr<OutgoingResponse> updatePetWithForm(const oatpp::String& userId, const
  //  oatpp::Int64& petId, const oatpp::Object<PetForm>& form) = 0;
  virtual std::shared_ptr<OutgoingResponse> deletePet(const oatpp::String& userId,
                                                      const oatpp::Int64& petId) = 0;
  virtual oatpp::Object<ApiResponseDTO> uploadFile(
      const oatpp::String& userId, const oatpp::Int64& petId,
      const oatpp::String& additionalMetadata,
      std::shared_ptr<oatpp::data::stream::InputStream> file) = 0;
};

class MyPetService : public PetService
{
private:
  const oatpp::String TAG = "MyPetService";

public:
  oatpp::Object<PetDTO> addPet(const oatpp::String& userId,
                               const oatpp::Object<PetDTO>& pet) override
  {
    OATPP_LOGD(TAG, "addPet");
    return {};
  }

  oatpp::Object<PetDTO> updatePet(const oatpp::String& userId,
                                  const oatpp::Object<PetDTO>& pet) override
  {
    return {};
  }

  oatpp::Vector<oatpp::Object<PetDTO>> findPetsByStatus(const oatpp::String& userId,
                                                        const oatpp::String& status) override
  {
    return {};
  }

  oatpp::Vector<oatpp::Object<PetDTO>> findPetsByTags(const oatpp::String& userId,
                                                      const oatpp::String& tags) override
  {
    return {};
  }
  oatpp::Object<PetDTO> getPetById(const oatpp::String& userId, const oatpp::Int64& petId) override
  {
    return {};
  }
  //   std::shared_ptr<OutgoingResponse> updatePetWithForm(const oatpp::String& userId, const
  //  oatpp::Int64& petId, const oatpp::Object<PetForm>& form) override{}
  std::shared_ptr<OutgoingResponse> deletePet(const oatpp::String& userId,
                                              const oatpp::Int64& petId) override
  {
    return ResponseFactory::createResponse(Status::CODE_200);
  }

  oatpp::Object<ApiResponseDTO> uploadFile(
      const oatpp::String& userId, const oatpp::Int64& petId,
      const oatpp::String& additionalMetadata,
      std::shared_ptr<oatpp::data::stream::InputStream> file) override
  {
    return {};
  }
};
