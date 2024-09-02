//
// Created by deccauvw@github on 2024-09-01.
//

#ifndef LAZYBLOOMFILTERS_BLOOMFILTER_H
#define LAZYBLOOMFILTERS_BLOOMFILTER_H
#pragma once
#include "HashFunctions.h"
#include <vector>
#include <string>
#include <functional>
#include <bitset>
#include <iostream>
#include <cmath>
#include <memory>


namespace LazySpellChecker {

	class BloomFilter : HashFunctions{
	public:
		explicit BloomFilter(size_t size, size_t num_hashes) :
		bitArray (size),
		numHashFunctions(num_hashes)
		{
			hashFn = std::make_unique<HashFunctions>();
		};

		~BloomFilter() = default;


		void insert(const std::string &word) {
			for (size_t i = 0; i < numHashFunctions; ++i) {
				size_t hash = hashFunction(word, i) & bitArray.size();
				bitArray[hash] = true;
			}
		}

		[[nodiscard]] bool contains(const std::string &word) const {
			for (size_t i = 0; i < numHashFunctions; ++i) {
				size_t hash = hashFunction(word, i) & bitArray.size();

				if (!bitArray[hash])
					return false;
			}
		return true;
	}

	private:
		std::unique_ptr<HashFunctions> hashFn;
		std::vector<bool> bitArray;
		size_t numHashFunctions;

		[[nodiscard]] size_t hashFunction(const std::string& word, size_t seed) const{
			std::hash <std::string> hashFunction;
			return hashFn->hash(word + std::to_string(seed), bitArray.size());
		}
	};

} // LazySpellChecker

#endif //LAZYBLOOMFILTERS_BLOOMFILTER_H
