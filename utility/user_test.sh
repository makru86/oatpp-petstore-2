#!/bin/sh

echo -n "operationId createUser: "
curl --fail -X POST http://localhost:8000/user \
    -H "api_key: special-key" \
    -H "Content-Type: application/json" \
    -d '{"username":"test"}' \
    && echo || exit 1

echo -n "operationId createUsersWithArrayInput: "
curl --fail -X POST http://localhost:8000/user/createWithArray \
    -H "api_key: special-key" \
    -H "Content-Type: application/json" \
    -d '[{"username":"test1"},{"username":"test2"}]' \
    && echo || exit 1

echo -n "operationId createUsersWithListInput: "
curl --fail -X POST http://localhost:8000/user/createWithList \
    -H "api_key: special-key" \
    -H "Content-Type: application/json" \
    -d '[{"username":"test"}]' \
    && echo || exit 1

echo -n "operationId loginUser: "
curl --fail -X GET http://localhost:8000/user/login\?username=test\&password=test \
    -H "Content-Type: application/json" \
    -d '{"username":"test"}' \
    && echo || exit 1

echo -n "operationId logoutUser: "
curl --fail -X GET http://localhost:8000/user/logout \
    -H "api_key: special-key" \
    && echo || exit 1

echo -n "operationId getUserByName: "
curl --fail -X GET http://localhost:8000/user/test \
    && echo || exit 1

echo -n "operationId updateUser: "
curl --fail -X PUT http://localhost:8000/user/test \
    -H "api_key: special-key" \
    -H "Content-Type: application/json" \
    -d '{"username":"test"}' \
    && echo || exit 1

echo -n "operationId deleteUser: "
curl --fail -X DELETE http://localhost:8000/user/test \
    -H "api_key: special-key" \
    && echo || exit 1
echo

