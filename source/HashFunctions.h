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
		static uint32_t _md5_processRoundsBlockWise(uint32_t word1, uint32_t word2, std::vector<uint32_t> &md5_buffer);

		static std::vector<uint8_t> _md5_paddingBits(const std::string &key);

		static inline uint32_t _md5_F(uint32_t x, uint32_t y, uint32_t z);

		static inline uint32_t _md5_G(uint32_t x, uint32_t y, uint32_t z);

		static inline uint32_t _md5_H(uint32_t x, uint32_t y, uint32_t z);

		static inline uint32_t _md5_I(uint32_t x, uint32_t y, uint32_t z);

		static inline uint32_t _md5_rotateLeft(uint32_t x, uint32_t n);

		static inline std::vector<uint32_t> stringToUint32(const std::string &key);

		void processMd5(std::vector<uint32_t>& digest, const std::vector<uint8_t> &message);

		//utilities



	};
} // LazySpellChecker

