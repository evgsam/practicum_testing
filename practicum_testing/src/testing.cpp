#include "log_duration.h"
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

using namespace std;

vector<string> SplitIntoWords(const string& text) {
    vector<string> words;
    string word;
    for (const char c : text) {
        if (c == ' ') {
            if (!word.empty()) {
                // обратите внимание на это место в коде
                // здесь мы каждый раз копируем найденное слово
                // в новый элемент в векторе
                words.push_back(word);
                word.clear();
            }
        } else {
            word += c;
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }
    return words;
}

/*vector<string_view> SplitIntoWordsView(const string& str) {
    vector<string_view> result;
    // 1
    int64_t pos = 0;
    // 2
    const int64_t pos_end = str.npos;
    // 3
    while (true) {
        // 4
        int64_t space = str.find(' ', pos);
        // 5
        result.push_back(space == pos_end ? str.substr(pos) : str.substr(pos, space - pos));
        // 6
        if (space == pos_end) {
            break;
        } else {
            pos = space + 1;
        }
    }

    return result;
}
*/
vector<string_view> SplitIntoWordsView(string_view str) {
    vector<string_view> result;
    while (true) {
        auto space = str.find(' ');
    	result.push_back(str.substr(0,space));
        if (space == str.npos) {
            break;
        } else {
            str.remove_prefix(space+1);
        }
    }

    return result;
}

string GenerateText() {
    const int SIZE = 10000000;
    string text(SIZE, 'a');
    for (int i = 100; i < SIZE; i += 100) {
        text[i] = ' ';
    }
    return text;
}

int main() {
    const string text = "a b";
    {
        LOG_DURATION("string");
        const auto words = SplitIntoWords(text);
        cout << words[0] << "\n";
    }
    {
        LOG_DURATION("string_view");
        const auto words = SplitIntoWordsView(text);
        cout << words[0] << "\n";
    }

    return 0;
}
