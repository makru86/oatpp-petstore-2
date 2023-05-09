cmake_minimum_required(VERSION 3.1)

set(project_name my-project) ## rename your project here

project(${project_name})

set(CMAKE_CXX_STANDARD 11)

add_library(${project_name}-lib
        src/AppComponent.hpp
        src/controller/MyController.cpp
        src/controller/MyController.hpp
        src/controller/UserController.hpp
        src/dto/ApiResponseDTO.hpp
        src/dto/CategoryDTO.hpp
        src/dto/DTOs.hpp
        src/dto/OrderDTO.hpp
        src/dto/PetDTO.hpp
        src/dto/TagDTO.hpp
        src/dto/UserArrayDTO.hpp
        src/dto/UserDTO.hpp
)

## link libs

find_package(oatpp 1.3.0 REQUIRED)

target_link_libraries(${project_name}-lib
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-test
)

target_include_directories(${project_name}-lib PUBLIC src)

## add executables

add_executable(${project_name}-exe
        src/App.cpp
        test/app/MyApiTestClient.hpp)
target_link_libraries(${project_name}-exe ${project_name}-lib)
add_dependencies(${project_name}-exe ${project_name}-lib)

add_executable(${project_name}-test
        test/tests.cpp
        test/app/MyApiTestClient.hpp
        test/app/TestComponent.hpp
        test/controller/MyControllerTest.cpp
        test/controller/MyControllerTest.hpp
        test/controller/UserControllerTest.cpp
        test/controller/UserControllerTest.hpp
        test/dto/ApiResponseDTOTest.cpp
        test/dto/ApiResponseDTOTest.hpp
        test/dto/CategoryDTOTest.cpp
        test/dto/CategoryDTOTest.hpp
        test/dto/OrderDTOTest.cpp
        test/dto/OrderDTOTest.hpp
        test/dto/PetDTOTest.cpp
        test/dto/PetDTOTest.hpp
        test/dto/TagDTOTest.cpp
        test/dto/TagDTOTest.hpp
        test/dto/UserDTOTest.cpp
        test/dto/UserDTOTest.hpp
)

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
