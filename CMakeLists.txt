cmake_minimum_required(VERSION 3.31)
project(leetcode)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(algorithm
        codeforces/2106/c.cpp
        codeforces/2065/c2.cpp
        codeforces/2123/e.cpp
        codeforces/2121/e.cpp
        "others/2500-2600/2581. 统计可能的树根数目.cpp")