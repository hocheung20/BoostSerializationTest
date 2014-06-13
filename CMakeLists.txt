cmake_minimum_required(VERSION 2.8)
project(BoostSerializationTest)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")

find_package(Boost REQUIRED serialization)

include_directories(${Boost_INCLUDE_DIR})

set(SRCS
    main.cpp
)

add_executable(BoostSerializationTest ${SRCS})
target_link_libraries(BoostSerializationTest ${Boost_LIBRARIES})