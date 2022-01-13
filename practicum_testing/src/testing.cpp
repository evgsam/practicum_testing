#include "log_duration.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

using namespace std;

// функция анализирует данные телескопа, определяя, сколько сильных сигналов
// зафиксировано по каждому направлению
vector<int> ComputeStatistics(const vector<string>& vs, int n) {
    int m = vs.size();
    vector<int> result(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            // прибавляем 1, если сигнал не менее 'K'
            result[i] += (vs[j][i] >= 'K' ? 1 : 0);
        }
    }

    return result;
}

vector<int> ReverseVector4(const vector<int> &source_vector) {
	vector<int> res;
	res.reserve(source_vector.size());
	for (auto iterator = source_vector.rbegin();
			iterator != source_vector.rend(); ++iterator) {
		res.push_back(*iterator);
	}
	return res;
}
vector<int> ComputeStatistics2(const vector<string>& vs, int n) {
    int m = vs.size();
    vector<int> result(n);

    // теперь первым идёт цикл по j
    for (int j = 0; j < m; ++j) {
        for (int i = 0; i < n; ++i) {
            // прибавляем 1, если сигнал не менее 'K'
            result[i] += (vs[j][i] >= 'K' ? 1 : 0);
        }
    }

    return result;
}

void AppendRandom(vector<int> &v, int n) {
	for (int i = 0; i < n; ++i) {
		v.push_back(rand() % 2);
	}
    return result;
}

void Operate() {
	vector<int> random_bits;
    uint64_t vect_size = 0;
	cin >> vect_size;
    
	//static const int N = vect_size;
	{
		AppendRandom(random_bits, vect_size);
	}
string GetRandomString(int size) {
    static mt19937 engine;
    uniform_int_distribution<int> distribution('A', 'Z');
string GetRandomString(int size) {
    static mt19937 engine;
    uniform_int_distribution<int> distribution('A', 'Z');

	vector<int> reversed_bits;
	if (vect_size <= 100000) {
		{
			LOG_DURATION("Naive"s);
			reversed_bits = ReverseVector(random_bits);
		}
		{
			LOG_DURATION("Good"s);
			reversed_bits = ReverseVector2(random_bits);
		}
	}
    string res(size, ' ');
    for (char& c : res) {
        c = char(distribution(engine));
    }
    string res(size, ' ');
    for (char& c : res) {
        c = char(distribution(engine));
    }
    string res(size, ' ');
    for (char& c : res) {
        c = char(distribution(engine));
    }
	if (vect_size > 100000) {
		{
			LOG_DURATION("Good"s);
			reversed_bits = ReverseVector2(random_bits);
		}
		{
			LOG_DURATION("Best"s);
			reversed_bits = ReverseVector3(random_bits);
		}
		{
			LOG_DURATION("Your"s);
			reversed_bits = ReverseVector4(random_bits);
		}
	}
}

int main() {
    vector<string> data;

    for (int i = 0; i < 20; ++i) {
        data.push_back(GetRandomString(20));
    }

    vector<int> statistics;
    {
        LOG_DURATION("ComputeStatistics"s);
        statistics = ComputeStatistics(data, 20);
    }

    cout << "Всего сильных сигналов: "s << accumulate(statistics.begin(), statistics.end(), 0) << endl;
}
