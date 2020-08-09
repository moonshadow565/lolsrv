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

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_subdirectory(enet)

add_library(lolsrv_lib STATIC
    lib/argparse.hpp
    lib/blowfish.cpp
    lib/blowfish.hpp
    lib/enetserver.cpp
    lib/enetserver.hpp
    lib/log.cpp
    lib/log.hpp
    lib/options.hpp
    lib/r3d/math.hpp
    lib/r3d/point2d.hpp
    lib/r3d/point3d.hpp
    lib/r3d/r3d.hpp
    lib/r3d/types.hpp
    )
target_include_directories(lolsrv_lib PUBLIC lib)
target_link_libraries(lolsrv_lib PUBLIC enet)

macro(Version ver)
    add_executable(lolsrv_${ver} src/${ver}/pkt.hpp src/${ver}/main.cpp)
    target_link_libraries(lolsrv_${ver} PRIVATE lolsrv_lib)
endmacro()

Version(0.8.13.26)
Version(0.9.22.14)
Version(0.9.22.14_ab)
Version(0.9.22.16)
Version(0.9.25.21)
Version(1.0.0.63)
Version(1.0.0.74)
Version(1.0.0.79)
Version(1.0.0.82)
Version(1.0.0.86)
Version(1.0.0.97)
Version(1.0.0.98)
Version(1.0.0.103)
Version(1.0.0.104)
Version(1.0.0.105)
Version(1.0.0.107)
Version(1.0.0.109)
Version(1.0.0.110)
Version(1.0.0.111)
Version(1.0.0.113)
Version(1.0.0.117)
Version(1.0.0.119)
Version(1.0.0.124)
Version(1.0.0.125)
Version(1.0.0.126)
Version(1.0.0.126_ab)
Version(1.0.0.131)
