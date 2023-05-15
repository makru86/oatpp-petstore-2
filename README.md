# oatpp-petstore-2
# WORK IN PROGRESS

Project will be used as a template to build new openapi-generator
'cpp-oatpp-server'. Server API specified in
[api/petstore.yaml](./api/petstore.yaml).

[Oatpp simple](https://oatpp.io/docs/simple-vs-async/) controllers used in
implemetation.

## Links
- [Oatpp ticket](https://github.com/oatpp/oatpp/issues/331)
- Old [pull request](https://github.com/OpenAPITools/openapi-generator/pull/7903) for `cpp-oatpp-server` in openapi-generator

## Curl test script

After this project is build, [./utility/test.sh](./utility/test.sh) could be
used to start the server and test it with curl.

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

Other endpoints:

- "POST", "/pet"
- "PUT", "/pet"
- "GET", "/pet/findByStatus"
- "GET", "/pet/findByTags"
- "POST", "/pet/{petId}"
- "POST", "/pet/{petId}/uploadImage"
- "POST", "/store/order"
- "GET", "/store/order/{orderId}"
- "DELETE", "/store/order/{orderId}"
- "GET", "/user/login"
- "GET", "/user/{username}"

See more:

- [Oat++ Website](https://oatpp.io/)
- [Oat++ Github Repository](https://github.com/oatpp/oatpp)
- [Get Started](https://oatpp.io/docs/start)

## Overview

### Project layout

```
|- CMakeLists.txt                        // projects CMakeLists.txt
|- src/
|    |
|    |- controller/                      // Folder containing MyController where all endpoints are declared
|    |- dto/                             // DTOs are declared here
|    |- AppComponent.hpp                 // Service config
|    |- App.cpp                          // main() is here
|
|- test/                                 // test folder
|- utility/install-oatpp-modules.sh      // utility script to install required oatpp-modules.  
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
