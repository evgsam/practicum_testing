#include <iostream>
#include <string>

using namespace std;

template<typename F>
string BruteForceInternal(F check, const string &begin, int n) {
	if (n == 5) {
		if (check(begin)) {
			return begin;
		} else {
			return ""s;
		}
	}

}

template<typename F>
string BruteForce(F check) {
	string current_pas="AAAAA"s;
	string result=""s;
	for (char a = 'A'; a <= 'Z'; a++) {
		current_pas[0]=a;
		for (char b = 'A'; b <= 'Z'; b++) {
			current_pas[1]=b;
			for (char c = 'A'; c <= 'Z'; c++) {
				current_pas[2]=c;
				for (char d = 'A'; d <= 'Z'; d++) {
					current_pas[3]=d;
					for (char e = 'A'; e <= 'Z'; e++) {
						current_pas[4]=e;
						if (check(current_pas)) {
							result=current_pas;
						}
					}
				}
			}
		}
	}
	return result;
}

int main() {
	string pass = "ARTUR"s;
	auto check = [pass](const string &s) {
		return s == pass;
	};
	cout << BruteForce(check) << endl;
}
