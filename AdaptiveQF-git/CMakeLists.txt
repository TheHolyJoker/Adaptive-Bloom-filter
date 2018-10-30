cmake_minimum_required(VERSION 3.12)
project(inheritance)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        inheritance main.cpp
        PackedArray.cpp PackedArray.h
        AdaptQF.cpp AdaptQF.h
        RegularQF.cpp RegularQF.h
        tests/paTests.cpp tests/paTests.h
        Filter.cpp Filter.h
        Hash/Hash.cpp Hash/Hash.h
        Hash/MurmurHash3.cpp Hash/MurmurHash3.h
        tests/Tests.cpp tests/Tests.h Helper.cpp Helper.h VariableLengthFingerPrint/VLHelper.cpp VariableLengthFingerPrint/VLHelper.h VariableLengthFingerPrint/VLQF.cpp VariableLengthFingerPrint/VLQF.h VariableLengthFingerPrint/RegularVLQF.cpp VariableLengthFingerPrint/RegularVLQF.h VariableLengthFingerPrint/VLTests.cpp VariableLengthFingerPrint/VLTests.h globalFunction.cpp globalFunction.h)