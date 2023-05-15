#!/bin/sh

echo "Testing pet endpoints... "
. utility/pet_test.sh

echo "Testing store endpoints... "
. utility/store_test.sh

echo "Testing user endpoints... "
. utility/user_test.sh

echo All tests passed
