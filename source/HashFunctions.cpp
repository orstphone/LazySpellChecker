//
// Created by deccauvw@github on 2024-09-01.
// reference :: https://www.comparitech.com/blog/information-security/md5-algorithm-with-examples/
//
#pragma once
#include "HashFunctions.h"

#include <cstring> //for memcpy>

namespace LazySpellChecker {
//	uint32_t HashFunctions::hash(const std::string &key, uint32_t tableSize) {
//		auto hashValue = _MD5(key, tableSize);
//		hashValue %= tableSize;
//		return hashValue;
//	}

	uint32_t HashFunctions::MD5(const std::string &key, uint32_t tableSize) {
		//convert str to uint8_t array
		auto keyVector32b = stringToUint32(key);

		//zero padding the keyVector32b to 512 bits
		auto keyVector512b = _md5_paddingBits(keyVector32b);
		//process the md5 hash
		processMd5(keyVector512b);

		//printf("\tkeyVector512b[0] == %x\n", keyVector512b[0]);
		return keyVector512b[0];
	}


	//======================================= F G H I FUNCTIONS


	//this returns padded char-wise 8bit sequence of the string for the md5 hash digestion prep
	std::vector<uint32_t> HashFunctions::_md5_paddingBits(std::vector<uint32_t> &message){
		//printf("bit padding called\n");
	//append 0 bits until the length is 64b short of a multiple of 512
	auto originalLengthBits = message.size() * 8;
		while (message.size() * 8 % 512 != 512 - 64)
			message.push_back(0x00);

		//append the original length in bits as 64b int. (little endian){
		for (auto i = 0; i < 8; ++i) {
			message.push_back(static_cast<uint32_t>(originalLengthBits & 0xFF));
			originalLengthBits >>= 8;
		}
		//printf("size of message = %d\n", message.size());
		return message;
	}

	//A to B (the F Fn)(1st round)
	inline uint32_t HashFunctions::_md5_F(uint32_t x, uint32_t y, uint32_t z) {
		return (x & y) | (~x & z);
	}

	inline uint32_t HashFunctions::_md5_G(uint32_t x, uint32_t y, uint32_t z) {
		return (x & z) | (y & ~z);
	}

	inline uint32_t HashFunctions::_md5_H(uint32_t x, uint32_t y, uint32_t z) {
		return (x ^ y ^ z);
	}

	inline uint32_t HashFunctions::_md5_I(uint32_t x, uint32_t y, uint32_t z) {
		return (y ^ (x | ~z));
	}

	inline uint32_t HashFunctions::_md5_rotateLeft(uint32_t x, uint32_t n) {
		return (x << n) | (x >> (32 - n));
	}

	std::vector<uint32_t> HashFunctions::stringToUint32(const std::string &key) {
//		printf("\n\nstringToUint32 called\n");
//		std::cout<<"key == "<<key<<std::endl;
		//printf("...key length = %d\n", key.length());

		std::vector<uint32_t> result;
		size_t                paddedLength = (key.length() + 3) / 4;
		result.reserve(paddedLength); //rnd up div. by 4

		//convert groups of 4B into uint32_t
		for (size_t i = 0; i < key.length(); i += 4) {
			uint32_t    value = 0;
			for (size_t j    = 0; j < 4 && (i + j < key.length()); ++j) {
				value |= (static_cast<uint32_t>(key.at(i + j)) << (j * 8));
			}
			result.push_back(value);
		}
		return result;
	}

	void HashFunctions::processMd5(std::vector<uint32_t> &digest) {
//		std::cout<<"process MD5 start\n";
//		printf("digest size = %d\n", digest.size());

		//init. variables
		uint32_t a = digest[0];
		uint32_t b = digest[1];
		uint32_t c = digest[2];
		uint32_t d = digest[3];

		//Const for MD5 TF
		const uint32_t Sij[4][4] = {
				{7, 12, 17, 22},
				{5, 9,  14, 20},
				{4, 11, 16, 23},
				{6, 10, 15, 21}
		};

		auto T = [](int i) -> uint32_t {
			return floor(pow(2, 32) * abs(sin(i + 1)));
		};

		//Convert message into 32b words
		std::vector<uint32_t> X(16);
		for (int              i = 0; i < 64; i += 4) {
			X[i / 4] = static_cast<uint32_t>(digest[i]) |
			           (static_cast<uint32_t>(digest[i + 1]) << 8) |
			           (static_cast<uint32_t>(digest[i + 2]) << 16) |
			           (static_cast<uint32_t>(digest[i + 3]) << 24);
		}

		//Phase 1
		for (auto i = 0; i < 4; ++i) {
			auto s = [&Sij](int r, int step) { return Sij[r - 1][step % 4]; };
			a = b + _md5_rotateLeft(a + _md5_F(b, c, d) + X[0 + 4 * i] + T(0 + 4 * i), s(1, 0));
			d = a + _md5_rotateLeft(d + _md5_F(a, b, c) + X[1 + 4 * i] + T(1 + 4 * i), s(1, 1));
			c = d + _md5_rotateLeft(c + _md5_F(d, a, b) + X[2 + 4 * i] + T(2 + 4 * i), s(1, 2));
			b = c + _md5_rotateLeft(b + _md5_F(c, d, a) + X[3 + 4 * i] + T(3 + 4 * i), s(1, 3));
		}

		//Phase 2
		for (auto i = 0; i < 4; ++i) {
			auto _idx = [](int i) { return (5 * i + 1) % 16; };
			auto s    = [&Sij](int r, int step) { return Sij[r - 1][step % 4]; };
			a = b + _md5_rotateLeft(a + _md5_G(b, c, d) + X[_idx(0 + 4 * i)] + T(16 + 0 + 4 * i), s(2, 0));
			d = a + _md5_rotateLeft(d + _md5_G(a, b, c) + X[_idx(1 + 4 * i)] + T(16 + 1 + 4 * i), s(2, 1));
			c = d + _md5_rotateLeft(c + _md5_G(d, a, b) + X[_idx(2 + 4 * i)] + T(16 + 2 + 4 * i), s(2, 2));
			b = c + _md5_rotateLeft(b + _md5_G(c, d, a) + X[_idx(3 + 4 * i)] + T(16 + 3 + 4 * i), s(2, 3));
		}
		//Phase 3
		for (auto i = 0; i < 4; ++i) {
			auto _idx = [](int i) { return (3 * i + 5) % 16; };
			auto s    = [&Sij](int r, int step) { return Sij[r - 1][step % 4]; };
			a         = b + _md5_rotateLeft(a + _md5_H(b, c, d) + X[_idx(0 + 4 * i)] + T(32 + 0 + 4 * i), s(3, 0));
			d         = a + _md5_rotateLeft(d + _md5_H(a, b, c) + X[_idx(1 + 4 * i)] + T(32 + 1 + 4 * i), s(3, 1));
			c         = d + _md5_rotateLeft(c + _md5_H(d, a, b) + X[_idx(2 + 4 * i)] + T(32 + 2 + 4 * i), s(3, 2));
			b         = c + _md5_rotateLeft(b + _md5_H(c, d, a) + X[_idx(3 + 4 * i)] + T(32 + 3 + 4 * i), s(3, 3));
		}
		//Phase 4
		for (auto i = 0; i < 4; ++i) {
			auto _idx = [](int i) { return (7 * i + 0) % 16; };
			auto s    = [&Sij](int r, int step) { return Sij[r - 1][step % 4]; };
			a         = b + _md5_rotateLeft(a + _md5_I(b, c, d) + X[_idx(0 + 4 * i)] + T(48 + 0 + 4 * i), s(4, 0));
			d         = a + _md5_rotateLeft(d + _md5_I(a, b, c) + X[_idx(1 + 4 * i)] + T(48 + 1 + 4 * i), s(4, 1));
			c         = d + _md5_rotateLeft(c + _md5_I(d, a, b) + X[_idx(2 + 4 * i)] + T(48 + 2 + 4 * i), s(4, 2));
			b         = c + _md5_rotateLeft(b + _md5_I(c, d, a) + X[_idx(3 + 4 * i)] + T(48 + 3 + 4 * i), s(4, 3));
		}

		//Add the tf'd values to the digest
		digest[0] += a;
		digest[1] += b;
		digest[2] += c;
		digest[3] += d;


		//printf("process MD5 end\n");
		//use the processMD5 function to process the message.
		//value is thrown by reference.
		//return;
	}


}// LazySpellChecker

