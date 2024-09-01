cmake_minimum_required(VERSION 3.27)
project(LazyBloomFilters)

set(CMAKE_CXX_STANDARD 17)

file(
  COPY "${CMAKE_SOURCE_DIR}\\source\\wordlist.txt"
  DESTINATION "${CMAKE_BINARY_DIR}")

add_executable(LazyBloomFilters main.cpp
        source/BloomFilter.cpp
        source/BloomFilter.h
        source/LazySpellCheckerHelper.h
        source/HashFunctions.cpp
        source/HashFunctions.h
        LazySpellCheckerHeader.h
        source/SpellChecker.cpp
        source/SpellChecker.h)
