//
// Created by deccauvw@github on 2024-09-01.
//

#ifndef LAZYBLOOMFILTERS_LAZYSPELLCHECKERHELPER_H
#define LAZYBLOOMFILTERS_LAZYSPELLCHECKERHELPER_H
#include <stdint.h>
#include <string>
#include <array>

namespace LazySpellChecker
{
	namespace Constants
	{
		inline const char *const k_defaultDictionaryFilename = "wordlist.txt";
		inline constexpr auto k_defaultDictionarySize = 350000;

		inline constexpr auto k_defaultMd5HashBufferNumber = 4;
		inline constexpr auto k_defaultMd5HashProcessBlocksBitSize = 512;
		std::array<uint32_t, k_defaultMd5HashBufferNumber> k_defaultMd5StateVariables = {0x67452301, 0xedfcba45, 0x98cbadfe, 0x10325476};

	}

	class ProcessRoundsBlockwise{
	public:
	private:
		ProcessRoundsBlockwise() = default;

		~ProcessRoundsBlockwise() = default;

		//F function
		virtual void process1(const uint32_t &input, size_t tableSize)
		{

		}
	};
}
#endif //LAZYBLOOMFILTERS_LAZYSPELLCHECKERHELPER_H

