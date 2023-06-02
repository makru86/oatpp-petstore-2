cmake_minimum_required(VERSION 3.1)

set(project_name "OpenAPI-Petstore")

project(${project_name})

set(CMAKE_CXX_STANDARD 11)

find_package(oatpp 1.3.0 REQUIRED)

# OpenAPI generated library

file(GLOB_RECURSE GENERATED_LIB_FILES generated/*.cpp generated/*.hpp)
add_library(${project_name}-generated-lib ${GENERATED_LIB_FILES})
target_include_directories(${project_name}-generated-lib PUBLIC .)
target_link_libraries(${project_name}-generated-lib
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-test
        )

# User-defined Business-logic library

file(GLOB_RECURSE LIB_FILES src/*.cpp src/*.hpp)
add_library(${project_name}-lib ${LIB_FILES})
target_include_directories(${project_name}-lib PUBLIC src)
target_link_libraries(${project_name}-lib
        PUBLIC ${project_name}-generated-lib
        )

# Executable app

add_executable(${project_name}-exe src/App.cpp)
target_link_libraries(${project_name}-exe
        ${project_name}-generated-lib
        )

# To enable Oat++ Swagger-UI, Link with oatpp::oatpp-swagger
# More https://oatpp.io/docs/modules/oatpp-swagger/


# Tests

file(GLOB_RECURSE TEST_FILES test/*.cpp test/*.hpp)
add_executable(${project_name}-test ${TEST_FILES})
target_include_directories(${project_name}-test PRIVATE test)
target_link_libraries(${project_name}-test
        ${project_name}-generated-lib
        ${project_name}-lib
        )

enable_testing()
add_test(project-tests ${project_name}-test)

## set target properties

set_target_properties(
        ${project_name}-generated-lib
        ${project_name}-lib
        ${project_name}-exe
        ${project_name}-test
        PROPERTIES CXX_STANDARD 11 CXX_EXTENSIONS OFF CXX_STANDARD_REQUIRED ON
)

