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
void EraseAndPrint(Container& container, Iterator it) {
    auto it_to_erased = container.erase(it);
    PrintRange(container.begin(), it_to_erased);
    PrintRange(it_to_erased, container.end());
}

int main() {
    set<string> langs = {"Python"s, "Java"s, "C#"s, "Ruby"s, "C++"s};
    EraseAndPrint(langs, langs.begin());
}
