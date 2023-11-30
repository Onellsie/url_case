cmake_minimum_required(VERSION 3.28.0 FATAL_ERROR)

project(URLCase VERSION 1.0 LANGUAGES CXX)

add_executable(URLCase src/Unit_test.cpp src/Test_Url.h src/Test_Url.cpp src/URL.h src/URL.cpp)

