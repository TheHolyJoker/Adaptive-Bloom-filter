cmake_minimum_required(VERSION 3.13)
project(ABF_Remote)

set(CMAKE_CXX_STANDARD 14)

add_executable(ABF_Remote
        main.cpp

        #        Be_Tree_files/
        Be_Tree_files/swap_space.cpp Be_Tree_files/swap_space.hpp
        Be_Tree_files/betree.hpp Be_Tree_files/debug.hpp
        Be_Tree_files/backing_store.cpp Be_Tree_files/backing_store.hpp
        Be_Tree_files/test.cpp

        New_BF/Wrapper/Wrapper.cpp New_BF/Wrapper/Wrapper.h
        New_BF/V_tests/tests.h New_BF/V_tests/tests.cpp
        New_BF/Hash_files/Hash.cpp New_BF/Hash_files/MurmurHash3.cpp
        New_BF/Hash_files/MurmurHash3.h New_BF/Hash_files/Hash.h
        New_BF/General_BF/GeneralBF.cpp New_BF/General_BF/GeneralBF.h
        New_BF/Grey_Box_Function_Dir/GreyBoxFunction.h New_BF/Grey_Box_Function_Dir/GreyBoxFunction.cpp

#        BF_files/.
        #        BF_files/old_Wrapper/old_Wrapper.cpp BF_files/old_Wrapper/old_Wrapper.h
#        BF_files/General_BF/GeneralBF.h BF_files/General_BF/GeneralBF.cpp
#        BF_files/Hash.h BF_files/Hash.cpp
#        BF_files/MurmurHash3.h BF_files/MurmurHash3.cpp
#        BF_files/BloomFilter.h BF_files/BloomFilter.cpp
#        BF_files/GreyBoxFunction.h BF_files/GreyBoxFunction.cpp
#        BF_files/Helper.h BF_files/Helper.cpp
#        BF_files/SetTable.h BF_files/SetTable.cpp
#        BF_files/tests/testers.h BF_files/tests/testers.cpp
#        BF_files/Non_Adaptive/NonAdaptiveBloomFilter.h BF_files/Non_Adaptive/NonAdaptiveBloomFilter.cpp
#        BF_files/Non_Adaptive/NonAdaptiveHelper.h BF_files/Non_Adaptive/NonAdaptiveHelper.cpp
#        BF_files/main.cpp
#        BF_files/V_tests/VirtTests.cpp BF_files/V_tests/VirtTests.h
#        BF_files/Path_Managing/Manage_paths.h BF_files/Path_Managing/Manage_paths.cpp

        #        QF_files/.
#        BF_files/BF_MH.h
        #        New_BF/Clean_main/atom.cpp New_BF/Clean_main/atom.h
        New_BF/Remote/Remote.cpp New_BF/Remote/Remote.h)