cmake_minimum_required(VERSION 3.10)
project(hgg_epp)

set(CMAKE_CXX_STANDARD 11)

add_executable(hgg_epp main.cpp tools/geometry_.h tools/Utils.cpp tools/Utils.h tools/Geometry.cpp tools/Geometry.h)