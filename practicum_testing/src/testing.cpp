#include <algorithm>
#include <iostream>
#include <vector>
#include "log_duration.h"

using namespace std;

// функция возвращает true, если векторы из одинаковых элементов
// перепишите эту функцию, улучшив её асимптотическую сложность
bool TestPermut(const vector<int> &v1, const vector<int> &v2) {
	if (v1.size() != v2.size()) {
		return false;
	}
	vector<int> v3=v1;
	vector<int> v4=v2;
	sort(v3.begin(), v3.end());
	sort(v4.begin(), v4.end());
	for (auto i=0;i<v1.size();++i){
		if (v3[i]!=v4[i]){
			return false;
		}
	}
	return true;
}

int main() {
	int n;
	cin >> n;
	vector<int> v1, v2;
	v1.reserve(n);
	v2.reserve(n);

	for (int i = 0; i < n; ++i) {
		v1.push_back(rand());
		v2.push_back(rand());
	}

	// оба вектора случайны, вряд ли они совпадут
	cout << "Random vectors match? "s << flush;
	cout << (TestPermut(v1, v2) ? "Yes"s : "No"s) << endl;

	// делаем один перестановкой другого явным образом
	v2 = v1;
	random_shuffle(v2.begin(), v2.end());
	cout << "Permuted vectors match? "s << flush;
	cout << (TestPermut(v1, v2) ? "Yes"s : "No"s) << endl;
}
