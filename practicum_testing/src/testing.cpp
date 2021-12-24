#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

uint64_t Factorial(int num) {
	int factorial = 1;
	if (0 != num) {
		factorial = Factorial(num - 2) * num;
	}
	return factorial;
}

uint64_t Fibonacci(int num) {
	if (num == 0) {
		return 0;
	}
	if (num == 1) {
		return 1;
	}
	return Fibonacci(num - 1) + Fibonacci(num - 2);
}

int main() {
	cout << Fibonacci(6) << endl;
}
