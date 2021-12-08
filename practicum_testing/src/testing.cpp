#include <string>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Rational {
public:
	Rational() = default;

	Rational(int numerator) :
			numerator_(numerator), denominator_(1) {
	}

	Rational(int numerator, int denominator) :
			numerator_(numerator), denominator_(denominator) {
		Normalize();
	}

	int Numerator() const {
		return numerator_;
	}

	int Denominator() const {
		return denominator_;
	}

	Rational& operator+=(Rational r) {
		// Результат операции сохраняется в текущем экземпляре класса
		numerator_ += r.numerator_;
		denominator_ += r.denominator_;
		Normalize();
		// return *this позволяет вернуть ссылку на текущий объект
		return *this;
	}

	Rational& operator-=(Rational r) {
		// Результат операции сохраняется в текущем экземпляре класса
		numerator_ -= r.numerator_;
		denominator_ -= r.denominator_;
		Normalize();
		// return *this позволяет вернуть ссылку на текущий объект
		return *this;
	}
	Rational& operator*=(Rational r) {
		// Результат операции сохраняется в текущем экземпляре класса
		numerator_ *= r.numerator_;
		denominator_ *= r.denominator_;
		Normalize();
		// return *this позволяет вернуть ссылку на текущий объект
		return *this;
	}
	Rational& operator/=(Rational r) {
		// Результат операции сохраняется в текущем экземпляре класса
		numerator_ /= r.numerator_;
		denominator_ /= r.denominator_;
		Normalize();
		// return *this позволяет вернуть ссылку на текущий объект
		return *this;
	}

private:
	void Normalize() {
		if (denominator_ < 0) {
			numerator_ = -numerator_;
			denominator_ = -denominator_;
		}
		const int divisor = gcd(numerator_, denominator_);
		numerator_ /= divisor;
		denominator_ /= divisor;
	}

	int numerator_ = 0;
	int denominator_ = 1;
};

ostream& operator<<(ostream& output, Rational rational) {
    return output << rational.Numerator() << '/' << rational.Denominator();
}

istream& operator>>(istream& input, Rational& rational) {
    int numerator;
    int denominator;
    char slash;
    if ((input >> numerator) && (input >> slash) && (slash == '/') && (input >> denominator)) {
        rational = Rational{numerator, denominator};
    }
    return input;
}

Rational Add(Rational r1, Rational r2) {
	int numerator = r1.Numerator() * r2.Denominator()
			+ r2.Numerator() * r1.Denominator();
	int denominator = r1.Denominator() * r2.Denominator();

	// Создаём и возвращаем дробь с заданным числителем и знаменателем
	return {numerator, denominator};
}

Rational operator+(Rational left, Rational right) {
	/*const int numerator = left.Numerator() * right.Denominator()
		+ right.Numerator() * left.Denominator();
	const int denominator = left.Denominator() * right.Denominator();

	return {numerator, denominator};
*/
	return left += right;
}

Rational operator-(Rational left, Rational right) {
	const int numerator = left.Numerator() * right.Denominator()
			- right.Numerator() * left.Denominator();
	const int denominator = left.Denominator() * right.Denominator();

	return {numerator, denominator};
}

Rational operator+(Rational r) {
	return {r};
}

Rational operator-(Rational r) {
	return {-r.Numerator(),r.Denominator()};
}

int main() {
	Rational r1, r2;

	cout << "Введите первую дробь: "s;
	cin >> r1;

	cout << "Введите вторую дробь: "s;
	cin >> r2;

	cout << "Их сумма равна: "s << r1 + r2 << endl;
	cout << "Их разница равна: "s << r1 - r2 << endl;

}

