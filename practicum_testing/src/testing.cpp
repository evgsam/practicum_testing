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
		numerator_ = numerator_ * r.denominator_ + r.numerator_ * denominator_;
		denominator_ *= r.denominator_;
		Normalize();
		return *this;
	}

	Rational& operator-=(Rational r) {
		numerator_ = numerator_ * r.denominator_ - r.numerator_ * denominator_;
		denominator_ *= r.denominator_;
		Normalize();
		return *this;
	}
	Rational& operator*=(Rational r) {
		numerator_ *= r.numerator_;
		denominator_ *= r.denominator_;
		Normalize();
		return *this;
	}
	Rational& operator/=(Rational r) {
		// Результат операции сохраняется в текущем экземпляре класса
		numerator_ *= r.denominator_;
		denominator_ *= r.numerator_;
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

ostream& operator<<(ostream &output, Rational rational) {
	return output << rational.Numerator() << '/' << rational.Denominator();
}

istream& operator>>(istream &input, Rational &rational) {
	int numerator;
	int denominator;
	char slash;
	if ((input >> numerator) && (input >> slash) && (slash == '/')
			&& (input >> denominator)) {
		rational = Rational { numerator, denominator };
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
	return left += right;
}

Rational operator-(Rational left, Rational right) {
	return left -= right;
}

Rational operator*(Rational left, Rational right) {
	return left *= right;
}

Rational operator/(Rational left, Rational right) {
	return left /= right;
}

Rational operator+(Rational r) {
	return {r};
}

Rational operator-(Rational r) {
	return {-r.Numerator(),r.Denominator()};
}

bool operator==(Rational left, Rational right) {
	return left.Numerator() == right.Numerator()
			&& left.Denominator() == right.Denominator();
}

bool operator!=(Rational left, Rational right) {
	return !(left == right);
}

bool operator<(Rational left, Rational right) {
	return left.Numerator() * right.Denominator()
			< right.Numerator() * left.Denominator();
}

bool operator<=(Rational left, Rational right) {
	return left.Numerator() * right.Denominator()
			< right.Numerator() * left.Denominator() || left==right;
}

bool operator>(Rational left, Rational right) {
	return left.Numerator() * right.Denominator()
			> right.Numerator() * left.Denominator();
}
bool operator>=(Rational left, Rational right) {
	return left.Numerator() * right.Denominator()
			> right.Numerator() * left.Denominator()||left==right;
}


int main() {
	cout << "Введите две обыкновенные дроби в формате x/y:"s << endl;
	Rational a, b;
	cin >> a >> b;

	// Аналогично if (b != Rational{0})
	if (a <= b) {
		cout << "a <= b" << endl;
	}
	if (a > b) {
		cout << "a >b" << endl;
	}

}

