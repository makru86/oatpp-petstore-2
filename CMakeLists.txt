cmake_minimum_required(VERSION 3.1)

set(project_name "OpenAPI-Petstore")

project(${project_name})

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE LIB_FILES
        src/*.cpp
        src/*.hpp
        )
add_library(${project_name}-lib ${LIB_FILES})

## link libs

find_package(oatpp 1.3.0 REQUIRED)

target_link_libraries(${project_name}-lib
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-test
)
# FIXME for Swagger-UI link with oatpp::oatpp-swagger

target_include_directories(${project_name}-lib PUBLIC src)

## add executables

add_executable(${project_name}-exe
        src/App.cpp
        test/app/MyApiTestClient.hpp)
target_link_libraries(${project_name}-exe ${project_name}-lib)
add_dependencies(${project_name}-exe ${project_name}-lib)

file(GLOB_RECURSE TEST_FILES
        test/*.cpp
        test/*.hpp
        )
add_executable(${project_name}-test ${TEST_FILES})

target_link_libraries(${project_name}-test ${project_name}-lib)
target_include_directories(${project_name}-test PRIVATE test)
add_dependencies(${project_name}-test ${project_name}-lib)

set_target_properties(${project_name}-lib ${project_name}-exe ${project_name}-test PROPERTIES
        CXX_STANDARD 11
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
)

enable_testing()
add_test(project-tests ${project_name}-test)
