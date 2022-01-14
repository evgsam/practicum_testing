#include "log_duration.h"

#include <iostream>

using namespace std;

class StreamUntier {
public:
	StreamUntier(istream &tied_before){
		tied_before_ = cin.tie(nullptr);
	}
	~StreamUntier(){
		cin.tie(tied_before_);
	}
	// добавьте конструктор, деструктор
	// и дополнительные поля класса при необходимости

private:
	ostream *tied_before_;
};

int main() {
	LOG_DURATION("\\n with tie"s);

	StreamUntier guard(cin);
	int i;
	while (cin >> i) {
		cout << i * i << "\n"s;
	}

	return 0;
}
