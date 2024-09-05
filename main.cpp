#include "LazySpellCheckerHeader.h"

int main() {

	const auto estimatedVocabularySize = 5;
	LazySpellChecker::SpellChecker sc;

	std::vector<std::string> testWords = {"hello", "world", "Kemodora", "is", "wonderful"};

	for(auto& w : testWords)
	{
		std::cout << "Checking word spellings :: " << w << std::endl;
		if (sc.check(w)) {
			std::cout << "\tWord found in dictionary" << std::endl;
		} else {
			std::cout << "\tWord not found in dictionary" << std::endl;
		}
	}
	return 0;

}
