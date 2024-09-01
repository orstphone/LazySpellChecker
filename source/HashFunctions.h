//
// Created by deccauvw@github on 2024-09-01.
//


#pragma once
#include "LazySpellCheckerHelper.h"
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <random>

namespace LazySpellChecker {

	class HashFunctions {
	public:
		HashFunctions() = default;
		~HashFunctions() = default;
		virtual size_t hash(const std::string &key, size_t tableSize);


		//hash functions
		virtual size_t _MD5(const std::string &key, size_t tableSize);
	};
} // LazySpellChecker

