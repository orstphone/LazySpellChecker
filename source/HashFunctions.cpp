//
// Created by deccauvw@github on 2024-09-01.
//

#include "HashFunctions.h"

namespace LazySpellChecker {
	size_t HashFunctions::hash(const std::string &key, size_t tableSize) {
		size_t hashValue = 0;
		for (auto &e: key) {
			hashValue = 37 * hashValue + e;
		}
		hashValue %= tableSize;
		if (hashValue < 0)
		{
			hashValue += tableSize;
		}
		return hashValue;
		//return key.length() % tableSize;

	}
} // LazySpellChecker