cmake_minimum_required(VERSION 3.5)
project(lolsrv LANGUAGES CXX)

if(WIN32)
    if(MSVC)
        set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /MT")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    else()
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libstdc++ -static-libgcc")
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

add_executable(lolsrv_live106 src/main_live106.hpp src/main_live106.cpp)
target_link_libraries(lolsrv_live106 PRIVATE lolsrv_lib)

add_executable(lolsrv_cb1 src/main_cb1.hpp src/main_cb1.cpp)
target_link_libraries(lolsrv_cb1 PRIVATE lolsrv_lib)

add_executable(lolsrv_cb3 src/main_cb3.hpp src/main_cb3.cpp)
target_link_libraries(lolsrv_cb3 PRIVATE lolsrv_lib)

add_executable(lolsrv_cb3_ab src/main_cb3_ab.hpp src/main_cb3_ab.cpp)
target_link_libraries(lolsrv_cb3_ab PRIVATE lolsrv_lib)

add_executable(lolsrv_live126 src/main_live126.hpp src/main_live126.cpp)
target_link_libraries(lolsrv_live126 PRIVATE lolsrv_lib)

add_executable(lolsrv_pbe126 src/main_pbe126.hpp src/main_pbe126.cpp)
target_link_libraries(lolsrv_pbe126 PRIVATE lolsrv_lib)

add_executable(lolsrv_live131 src/main_live131.hpp src/main_live131.cpp)
target_link_libraries(lolsrv_live131 PRIVATE lolsrv_lib)
