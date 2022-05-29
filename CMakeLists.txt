cmake_minimum_required(VERSION 3.12.0)
project(SimpleATM)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

include_directories(
        ${PROJECT_SOURCE_DIR}/include
)

add_library(${PROJECT_NAME} SHARED
        src/account.cpp
        src/atm.cpp
        src/bank.cpp
        src/card.cpp
        include/account.h
        include/atm.h
        include/bank.h
        include/card.h
)

add_executable(${PROJECT_NAME}_example main.cpp)
target_link_libraries(${PROJECT_NAME}_example ${PROJECT_NAME})
