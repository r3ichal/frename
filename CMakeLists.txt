include(GNUInstallDirs)

cmake_minimum_required(VERSION 3.20)
project(frename VERSION 1.0.0 LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(frename 
  src/main.cpp
  src/int_utils.cpp
  src/string_utils.cpp
  src/log.cpp
  src/fs_utils.cpp
  src/cli.cpp
)

if(WIN32)
  target_link_options(frename PRIVATE -static -static-libgcc -static-libstdc++)
endif()

target_compile_options(frename PRIVATE -Wall -Wextra)

target_include_directories(frename PRIVATE include)

install(TARGETS frename RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES man/frename.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)