cmake_minimum_required(VERSION 3.23)
project(labb3)

set(CMAKE_CXX_STANDARD 14)

add_executable(labb3 main.cpp gen_data.cpp gen_data.h lin_search.cpp lin_search.h bin_search.cpp bin_search.h bin_tree.cpp bin_tree.h hash_table.cpp hash_table.h)
