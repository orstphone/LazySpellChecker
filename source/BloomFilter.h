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
		explicit BloomFilter(size_t _numHashes, size_t _numBits) :
				numHashFunctions(_numHashes),
				numBits(_numBits),
				bitArraySize(0)
		{
			size_t numInts = (size_t) (_numBits + 31) / 32;
//			printf("BloomFilter constructor called\n");
//			printf("bitArraySize[bits] == %zu\n", _numBits);
//			printf("bitArraySize[int] == %zu\n", numInts);

			bitArray.resize(numInts, 0x00);
			//printf("sizeof bitarray == %zu\n", bitArray.size());
			hashFn = std::make_unique<HashFunctions>();
		};

		~BloomFilter() = default;

		void insert(const std::string &word) {
//			printf("------------------------------calling insert\n");
//			printf("word == %s\n", word.c_str());
			for (size_t i = 0; i < numHashFunctions; ++i) {

				size_t index = hashFunction(word, i) % numBits; //index is uint32_t
				auto arrayIndex = index / 32;
				auto bitMask = 1U << (index % 32);
				bitArray[arrayIndex] |= bitMask;
			}
		}

		[[nodiscard]] bool contains(const std::string &word) const {
			for (size_t i = 0; i < numHashFunctions; ++i) {
				size_t index = hashFunction(word, i) % numBits;

				auto exists = (bitArray[index / 32] & (1U << (index % 32))) != 0;

				if (!exists) {
					return false;
				}
			}
		return true;
	}

	private:
		std::unique_ptr<HashFunctions> hashFn;
		std::vector<uint32_t> bitArray;
		size_t numHashFunctions;
		size_t bitArraySize;
		size_t numBits;

		[[nodiscard]] size_t hashFunction(const std::string& word, size_t seed) const{
			std::hash <std::string> hashFunction;
			return hashFn->MD5(word + std::to_string(seed), bitArraySize);
		}
	};

} // LazySpellChecker

#endif //LAZYBLOOMFILTERS_BLOOMFILTER_H
