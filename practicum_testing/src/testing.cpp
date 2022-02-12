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
	Translator() = default;
	void Add(std::string_view source, std::string_view target) {
		/*lang1tolang2_.insert_or_assign(target, source);
		lang2tolang1_.insert_or_assign(source, target);
		*/
		words_.push_back(std::string{source});
		words_.push_back(std::string{target});
	}
	std::string_view TranslateForward(std::string_view source) const{
		auto it =lang1tolang2_.find(source);
		return it->second;;
	}
	std::string_view TranslateBackward(std::string_view target) const{
		auto it =lang2tolang1_.find(target);
		return it->second;
	}

private:
	std::map<std::string_view, std::string_view> lang1tolang2_;
	std::map<std::string_view, std::string_view> lang2tolang1_;
	std::vector<std::string> words_;
};

void TestSimple() {
	Translator translator;
	translator.Add(std::string("okno"s), std::string("window"s));
	translator.Add(std::string("stol"s), std::string("table"s));

	std::cout<<translator.TranslateForward("okno"s);
	/*assert(translator.TranslateForward("okno"s) == "window"s);
	assert(translator.TranslateBackward("table"s) == "stol"s);
	assert(translator.TranslateForward("table"s) == ""s);
	*/
}

int main() {
	TestSimple();
	return 0;
}
