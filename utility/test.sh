#!/bin/sh

CURL_ARG=$1
echo
echo "Testing pet endpoints... "

echo -n "   addPet: "
curl $CURL_ARG --fail \
    -X POST http://localhost:8000/pet \
    -H "Authorization: Bearer 870bbe18-0969-47b2-9b31-ddf1e6aa9e55" \
    -H "Content-Type: application/json" \
    -d '{"name":"test","photoUrls":["photoUrl","photoUrl"]}' \
    && echo || exit 1

echo -n "   updatePet: "
curl $CURL_ARG --fail \
    -X PUT http://localhost:8000/pet \
    -H "Content-Type: application/json" \
    -d '{"name":"test","photoUrls":["photoUrl","photoUrl"]}' \
    && echo || exit 1

echo -n "   findPetsByStatus: "
curl $CURL_ARG --fail \
    -X GET http://localhost:8000/pet/findByStatus\?status=available \
    -H "Content-Type: application/json" \
    -d '[{"petname":"test"}]' \
    && echo || exit 1

echo -n "   findPetsByTags: "
curl $CURL_ARG --fail \
    -X GET http://localhost:8000/pet/findByTags\?tags=test \
    -H "Content-Type: application/json" \
    -d '{"petname":"test"}' \
    && echo || exit 1

echo -n "   getPetById: "
curl $CURL_ARG --fail \
    -X GET http://localhost:8000/pet/123 \
    -H "api_key: special-key" \
    && echo || exit 1

# echo -n "   updatePetWithForm: "
# curl $CURL_ARG --fail \
    -X POST http://localhost:8000/pet/123 \
#     && echo || exit 1

echo -n "   deletePet: "
curl $CURL_ARG --fail \
    -X DELETE http://localhost:8000/pet/123 \
    -H "api_key: special-key" \
    && echo || exit 1

echo -n "   uploadFile: "
curl $CURL_ARG --fail \
    http://localhost:8000/pet/123/uploadImage \
    -F additionalMetadata=string \
    -F file=\@/bin/sh \
    -H "Expect:" \
    && echo #|| exit 1

echo
echo "Testing store endpoints... "

echo -n "   getInventory: "
curl $CURL_ARG --fail \
    -X GET http://localhost:8000/store/inventory \
    -H "api_key: special-key" \
    && echo || exit 1

echo -n "   placeOrder: "
curl $CURL_ARG --fail \
    -X POST http://localhost:8000/store/order \
    -H "Content-Type: application/json" \
    -d '{"id":123,"petId":123,"quantity":123,"shipDate":"2019-01-01T00:00:00.000Z","status":"placed","complete":true}' \
    && echo || exit 1

echo -n "   getOrderById: "
curl $CURL_ARG --fail \
    -X GET http://localhost:8000/store/order/123 \
    && echo || exit 1

echo -n "   deleteOrder: "
curl $CURL_ARG --fail \
    -X DELETE http://localhost:8000/store/order/123 \
    && echo || exit 1

echo
echo "Testing user endpoints... "

echo -n "   createUser: "
curl $CURL_ARG --fail \
    -X POST http://localhost:8000/user \
    -H "api_key: special-key" \
    -H "Content-Type: application/json" \
    -d '{"username":"test"}' \
    && echo || exit 1

echo -n "   createUsersWithArrayInput: "
curl $CURL_ARG --fail \
    -X POST http://localhost:8000/user/createWithArray \
    -H "api_key: special-key" \
    -H "Content-Type: application/json" \
    -d '[{"username":"test1"},{"username":"test2"}]' \
    && echo || exit 1

echo -n "   createUsersWithListInput: "
curl $CURL_ARG --fail \
    -X POST http://localhost:8000/user/createWithList \
    -H "api_key: special-key" \
    -H "Content-Type: application/json" \
    -d '[{"username":"test"}]' \
    && echo || exit 1

echo -n "   loginUser: "
curl $CURL_ARG --verbose --fail \
    -X GET http://localhost:8000/user/login\?username=test\&password=test \
    2>&1 | grep -e '^>' \
    || exit 1

echo -n "   logoutUser: "
curl $CURL_ARG --fail \
    -X GET http://localhost:8000/user/logout \
    -H "api_key: special-key" \
    && echo || exit 1

echo -n "   getUserByName: "
curl $CURL_ARG --fail \
    -X GET http://localhost:8000/user/test \
    && echo || exit 1

echo -n "   updateUser: "
curl $CURL_ARG --fail \
    -X PUT http://localhost:8000/user/test \
    -H "api_key: special-key" \
    -H "Content-Type: application/json" \
    -d '{"username":"test"}' \
    && echo || exit 1

echo -n "   deleteUser: "
curl $CURL_ARG --fail \
    -X DELETE http://localhost:8000/user/test \
    -H "api_key: special-key" \
    && echo || exit 1
echo

echo All tests passed
