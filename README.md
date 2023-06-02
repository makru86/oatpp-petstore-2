# WORK IN PROGRESS

- [Work in progress issue](https://github.com/oatpp/oatpp/issues/331)
- [Old pull request](https://github.com/OpenAPITools/openapi-generator/pull/7903) for `cpp-oatpp-server`

# Oat++ OpenAPI Petstore starter

This project extends [Oat++ starter](https://github.com/oatpp/oatpp-starter)
by adding DTOs, controllers, and API-Key and OAuth2 security schemes as
defined in OpenAPI [spec](api/petstore.yaml).

## Helpful projects

- [Petstore API example on Swagger](https://petstore.swagger.io)
- [Oat++ JWT auth example](https://github.com/oatpp/example-jwt)

## List of endpoints of OpenAPI Petstore

Endpoints with `apiKey` security:

- "GET", "/pet/{petId}"
- "DELETE", "/pet/{petId}"
- "GET", "/store/inventory"
- "POST", "/user"
- "POST", "/user/createWithArray"
- "POST", "/user/createWithList"
- "GET", "/user/logout"
- "PUT", "/user/{username}"
- "DELETE", "/user/{username}"

OAuth2 endpoints:

- "POST", "/pet"
- "PUT", "/pet"
- "GET", "/pet/findByStatus"
- "GET", "/pet/findByTags"
- "POST", "/pet/{petId}"
- "DELETE", "/pet/{petId}"
- "POST", "/pet/{petId}/uploadImage"

Anonymous endpoints:

- "POST", "/store/order"
- "GET", "/store/order/{orderId}"
- "DELETE", "/store/order/{orderId}"
- "GET", "/user/login"
- "GET", "/user/{username}"

# Oat++ starter

See more:

- [Oat++ Website](https://oatpp.io/)
- [Oat++ Github Repository](https://github.com/oatpp/oatpp)
- [Get Started](https://oatpp.io/docs/start)

## Overview

### Project layout

```
|- CMakeLists.txt                        // projects CMakeLists.txt
|- generated/
|    |
|    |- controller/                      // Folder containing controllers where all endpoints are declared
|    |- dto/                             // DTOs are declared here
|    |- service/                         // Service interfaces
|
|- src/
|    |
|    |- service/                         // Service imlementations
|    |- AppComponent.hpp                 // Service config
|    |- App.cpp                          // main() is here
|
|- test/                                 // test folder
|
|- utility/
|    |
|    |- install-oatpp-modules.sh         // utility script to install required oatpp-modules
|    |- test.sh                          // curl tests suite
```

---

### Build and Run

#### Using CMake

**Requires**

- `oatpp` module installed. You may run `utility/install-oatpp-modules.sh`
script to install required oatpp modules.

```
$ mkdir build && cd build
$ cmake ..
$ make
$ ./my-project-exe  # - run application.

```

#### In Docker

```
$ docker build -t oatpp-starter .
$ docker run -p 8000:8000 -t oatpp-starter
```
