cmake_minimum_required(VERSION 3.5)

project(enet LANGUAGES C)

add_library(enet STATIC
    src/callbacks.c
    src/host.c
    src/list.c
    src/packet.c
    src/peer.c
    src/protocol.c
    src/unix.c
    src/win32.c
)

target_include_directories(enet PUBLIC include)

if(MSVC)
    target_compile_options(enet PRIVATE -W3)
else()
    target_compile_options(enet PRIVATE -Wno-error)
endif()

if(WIN32)
    target_link_libraries(enet PRIVATE ws2_32 winmm)
else()
    include(CheckFunctionExists)
    include(CheckStructHasMember)
    include(CheckTypeSize)
    check_function_exists("fcntl" HAS_FCNTL)
    check_function_exists("poll" HAS_POLL)
    check_function_exists("getaddrinfo" HAS_GETADDRINFO)
    check_function_exists("getnameinfo" HAS_GETNAMEINFO)
    check_function_exists("gethostbyname_r" HAS_GETHOSTBYNAME_R)
    check_function_exists("gethostbyaddr_r" HAS_GETHOSTBYADDR_R)
    check_function_exists("inet_pton" HAS_INET_PTON)
    check_function_exists("inet_ntop" HAS_INET_NTOP)
    check_struct_has_member("struct msghdr" "msg_flags" "sys/types.h;sys/socket.h" HAS_MSGHDR_FLAGS)
    set(CMAKE_EXTRA_INCLUDE_FILES "sys/types.h" "sys/socket.h")
    check_type_size("socklen_t" HAS_SOCKLEN_T BUILTIN_TYPES_ONLY)
    unset(CMAKE_EXTRA_INCLUDE_FILES)
    if(HAS_FCNTL)
        target_compile_definitions(enet PRIVATE -DHAS_FCNTL)
    endif()
    if(HAS_POLL)
        target_compile_definitions(enet PRIVATE -DHAS_POLL)
    endif()
    if(HAS_GETNAMEINFO)
        target_compile_definitions(enet PRIVATE -DHAS_GETNAMEINFO)
    endif()
    if(HAS_GETADDRINFO)
        target_compile_definitions(enet PRIVATE -DHAS_GETADDRINFO)
    endif()
    if(HAS_GETHOSTBYNAME_R)
        target_compile_definitions(enet PRIVATE -DHAS_GETHOSTBYNAME_R)
    endif()
    if(HAS_GETHOSTBYADDR_R)
        target_compile_definitions(enet PRIVATE -DHAS_GETHOSTBYADDR_R)
    endif()
    if(HAS_INET_PTON)
        target_compile_definitions(enet PRIVATE -DHAS_INET_PTON)
    endif()
    if(HAS_INET_NTOP)
        target_compile_definitions(enet PRIVATE -DHAS_INET_NTOP)
    endif()
    if(HAS_MSGHDR_FLAGS)
        target_compile_definitions(enet PRIVATE -DHAS_MSGHDR_FLAGS)
    endif()
    if(HAS_SOCKLEN_T)
        target_compile_definitions(enet PRIVATE -DHAS_SOCKLEN_T)
    endif()
endif()
