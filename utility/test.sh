#!/bin/sh

nohup ./build/my-project-exe & serverPID=$! 
echo "Server started (pid $serverPID)"
echo "Starting tests..."
sleep 1

echo -n "Test createUser: "
curl -X POST http://localhost:8000/user \
    -H "api_key: special-key" \
    -H "Content-Type: application/json" \
    -d '{"username":"test"}' \
    && echo || exit 1

echo -n "Test createUsersWithArrayInput: "
curl -X POST http://localhost:8000/user/createWithArray \
    -H "api_key: special-key" \
    -H "Content-Type: application/json" \
    -d '[{"username":"test1"},{"username":"test2"}]' \
    && echo || exit 1

echo -n "Test createUsersWithListInput: "
curl -X POST http://localhost:8000/user/createWithList \
    -H "api_key: special-key" \
    -H "Content-Type: application/json" \
    -d '[{"username":"test"}]' \
    && echo || exit 1

echo -n "Test loginUser: "
curl -X GET http://localhost:8000/user/login\?username=test\&password=test \
    -H "Content-Type: application/json" \
    -d '{"username":"test"}' \
    && echo || exit 1

echo -n "Test logoutUser: "
curl -X GET http://localhost:8000/user/logout \
    -H "api_key: special-key" \
    && echo || exit 1

echo -n "Test getUserByName: "
curl -X GET http://localhost:8000/user/test \
    && echo || exit 1

echo -n "Test updateUser: "
curl -X PUT http://localhost:8000/user/test \
    -H "api_key: special-key" \
    -H "Content-Type: application/json" \
    -d '{"username":"test"}' \
    && echo || exit 1

echo -n "Test deleteUser: "
curl -X DELETE http://localhost:8000/user/test \
    -H "api_key: special-key" \
    && echo || exit 1
echo

echo Tests finished
kill $serverPID
echo Server killed

