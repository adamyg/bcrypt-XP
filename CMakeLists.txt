##
# CMake Application Build Manifest
#
# Copyright (c) 2025, Adam Young.
#
# https://github.com/adamyg/bcrypt-XP
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
#
# Mingw64 setup:
#
#   c:\msys64\usr\bin\pacman --noconfirm -S mingw-w64-x86_64-gnutls
#   c:\msys64\usr\bin\pacman --noconfirm -S mingw-w64-x86_64-dlfcn
#
#   c:\msys64\usr\bin\pacman --noconfirm -S mingw-w64-i686-gnutls
#   c:\msys64\usr\bin\pacman --noconfirm -S mingw-w64-i686-dlfcn
#

cmake_minimum_required(VERSION 3.15)

project("busybox-xp" LANGUAGES C CXX)

add_definitions(-D_WINDLL -DUNICODE -D_UNICODE -D_WIN32_WINNT=0x501)

message("-- C Compiler: ${CMAKE_C_COMPILER_ID}")
message("-- C++ Compiler: ${CMAKE_CXX_COMPILER_ID}")
message("-- Generated with config types: ${CMAKE_CONFIGURATION_TYPES}")

if(MSVC)
        add_definitions(-D_CRT_SECURE_NO_WARNINGS)
        set(CMAKE_CXX_STANDARD 17)
elseif(CMAKE_C_COMPILER_ID STREQUAL OpenWatcom)
        message("-- Watcom Version: ${_CMAKE_WATCOM_VERSION}")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -za99")
endif()

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")


##  --- library: tomcrypt.lib

include(FetchContent)
FetchContent_Declare(
        tomcrypt
        GIT_REPOSITORY https://github.com/libtom/libtomcrypt
        GIT_TAG v1.18.2
        )
FetchContent_GetProperties(tomcrypt)
if(NOT tomcrypt_POPULATED)
        FetchContent_Populate(tomcrypt)
endif()

set(TOMCRYPT_DIR
        "${tomcrypt_SOURCE_DIR}/src"
        )

set(TOMCRYPT_INCLUDE
        "${TOMCRYPT_DIR}/headers"
        )

file(GLOB TOMCRYPT_SOURCE
        "${TOMCRYPT_DIR}/ciphers/*.c"
        "${TOMCRYPT_DIR}/ciphers/*/*.c"
        "${TOMCRYPT_DIR}/hashes/*.c"
        "${TOMCRYPT_DIR}/hashes/*/*.c"
        "${TOMCRYPT_DIR}/misc/*.c"
        "${TOMCRYPT_DIR}/misc/*/*.c"
        "${TOMCRYPT_DIR}/modes/*/*.c"
        "${TOMCRYPT_DIR}/prngs/*.c"
        "${TOMCRYPT_DIR}/stream/*/*.c"
        "${TOMCRYPT_INCLUDE}/*"
        )

add_library(tomcrypt
        STATIC ${TOMCRYPT_SOURCE} ${TOMCRYPT_HEADERS})

target_compile_definitions(tomcrypt
        PUBLIC -DLTM_DESC -DLTC_SOURCE -DLTC_NO_PROTOTYPES
        )

target_include_directories(tomcrypt
        PUBLIC ${TOMCRYPT_INCLUDE})


##  --- application: hashsum

add_executable(hashsum
        ${tomcrypt_SOURCE_DIR}/demos/hashsum.c
        )

target_compile_definitions(hashsum
        PUBLIC -DLTC_NO_PROTOTYPES
        )

target_include_directories(hashsum
        PUBLIC ${TOMCRYPT_INCLUDE})

target_link_libraries(hashsum
        tomcrypt)


##  --- application: ltcrypt

add_executable(ltcrypt
        ${tomcrypt_SOURCE_DIR}/demos/ltcrypt.c
        )

target_compile_definitions(ltcrypt
        PUBLIC -DLTC_NO_PROTOTYPES
        )

target_include_directories(ltcrypt
        PUBLIC ${TOMCRYPT_INCLUDE})

target_link_libraries(ltcrypt
        tomcrypt)


##  --- library: bcrypt.lib/.dll

set(BCRYPT_HEADER "bcrypt.h")

set(BCRYPT_DIR ${SOURCE_DIR})
set(BCRYPT_SOURCE
        "${BCRYPT_DIR}/bcrypt_main.c"
        "${BCRYPT_DIR}/bcrypt_notimpl.c"
        "${BCRYPT_DIR}/gnutls.c"
        "${BCRYPT_DIR}/debug.c"
        "${BCRYPT_DIR}/bcrypt.rc"
        )

add_library(bcryptxp
        SHARED ${BCRYPT_SOURCE} ${BCRYPT_HEADERS}
        )

target_compile_definitions(bcryptxp
        PUBLIC -DLTC_NO_PROTOTYPES -DSONAME_LIBGNUTLS="libgnutls-30.dll"
        )

target_include_directories(bcryptxp
        PUBLIC ${TOMCRYPT_INCLUDE}
        )

target_link_libraries(bcryptxp
        tomcrypt
        )

if(MSVC)
        set_target_properties(bcryptxp
                PROPERTIES LINK_FLAGS "/MAP /MAPINFO:EXPORTS /DEF:${BCRYPT_DIR}/bcrypt.def"
                )
elseif(MINGW)
        get_filename_component(MINGWBINPATH ${CMAKE_C_COMPILER} PATH)
        find_file(libgnutls
                NAMES libgnutls-30.dll
                PATHS ${MINGWBINPATH}
                REQUIRED
                )
        set_target_properties(bcryptxp
                PROPERTIES PREFIX ""
                )
        target_sources(bcryptxp
                PRIVATE ${BCRYPT_DIR}/bcrypt.def
                )
        target_link_options(bcryptxp
                PRIVATE "-Wl,--enable-stdcall-fixup"
                )
        target_link_libraries(bcryptxp
                dl.a
                )
endif()


##  --- application: bcrypt_test

add_executable(bcrypt_test
        "${BCRYPT_DIR}/tests/bcrypt.c"
        "${BCRYPT_DIR}/debug.c"
        )

target_link_libraries(bcrypt_test
        bcryptxp)

if(MSVC)
        set_target_properties(bcrypt_test
                PROPERTIES LINK_FLAGS "/MAP")
endif()

##end
