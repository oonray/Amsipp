cmake_minimum_required(VERSION 3.7)

project(AmsiBypass)
set(CMAKE_CXX_STANDARD 20)

add_library(AmsiBypasslib main.cpp)
add_executable(AmsiBypass main.cpp)
