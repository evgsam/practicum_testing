#include <chrono>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "log_duration.h"

using namespace std;

vector<int> ReverseVector(const vector<int> &source_vector) {
	vector<int> res;
	for (int i : source_vector) {
		res.insert(res.begin(), i);
	}
	return res;
}

vector<int> ReverseVector2(const vector<int> &source_vector) {
	vector<int> res;
	for (auto iterator = source_vector.rbegin();
			iterator != source_vector.rend(); ++iterator) {
		res.push_back(*iterator);
	}
	return res;
}

vector<int> ReverseVector3(const vector<int> &source_vector) {
	vector<int> res;
	res.reserve(source_vector.size());
	for (auto iterator = source_vector.rbegin();
			iterator != source_vector.rend(); ++iterator) {
		res.push_back(*iterator);
	}
	return res;
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

int CountPops(const vector<int> &source_vector, int begin, int end) {
	int res = 0;
	for (int i = begin; i < end; ++i) {
		if (source_vector[i]) {
			++res;
		}
	}
	return res;
}

void AppendRandom(vector<int> &v, int n) {
	for (int i = 0; i < n; ++i) {
		v.push_back(rand() % 2);
	}
}

void Operate() {
	vector<int> random_bits;
    uint64_t vect_size = 0;
	cin >> vect_size;
    
	//static const int N = vect_size;
	{
		AppendRandom(random_bits, vect_size);
	}

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
	Operate();
}
