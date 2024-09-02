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
#include <bitset>
#include <cstring> //formemcpy

namespace LazySpellChecker {

	class HashFunctions {
	public:
		HashFunctions() = default;
		~HashFunctions() = default;
		virtual uint32_t hash(const std::string &key, uint32_t tableSize);

		//hash functions
		virtual uint32_t _MD5(const std::string &key, uint32_t tableSize);

	private:
		uint32_t _md5_processRoundsBlockWise(uint32_t word1, uint32_t word2, std::vector<uint32_t> &md5_buffer);

		std::vector<uint8_t> _md5_paddingBits(const std::string &key);

		uint32_t _md5_F(uint32_t x, uint32_t y, uint32_t z);

		uint32_t _md5_G(uint32_t x, uint32_t y, uint32_t z);

		uint32_t _md5_H(uint32_t x, uint32_t y, uint32_t z);

		uint32_t _md5_I(uint32_t x, uint32_t y, uint32_t z);

		uint32_t _md5_rotateLeft(uint32_t x, uint32_t n);


		//utilities
		void printHex(const std::vector<uint8_t>& dat)
		{
			for(auto b : dat)
			{
				printf("%02x",b);
			}
			printf("\n");
		}


	};
} // LazySpellChecker

