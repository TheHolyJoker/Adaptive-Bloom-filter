cmake_minimum_required(VERSION 3.12)
project(AdaptiveBF)

set(CMAKE_CXX_STANDARD 14)

add_executable(AdaptiveBF main.cpp
        MurmurHash3.cpp MurmurHash3.h
        GreyBoxFunction.cpp GreyBoxFunction.h
        Hash.cpp Hash.h
        BloomFilter.cpp BloomFilter.h
        SetTable.h SetTable.cpp
        Helper.cpp Helper.h
        "tests/testers.cpp" "tests/testers.h"
        Non_Adaptive/NonAdaptiveBloomFilter.cpp Non_Adaptive/NonAdaptiveBloomFilter.h
        Non_Adaptive/NonAdaptiveHelper.cpp Non_Adaptive/NonAdaptiveHelper.h
        DB/myDB.cpp DB/myDB.h
#        new_tests/newTesters.cpp new_tests/newTesters.h
        )
target_link_libraries(AdaptiveBF leveldb)
