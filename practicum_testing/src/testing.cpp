#include "log_duration.h"

#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

using namespace std;

vector<float> ComputeAvgTemp(const vector<vector<float>> &vs) {
	if (vs.empty())
		return {};
	int m = vs.size();

	vector<float> result(m);
	vector<float> sum(m);
	vector<int> count(m);

	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < vs[i].size(); ++j) {
			float c = vs[j][i];
			sum[i] += (c > 0 ? c : 0);
			count[i]+= (c > 0 ? 1 : 0);
		}
		result[i]+=(count[i] > 0 ? sum[i] / count[i] : 0);
	}
	return result;

}

vector<float> GetRandomVector(int size) {
	static mt19937 engine;
	uniform_real_distribution<float> d(-100, 100);

	vector<float> res(size);
	for (int i = 0; i < size; ++i) {
		res[i] = d(engine);
	}

	return res;
}

int main() {
	vector<vector<float>> data;
	data.reserve(10);

	for (int i = 0; i < 5; ++i) {
		data.push_back(GetRandomVector(5));
	}

	vector<float> avg;
	{
		LOG_DURATION("ComputeAvgTemp"s);
		avg = ComputeAvgTemp(data);
	}

	cout << "Total mean: "s
			<< accumulate(avg.begin(), avg.end(), 0.f) / avg.size() << endl;
}
