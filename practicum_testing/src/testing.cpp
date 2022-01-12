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

string GetRandomString(int size) {
    static mt19937 engine;
    uniform_int_distribution<int> distribution('A', 'Z');

    string res(size, ' ');
    for (char& c : res) {
        c = char(distribution(engine));
    }

    return res;
}

int main() {
    vector<string> data;

    for (int i = 0; i < 5000; ++i) {
        data.push_back(GetRandomString(5000));
    }

    vector<int> statistics;
    {
        LOG_DURATION("ComputeStatistics"s);
        statistics = ComputeStatistics(data, 5000);
    }

    cout << "Всего сильных сигналов: "s << accumulate(statistics.begin(), statistics.end(), 0) << endl;
}
