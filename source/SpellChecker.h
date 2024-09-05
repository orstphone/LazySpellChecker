//
// Created by deccauvw@github on 2024-09-01.
//

#ifndef LAZYBLOOMFILTERS_SPELLCHECKER_H
#define LAZYBLOOMFILTERS_SPELLCHECKER_H
#pragma once
#include "BloomFilter.h"
#include "LazySpellCheckerHelper.h"
#include "HashFunctions.h"
#include <vector>
#include <string>
#include <functional>
#include <fstream>

namespace LazySpellChecker {

	class SpellChecker : BloomFilter{
	public:
		explicit SpellChecker()
				: BloomFilter(0, 0)
				 {
			 std::cout << "Lazy SpellChecker" << std::endl;

			const std::string &dictionaryFilename = Constants::k_defaultDictionaryFilename;

			auto p = LazySpellChecker::Constants::k_desiredFalsePositiveRate;
			auto n = LazySpellChecker::Constants::k_defaultDictionarySize;
			auto m = (int) ((-n * std::log(p)) / (std::log(2) * std::log(2))); // size of the bit array
			auto k = (int) (m / n * std::log(2)); // number of hash functions

//			printf("p = %f\n", p);  //nums [100% == 1]
//			printf("n = %d\n", n); //nums
//			printf("m = %d\n", m); //bits
//			printf("k = %d\n", k); //nums

			//printf("calling BF\n");
			bf = std::make_unique<BloomFilter>(k, m);

			printf("opening file\n");
			std::ifstream file(dictionaryFilename);
			if (!file) {
				std::cerr << "ERR : couldn't open file" << dictionaryFilename << std::endl;
				return;
			}

			std::string word;
			size_t count = 0;
			while (std::getline(file, word)){
				count++;
				bf->insert(word);
			}
			std::cout << count << " all words inserted" << std::endl;
		}

		~SpellChecker() = default;

		bool check(const std::string &word) {
			return bf->contains(word);
		}
	private:
		std::unique_ptr <BloomFilter> bf;
	};

} // LazySpellChecker

#endif //LAZYBLOOMFILTERS_SPELLCHECKER_H
