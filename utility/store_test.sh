#!/bin/sh

echo -n "operationId getInventory: "
curl --fail -X GET http://localhost:8000/store/inventory \
    -H "api_key: special-key" \
    && echo || exit 1

echo -n "operationId placeOrder: "
curl --fail -X POST http://localhost:8000/store/order \
    -H "Content-Type: application/json" \
    -d '{"id":123,"petId":123,"quantity":123,"shipDate":"2019-01-01T00:00:00.000Z","status":"placed","complete":true}' \
    && echo || exit 1

echo -n "operationId getOrderById: "
curl --fail -X GET http://localhost:8000/store/order/123 \
    && echo || exit 1

echo -n "operationId deleteOrder: "
curl --fail -X DELETE http://localhost:8000/store/order/123 \
    && echo || exit 1
