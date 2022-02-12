#include "log_duration.h"
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>
#include <map>

using namespace std;

class Translator {
public:
	void Add(string_view source, string_view target);
	string_view TranslateForward(string_view source) const;
	string_view TranslateBackward(string_view target) const;

private:
	map<string_view,string_view> lang1tolang2_;
	map<string_view,string_view> lang2tolang1_;
};

void TestSimple() {
	Translator translator;
	translator.Add(string("okno"s), string("window"s));
	translator.Add(string("stol"s), string("table"s));

	assert(translator.TranslateForward("okno"s) == "window"s);
	assert(translator.TranslateBackward("table"s) == "stol"s);
	assert(translator.TranslateForward("table"s) == ""s);
}

int main() {
	TestSimple();
	return 0;
}
