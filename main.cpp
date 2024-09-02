#include "LazySpellCheckerHeader.h"

int main() {

	LazySpellChecker::SpellChecker sc(10000, 5);

	std::vector<std::string> testWords = {"hello", "world"};

	for(auto& w : testWords)
	{
		std::cout << "Checking word: " << w << std::endl;
		if (sc.check(w)) {
			std::cout << "Word found in dictionary" << std::endl;
		} else {
			std::cout << "Word not found in dictionary" << std::endl;
		}
	}
	return 0;

}
