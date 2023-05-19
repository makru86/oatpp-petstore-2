#!/bin/bash

CURL_ARGS=$@
CURL_ARGS="$CURL_ARGS --fail"
echo
echo "Testing pet endpoints... "

BOLD='\033[1;33m'
NC='\033[0m' # No Color

function test_name {
    echo -en "   ${BOLD}$1${NC} "
}

test_name "addPet:"
curl $CURL_ARGS \
    -X POST http://localhost:8000/pet \
    -H "Authorization: Bearer 870bbe18-0969-47b2-9b31-ddf1e6aa9e55" \
    -H "Content-Type: application/json" \
    -d '{"name":"test","photoUrls":["photoUrl","photoUrl"]}' \
    && echo || exit 1

test_name "updatePet:"
curl $CURL_ARGS \
    -X PUT http://localhost:8000/pet \
    -H "Authorization: Bearer 870bbe18-0969-47b2-9b31-ddf1e6aa9e55" \
    -H "Content-Type: application/json" \
    -d '{"name":"test","photoUrls":["photoUrl","photoUrl"]}' \
    && echo || exit 1

test_name "findPetsByStatus:"
curl $CURL_ARGS \
    -X GET http://localhost:8000/pet/findByStatus\?status=available \
    -H "Authorization: Bearer 870bbe18-0969-47b2-9b31-ddf1e6aa9e55" \
    -H "Content-Type: application/json" \
    -d '[{"petname":"test"}]' \
    && echo || exit 1

test_name "findPetsByTags:"
curl $CURL_ARGS \
    -X GET http://localhost:8000/pet/findByTags\?tags=test \
    -H "Authorization: Bearer 870bbe18-0969-47b2-9b31-ddf1e6aa9e55" \
    -H "Content-Type: application/json" \
    -d '{"petname":"test"}' \
    && echo || exit 1

test_name "getPetById:"
curl $CURL_ARGS \
    -X GET http://localhost:8000/pet/123 \
    -H "api_key: special-key" \
    && echo || exit 1

# test_name "updatePetWithForm:"
# curl $CURL_ARGS \
#   -H "Authorization: Bearer 870bbe18-0969-47b2-9b31-ddf1e6aa9e55" \
#   -X POST http://localhost:8000/pet/123 \
#     && echo || exit 1

test_name "deletePet:"
curl $CURL_ARGS \
    -X DELETE http://localhost:8000/pet/123 \
    -H "Authorization: Bearer 870bbe18-0969-47b2-9b31-ddf1e6aa9e55" \
    -H "api_key: special-key" \
    && echo || exit 1

test_name "uploadFile:"
curl $CURL_ARGS \
    http://localhost:8000/pet/123/uploadImage \
    -H "Authorization: Bearer 870bbe18-0969-47b2-9b31-ddf1e6aa9e55" \
    -F additionalMetadata=string \
    -F file=\@/bin/sh \
    -H "Expect:" \
    && echo #|| exit 1

echo
echo "Testing store endpoints... "

test_name "getInventory:"
curl $CURL_ARGS \
    -X GET http://localhost:8000/store/inventory \
    -H "api_key: special-key" \
    && echo || exit 1

test_name "placeOrder:"
curl $CURL_ARGS \
    -X POST http://localhost:8000/store/order \
    -H "Content-Type: application/json" \
    -d '{"id":123,"petId":123,"quantity":123,"shipDate":"2019-01-01T00:00:00.000Z","status":"placed","complete":true}' \
    && echo || exit 1

test_name "getOrderById:"
curl $CURL_ARGS \
    -X GET http://localhost:8000/store/order/123 \
    && echo || exit 1

test_name "deleteOrder:"
curl $CURL_ARGS \
    -X DELETE http://localhost:8000/store/order/123 \
    && echo || exit 1

echo
echo "Testing user endpoints... "

test_name "createUser:"
curl $CURL_ARGS \
    -X POST http://localhost:8000/user \
    -H "api_key: special-key" \
    -H "Content-Type: application/json" \
    -d '{"username":"test"}' \
    && echo || exit 1

test_name "createUsersWithArrayInput:"
curl $CURL_ARGS \
    -X POST http://localhost:8000/user/createWithArray \
    -H "api_key: special-key" \
    -H "Content-Type: application/json" \
    -d '[{"username":"test1"},{"username":"test2"}]' \
    && echo || exit 1

test_name "createUsersWithListInput:"
curl $CURL_ARGS \
    -X POST http://localhost:8000/user/createWithList \
    -H "api_key: special-key" \
    -H "Content-Type: application/json" \
    -d '[{"username":"test"}]' \
    && echo || exit 1

test_name "loginUser:"
curl $CURL_ARGS \
    -X GET http://localhost:8000/user/login\?username=test\&password=test \
    && echo || exit 1

test_name "logoutUser:"
curl $CURL_ARGS \
    -X GET http://localhost:8000/user/logout \
    -H "api_key: special-key" \
    && echo || exit 1

test_name "getUserByName:"
curl $CURL_ARGS \
    -X GET http://localhost:8000/user/test \
    && echo || exit 1

test_name "updateUser:"
curl $CURL_ARGS \
    -X PUT http://localhost:8000/user/test \
    -H "api_key: special-key" \
    -H "Content-Type: application/json" \
    -d '{"username":"test"}' \
    && echo || exit 1

test_name "deleteUser:"
curl $CURL_ARGS \
    -X DELETE http://localhost:8000/user/test \
    -H "api_key: special-key" \
    && echo || exit 1
echo

echo All tests passed
