#!/bin/sh

pkill my-project-exe
nohup ./build/my-project-exe & serverPID=$!
echo "Server started (pid $serverPID)"
sleep 1

echo "Testing pet endpoints... "
. utility/pet_test.sh

echo "Testing store endpoints... "
. utility/store_test.sh

echo "Testing user endpoints... "
. utility/user_test.sh

echo All tests passed
kill $serverPID
echo Server killed
sleep 1
