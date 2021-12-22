#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

template <typename It>
void PrintRange(It range_begin, It range_end) {
    for (auto it = range_begin; it != range_end; ++it) {
        cout << *it << " "s;
    }
    cout << endl;
}


template <typename Container, typename Iterator>
void EraseAndPrint(Container& container, Iterator iterator) {
	PrintRange(container.begin(), iterator);
	auto iter = find(container.begin(), container.end(), *iterator);
    auto it_begin=container.erase(iter);
	auto it_end=end(container);
	PrintRange(it_begin, it_end);
}


int main() {
    set<string> langs = {"Python"s, "Java"s, "C#"s, "Ruby"s, "C++"s};
    EraseAndPrint(langs, langs.begin());
}
