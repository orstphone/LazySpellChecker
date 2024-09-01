//
// Created by deccauvw@github on 2024-09-01.
//

#include "HashFunctions.h"


namespace LazySpellChecker {
	size_t HashFunctions::hash(const std::string &key, size_t tableSize) {
		std::hash <std::string> hash_fn;
		size_t                  hashValue = hash_fn(key);
		hashValue %= tableSize;

		return hashValue;
}

	size_t HashFunctions::_MD5(const std::string &key, size_t tableSize) {
		size_t lengthOfPaddingBitsCoefficient = 0;

		while (true)
		{
			auto lengthOfKey = key.length();
			auto i = 0;
			auto get512Coefficient = [&lengthOfKey](int n) -> size_t { 512 * n - 64 - lengthOfKey; };
			if (get512Coefficient(i) > 0) {
				lengthOfPaddingBitsCoefficient = get512Coefficient(i);
				break;
			}
				i++;
		}

		size_t AppendedBitsSize = lengthOfPaddingBitsCoefficient * 512 - 64;
		const size_t AppendingBitsSize = 64;

		//initialize MD Buffer
		size_t MD_Buffer[LazySpellChecker::Constants::k_defaultMd5HashBufferNumber];
		for (size_t i = 0; i < LazySpellChecker::Constants::k_defaultMd5HashBufferNumber; i++) {
			MD_Buffer[i] = LazySpellChecker::Constants::k_defaultMd5StateVariables[i];
		}

		//compute rounds from 1 to 4


	}
		return 0;
	}
	// LazySpellChecker

