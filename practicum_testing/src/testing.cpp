//#include "search_server.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <cmath>
#include <cassert>

using namespace std;

/*
 * Разработайте для класса Rational конструктор по умолчанию,
 * который задаёт значение дроби, равное 0/1.
 */

class Rational {
public:
	Rational(){
		SetNumerator(0);
		SetDenominator(1);
	}

    int Numerator() const {
        return numerator_;
    }

    int Denominator() const {
        return denominator_;
    }

    void SetNumerator(int numerator) {
        numerator_ = numerator;
    }

    void SetDenominator(int denominator) {
        if (denominator != 0) {
            denominator_ = denominator;
        }
    }

private:
    int numerator_;
    int denominator_;
};

int main(){
    Rational r;
    cout << r.Numerator() << "/" << r.Denominator() << endl;
	return 0;
}
