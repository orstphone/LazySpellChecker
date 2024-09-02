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
		explicit SpellChecker(size_t size, size_t numHashes,
		                      const std::string &dictionaryFilename = Constants::k_defaultDictionaryFilename)
				: BloomFilter(size, numHashes)
				 {
			std::cout << "SpellChecker constructor called" << std::endl;
			bf = std::make_unique<BloomFilter>(Constants::k_defaultDictionarySize, 3);

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
			std::cout << count << " words inserted" << std::endl;
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
