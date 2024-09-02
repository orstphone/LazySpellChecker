//
// Created by deccauvw@github on 2024-09-01.
//
#pragma once
#include "HashFunctions.h"

#include <cstring> //for memcpy>

namespace LazySpellChecker {
	uint32_t HashFunctions::hash(const std::string &key, uint32_t tableSize) {
		auto hashValue = _MD5(key, tableSize);
		hashValue %= tableSize;
		return hashValue;
	}

	uint32_t HashFunctions::_MD5(const std::string &key, uint32_t tableSize) {
		uint32_t       lengthOfPaddingBitsCoefficient = static_cast<int>((key.length() + 64) / 512);
		const uint32_t appendingBitsSize              = 64;
		//uint32_t       AppendedBitsSize               = lengthOfPaddingBitsCoefficient * 512 - appendingBitsSize;

		//padding bits
		auto md5_paddedSequence = _md5_paddingBits(key);
		printf("padded Sequence done\n");


		//process rounds
		auto extract_word_from_md5_buffer =
				     [](std::vector<uint8_t>& data, size_t ofs)->uint32_t
				     {
					     return (data[ofs + 0] << 24) | (data[ofs + 1] << 16) | (data[ofs + 2] << 8) | data[ofs + 3];
				     };
		printf("extract_word_from_md5_buffer done\n");

		//initialize MD Buffer
		std::vector<uint32_t>      md5_buffer(LazySpellChecker::Constants::k_defaultMd5HashBufferNumber);
		for (uint32_t i = 0; i < LazySpellChecker::Constants::k_defaultMd5HashBufferNumber; i++) {
			md5_buffer[i] = LazySpellChecker::Constants::k_Md5StateVariables[i];
		}

		//extract word from md5 buffer
		auto word1 = extract_word_from_md5_buffer(md5_paddedSequence, 0);
		auto word2 = extract_word_from_md5_buffer(md5_paddedSequence, 4);


		//compute rounds from 1 to 4
		auto hashValue = _md5_processRoundsBlockWise(key);
		return 0;
	}


	//======================================= F G H I FUNCTIONS
	uint32_t HashFunctions::_md5_processRoundsBlockWise(const uint32_t word1, const uint32_t word2, std::vector<uint32_t> &md5_buffer) {
		auto resultF = _md5_F(word1, word2, md5_buffer[0]);
		auto resultG = _md5_G(word1, word2, md5_buffer[1]);
		auto resultH = _md5_H(word1, word2, md5_buffer[2]);
		auto resultI = _md5_I(word1, word2, md5_buffer[3]);

		//take input as initialize MD buffer ie ABCD
		//e.g. B will be fed in C, vice versa
		md5_buffer[2] = md5_buffer[1];
		return 0;
	}

	//this returns padded char-wise 8bit sequence of the string for the md5 hash digestion prep
	std::vector<uint8_t> HashFunctions::_md5_paddingBits(const std::string &key) {
		//padding bits
		//each character of the string is converted to a byte and stored in a vector
		std::vector<uint8_t> message(key.begin(), key.end());

		//append a single '1' bit followed by seven bits of zeros.
		uint32_t originalLengthBits = message.size() * 8;
		message.push_back(0x80);

		//append 0 bits until the length is 64b short of a multiple of 512
		while(message.size() * 8 % 512 != 512 - 64)
			message.push_back(0x00);

		//append the original length in bits as 64b int. (little endian){
		for(auto i = 0; i < 8; ++i){
			message.push_back(static_cast<uint8_t>(originalLengthBits & 0xFF));
			originalLengthBits >>= 8;
		}

		return message;
	}

	//A to B (the F Fn)(1st round)
	uint32_t HashFunctions::_md5_F(uint32_t x, uint32_t y, uint32_t z) {
		return (x & y) | (~x & z);
	}

	uint32_t HashFunctions::_md5_G(uint32_t x, uint32_t y, uint32_t z) {
		return (x & z) | (y & ~z);
	}

	uint32_t HashFunctions::_md5_H(uint32_t x, uint32_t y, uint32_t z) {
		return (x^ y ^ z);
	}

	uint32_t HashFunctions::_md5_I(uint32_t x, uint32_t y, uint32_t z) {
		return (y^ (x | ~z));
	}

	uint32_t HashFunctions::_md5_rotateLeft(uint32_t x, uint32_t n) {
		return 0;
	}


}// LazySpellChecker

