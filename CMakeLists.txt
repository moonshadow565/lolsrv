cmake_minimum_required(VERSION 3.5)
project(lolsrv LANGUAGES CXX)

if(WIN32)
    if(MSVC)
        set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /MT")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    else()
        set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s")
        set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -static -static-libstdc++ -static-libgcc")
    endif()
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_subdirectory(enet)

add_library(lolsrv_lib STATIC
    lib/argparse.hpp
    lib/blowfish.cpp
    lib/blowfish.hpp
    lib/enetserver.cpp
    lib/enetserver.hpp
    lib/io.hpp
    lib/io.cpp
    lib/json.hpp
    lib/json.cpp
    lib/log.cpp
    lib/log.hpp
    lib/r3d.hpp
    lib/r3d_ops.hpp
    lib/span.hpp
    )
target_include_directories(lolsrv_lib PUBLIC lib)
target_link_libraries(lolsrv_lib PUBLIC enet)

add_executable(lolsrv
    src/game.hpp
    src/game.cpp
    src/game_replacer.hpp
    src/game_replacer.cpp
    src/main.cpp
    src/options.hpp
    src/options.cpp
    src/proto.hpp
    src/proto.cpp
    src/proto_base.cpp
    src/proto_base.hpp
    src/proto_pkt.hpp
    src/proto_json.hpp
    src/proto_json.cpp
    src/proto/proto_0.8.13.26.cpp
    src/proto/proto_0.8.13.26.hpp
    src/proto/proto_0.9.22.14.cpp
    src/proto/proto_0.9.22.14.hpp
    src/proto/proto_0.9.22.14_ab.cpp
    src/proto/proto_0.9.22.14_ab.hpp
    src/proto/proto_0.9.22.16.cpp
    src/proto/proto_0.9.22.16.hpp
    src/proto/proto_0.9.22.18.cpp
    src/proto/proto_0.9.22.18.hpp
    src/proto/proto_0.9.25.21.cpp
    src/proto/proto_0.9.25.21.hpp
    src/proto/proto_0.9.25.24.cpp
    src/proto/proto_0.9.25.24.hpp
    src/proto/proto_0.9.25.36.cpp
    src/proto/proto_0.9.25.36.hpp
    src/proto/proto_1.0.0.25.cpp
    src/proto/proto_1.0.0.25.hpp
    src/proto/proto_1.0.0.28.cpp
    src/proto/proto_1.0.0.28.hpp
    src/proto/proto_1.0.0.52.cpp
    src/proto/proto_1.0.0.52.hpp
    src/proto/proto_1.0.0.58.cpp
    src/proto/proto_1.0.0.58.hpp
    src/proto/proto_1.0.0.61.cpp
    src/proto/proto_1.0.0.61.hpp
    src/proto/proto_1.0.0.63.cpp
    src/proto/proto_1.0.0.63.hpp
    src/proto/proto_1.0.0.66.cpp
    src/proto/proto_1.0.0.66.hpp
    src/proto/proto_1.0.0.70.cpp
    src/proto/proto_1.0.0.70.hpp
    src/proto/proto_1.0.0.72.cpp
    src/proto/proto_1.0.0.72.hpp
    src/proto/proto_1.0.0.74.cpp
    src/proto/proto_1.0.0.74.hpp
    src/proto/proto_1.0.0.75.cpp
    src/proto/proto_1.0.0.75.hpp
    src/proto/proto_1.0.0.79.cpp
    src/proto/proto_1.0.0.79.hpp
    src/proto/proto_1.0.0.81.cpp
    src/proto/proto_1.0.0.81.hpp
    src/proto/proto_1.0.0.82.cpp
    src/proto/proto_1.0.0.82.hpp
    src/proto/proto_1.0.0.83.cpp
    src/proto/proto_1.0.0.83.hpp
    src/proto/proto_1.0.0.85.cpp
    src/proto/proto_1.0.0.85.hpp
    src/proto/proto_1.0.0.86.cpp
    src/proto/proto_1.0.0.86.hpp
    src/proto/proto_1.0.0.87.cpp
    src/proto/proto_1.0.0.87.hpp
    src/proto/proto_1.0.0.94.cpp
    src/proto/proto_1.0.0.94.hpp
    src/proto/proto_1.0.0.96.cpp
    src/proto/proto_1.0.0.96.hpp
    src/proto/proto_1.0.0.97.cpp
    src/proto/proto_1.0.0.97.hpp
    src/proto/proto_1.0.0.98.cpp
    src/proto/proto_1.0.0.98.hpp
    src/proto/proto_1.0.0.99.cpp
    src/proto/proto_1.0.0.99.hpp
    src/proto/proto_1.0.0.100.cpp
    src/proto/proto_1.0.0.100.hpp
    src/proto/proto_1.0.0.101.cpp
    src/proto/proto_1.0.0.101.hpp
    src/proto/proto_1.0.0.102.cpp
    src/proto/proto_1.0.0.102.hpp
    src/proto/proto_1.0.0.103.cpp
    src/proto/proto_1.0.0.103.hpp
    src/proto/proto_1.0.0.104.cpp
    src/proto/proto_1.0.0.104.hpp
    src/proto/proto_1.0.0.105.cpp
    src/proto/proto_1.0.0.105.hpp
    src/proto/proto_1.0.0.106.cpp
    src/proto/proto_1.0.0.106.hpp
    src/proto/proto_1.0.0.107.cpp
    src/proto/proto_1.0.0.107.hpp
    src/proto/proto_1.0.0.108.cpp
    src/proto/proto_1.0.0.108.hpp
    src/proto/proto_1.0.0.109.cpp
    src/proto/proto_1.0.0.109.hpp
    src/proto/proto_1.0.0.110.cpp
    src/proto/proto_1.0.0.110.hpp
    src/proto/proto_1.0.0.111.cpp
    src/proto/proto_1.0.0.111.hpp
    src/proto/proto_1.0.0.112.cpp
    src/proto/proto_1.0.0.112.hpp
    src/proto/proto_1.0.0.113.cpp
    src/proto/proto_1.0.0.113.hpp
    src/proto/proto_1.0.0.114.cpp
    src/proto/proto_1.0.0.114.hpp
    src/proto/proto_1.0.0.116.cpp
    src/proto/proto_1.0.0.116.hpp
    src/proto/proto_1.0.0.117.cpp
    src/proto/proto_1.0.0.117.hpp
    src/proto/proto_1.0.0.118.cpp
    src/proto/proto_1.0.0.118.hpp
    src/proto/proto_1.0.0.119.cpp
    src/proto/proto_1.0.0.119.hpp
    src/proto/proto_1.0.0.120.cpp
    src/proto/proto_1.0.0.120.hpp
    src/proto/proto_1.0.0.121.cpp
    src/proto/proto_1.0.0.121.hpp
    src/proto/proto_1.0.0.122.cpp
    src/proto/proto_1.0.0.122.hpp
    src/proto/proto_1.0.0.123.cpp
    src/proto/proto_1.0.0.123.hpp
    src/proto/proto_1.0.0.124.cpp
    src/proto/proto_1.0.0.124.hpp
    src/proto/proto_1.0.0.125.cpp
    src/proto/proto_1.0.0.125.hpp
    src/proto/proto_1.0.0.126.cpp
    src/proto/proto_1.0.0.126.hpp
    src/proto/proto_1.0.0.126_ab.cpp
    src/proto/proto_1.0.0.126_ab.hpp
    src/proto/proto_1.0.0.127.cpp
    src/proto/proto_1.0.0.127.hpp
    src/proto/proto_1.0.0.128.cpp
    src/proto/proto_1.0.0.128.hpp
    src/proto/proto_1.0.0.129.cpp
    src/proto/proto_1.0.0.129.hpp
    src/proto/proto_1.0.0.130.cpp
    src/proto/proto_1.0.0.130.hpp
    src/proto/proto_1.0.0.131.cpp
    src/proto/proto_1.0.0.131.hpp
    )
target_link_libraries(lolsrv PRIVATE lolsrv_lib)
target_include_directories(lolsrv PUBLIC src)

file(COPY ./pkt/ DESTINATION ./pkt/)
