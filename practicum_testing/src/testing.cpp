#include "log_duration.h"
#include "my_assert.h"
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>
#include <map>

using namespace std::literals::string_literals;

class Translator {
public:
	void Add(std::string_view source, std::string_view target);
	std::string_view TranslateForward(std::string_view source) const;
	std::string_view TranslateBackward(std::string_view target) const;

private:
	std::map<std::string_view,std::string_view> lang1tolang2_;
	std::map<std::string_view,std::string_view> lang2tolang1_;
	std::vector<std::string> words;
};

void TestSimple() {
	Translator translator;
	translator.Add(std::string("okno"s), std::string("window"s));
	translator.Add(std::string("stol"s), std::string("table"s));

	assert(translator.TranslateForward("okno"s) == "window"s);
	assert(translator.TranslateBackward("table"s) == "stol"s);
	assert(translator.TranslateForward("table"s) == ""s);
}

int main() {
	TestSimple();
	return 0;
}
