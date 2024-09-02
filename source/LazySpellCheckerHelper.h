//
// Created by deccauvw@github on 2024-09-01.
//

#ifndef LAZYBLOOMFILTERS_LAZYSPELLCHECKERHELPER_H
#define LAZYBLOOMFILTERS_LAZYSPELLCHECKERHELPER_H
#pragma once
#include <stdint.h>
#include <array>

namespace LazySpellChecker
{
	namespace Constants
	{
		inline const char *const k_defaultDictionaryFilename = "wordlist.txt";
		inline constexpr auto k_defaultDictionarySize = 338882;
		inline constexpr auto k_defaultMd5HashBufferNumber = 4;
		//inline constexpr auto k_defaultMd5HashProcessBlocksBitSize = 512;
		inline std::array<uint32_t, k_defaultMd5HashBufferNumber> k_Md5StateVariables = {
				0x67452301,
				0xedfcba45,
				0x98cbadfe,
				0x10325476
		};

	}
}
#endif //LAZYBLOOMFILTERS_LAZYSPELLCHECKERHELPER_H

