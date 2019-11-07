cmake_minimum_required(VERSION 3.12)
project(newQF)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "-O3")
SET(CMAKE_C_FLAGS "-O3")

add_executable(newQF main.cpp
        GlobalFunctions/globalFunction.h GlobalFunctions/globalFunction.cpp
        Hash/MurmurHash3.h Hash/MurmurHash3.cpp
        Hash/Hash.h Hash/Hash.cpp
        QuotientFilter/BitArray.h QuotientFilter/BitArray.cpp
        QuotientFilter/BasicFilter.h QuotientFilter/BasicFilter.cpp
        QuotientFilter/Filter.h QuotientFilter/Filter.cpp
        QuotientFilter/DB.h QuotientFilter/DB.cpp
        Tests/DBtests.cpp Tests/DBtests.h)