#include "log_duration.h"
#include "my_assert.h"
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>
#include <map>
#include <string_view>
#include <array>

using namespace std::literals::string_literals;

class Translator {
public:
	Translator() = default;
	void Add(std::string_view source, std::string_view target) {
		words_[size_] = std::string { source };
		words_[size_ + 1] = std::string { target };

		std::string_view strv_source = std::string_view(words_[size_++]);
		std::string_view strv_target = std::string_view(words_[size_++]);

		//lang1tolang2_[size_]=(strv_source, strv_target);
		//lang2tolang1_[size_++]=(strv_target, strv_source);

		lang1tolang2_[strv_source]=strv_target;
		lang2tolang1_[strv_target]=strv_source;
		//lang1tolang2_.insert_or_assign(strv_source, strv_target);
		//lang2tolang1_.insert_or_assign(strv_target, strv_source);
	}
	std::string_view TranslateForward(std::string_view source) const {
		auto it = lang1tolang2_.find(source);
		if (it==lang1tolang2_.end()){
			return ""s;
		}
		else{
			return it->second;;
		}

	}
	std::string_view TranslateBackward(std::string_view target) const {
		auto it = lang2tolang1_.find(target);
		if (it==lang2tolang1_.end()){
			return ""s;
		}
		else{
			return it->second;;
		}
	}

private:
	std::map<std::string_view, std::string_view> lang1tolang2_;
	std::map<std::string_view, std::string_view> lang2tolang1_;
	std::array<std::string, 100> words_;
	size_t size_ = 0;
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
