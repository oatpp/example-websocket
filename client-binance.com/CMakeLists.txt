cmake_minimum_required(VERSION 3.1)

set(project_name ws-client-binance.com) ## rename your project here

project(${project_name})

set(CMAKE_CXX_STANDARD 11)

include_directories(src)

add_library(${project_name}-lib
        src/WSListener.cpp
        src/WSListener.hpp
        src/Model.hpp
        src/WSEventListener.hpp
        src/AggregateTradesListener.hpp
        src/TradesListener.hpp
        src/KlineCandlestickListener.hpp
)

## link libs

include(FindPkgConfig)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../cmake/module") # <-- use Findmbedtls.cmake in /cmake/module folder

find_package(mbedtls 2.16.0 REQUIRED)

find_package(oatpp              1.3.0 REQUIRED)
find_package(oatpp-websocket    1.3.0 REQUIRED)
find_package(oatpp-mbedtls      1.3.0 REQUIRED)

target_link_libraries(${project_name}-lib
        ## oatpp
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-test
        PUBLIC oatpp::oatpp-websocket
        PUBLIC oatpp::oatpp-mbedtls

        ## mbedtls
        PUBLIC mbedtls::TLS
        PUBLIC mbedtls::X509
        PUBLIC mbedtls::Crypto
)

#################################################################
## link mbedtls

link_directories(
        /usr/local/lib/
)

#################################################################

## add executables

add_executable(${project_name}-exe
        src/App.cpp
)
target_link_libraries(${project_name}-exe ${project_name}-lib)
add_dependencies(${project_name}-exe ${project_name}-lib)

add_executable(${project_name}-test
        test/tests.cpp
        test/WSTest.cpp
        test/WSTest.hpp
)
target_link_libraries(${project_name}-test ${project_name}-lib)
add_dependencies(${project_name}-test ${project_name}-lib)

set_target_properties(${project_name}-lib ${project_name}-exe ${project_name}-test PROPERTIES
        CXX_STANDARD 11
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
        LINKER_LANGUAGE CXX
)

enable_testing()
add_test(tests ${project_name}-test)
