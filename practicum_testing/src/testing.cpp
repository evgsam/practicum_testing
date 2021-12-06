#include <string>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Rational {
public:
	Rational(int numerator = 0) {
		numerator_ = numerator;
		denominator_ = 1;
	}

	Rational(int numerator, int denominator) {
		if (denominator < 0) {
			numerator_ = (0 - numerator) / gcd(numerator, denominator);
			denominator_ = abs(denominator) / gcd(numerator, denominator);
		} else {
			numerator_ = numerator / gcd(numerator, denominator);
			denominator_ = denominator / gcd(numerator, denominator);
		}
	}

	int Numerator() const {
		return numerator_;
	}

	int Denominator() const {
		return denominator_;
	}

private:
	int numerator_ = 0;
	int denominator_ = 1;
};

Rational Add(Rational r1, Rational r2) {
	int numerator = r1.Numerator() * r2.Denominator()
			+ r2.Numerator() * r1.Denominator();
	int denominator = r1.Denominator() * r2.Denominator();

	// Создаём и возвращаем дробь с заданным числителем и знаменателем
	return Rational { numerator, denominator };
}

int main() {
	Rational zero;     // Дробь 0/1 = 0
	const Rational seven(7); // Дробь 7/1 = 7
	const Rational one_third(-1, 3); // Дробь 1/3

	vector<Rational> numbers;
	numbers.push_back(Rational { 7, 8 });

	Rational sum = Add(Rational { 1, 6 }, one_third);
	// Выведет 1/2
	if (sum.Numerator() < 0) {
		cout << "(" << sum.Numerator() << ")" << "/" << sum.Denominator();
	} else {
		cout << sum.Numerator() << "/" << sum.Denominator();
	}

	/*const Rational my_rational(8, 6);
	 cout << my_rational.Numerator() << "/" << my_rational.Denominator() << endl;
	 */

}

