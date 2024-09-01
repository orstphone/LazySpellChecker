cmake_minimum_required(VERSION 3.27)
project(LazyBloomFilters)

set(CMAKE_CXX_STANDARD 17)

add_executable(LazyBloomFilters main.cpp
        source/BloomFilter.cpp
        source/BloomFilter.h
        source/LazySpellCheckerHelper.h
        source/HashFunctions.cpp
        source/HashFunctions.h
        LazySpellCheckerHeader.h
        source/SpellChecker.cpp
        source/SpellChecker.h)
