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


bool IsPowOfTwo(int num) {
	if (num == 0) {
		return false;
	}
	if (num == 1) {
		return true;
	}
	if (num % 2 == 0) {
		return IsPowOfTwo(num/2);
	}
	return false;
}


int main() {
    int result = IsPowOfTwo(3);
    cout << result << endl;
}
