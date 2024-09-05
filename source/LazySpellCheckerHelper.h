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

		inline constexpr auto k_desiredFalsePositiveRate = 0.01;

	}
}
#endif //LAZYBLOOMFILTERS_LAZYSPELLCHECKERHELPER_H

