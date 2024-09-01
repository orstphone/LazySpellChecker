//
// Created by deccauvw@github on 2024-09-01.
//

#ifndef LAZYBLOOMFILTERS_HASHFUNCTIONS_H
#define LAZYBLOOMFILTERS_HASHFUNCTIONS_H
#pragma once
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


	};

} // LazySpellChecker

#endif //LAZYBLOOMFILTERS_HASHFUNCTIONS_H
