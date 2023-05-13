#!/bin/sh

echo -n "operationId addPet: "
curl --fail -X POST http://localhost:8000/pet \
    -H "Content-Type: application/json" \
    -d '{"name":"test","photoUrls":["photoUrl","photoUrl"]}' \
    && echo || exit 1

echo -n "operationId updatePet: "
curl --fail -X PUT http://localhost:8000/pet \
    -H "Content-Type: application/json" \
    -d '{"name":"test","photoUrls":["photoUrl","photoUrl"]}' \
    && echo || exit 1

echo -n "operationId findPetsByStatus: "
curl --fail -X GET http://localhost:8000/pet/findByStatus\?status=available \
    -H "Content-Type: application/json" \
    -d '[{"petname":"test"}]' \
    && echo || exit 1

echo -n "operationId findPetsByTags: "
curl --fail -X GET http://localhost:8000/pet/findByTags\?tags=test \
    -H "Content-Type: application/json" \
    -d '{"petname":"test"}' \
    && echo || exit 1

echo -n "operationId getPetById: "
curl --fail -X GET http://localhost:8000/pet/123 \
    -H "Authorization: special-key" \
    && echo || exit 1

# echo -n "operationId updatePetWithForm: "
# curl --fail -X POST http://localhost:8000/pet/123 \
#     && echo || exit 1

echo -n "operationId deletePet: "
curl --fail -X DELETE http://localhost:8000/pet/123 \
    && echo || exit 1

echo -n "operationId uploadFile: "
curl --verbose --fail -X POST http://localhost:8000/pet/123/uploadImage \
    -F additionalMetadata=value1 -F file=@/bin/sh \
    && echo || exit 1
