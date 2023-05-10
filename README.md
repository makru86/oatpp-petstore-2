# oatpp-petstore-2

[petstore API](api/petstore.yaml) implementation using [Oatpp
simple](https://oatpp.io/docs/simple-vs-async/) controllers.

## Links
- [Oatpp ticket](https://github.com/oatpp/oatpp/issues/331)
- [Old openapi-generator Pull request](https://github.com/OpenAPITools/openapi-generator/pull/7903)

## Curl test script

After project is build, [./utility/test.sh](./utility/test.sh) could be
used to start the server and test it with curl.

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
