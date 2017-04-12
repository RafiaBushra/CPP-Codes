#include<iostream>
#include<iomanip>

using namespace std;
class Fractional {
public:
	Fractional(int numerator, int denominator);
	int gcd(Fractional second);
	Fractional addition(Fractional second);
	Fractional subtraction(Fractional second);
	Fractional multiplication(Fractional second);
	Fractional division(Fractional second);
	void print();
private:
	int numerator_;
	int denominator_;
};

Fractional::Fractional(int numerator, int denominator) {
	numerator_ = numerator;
	denominator_ = denominator;
}

int Fractional::gcd(Fractional second) {
	int gcd_ = 0;
	bool flag = false;
	if (denominator_ % second.denominator_ == 0) {
		return denominator_;
	}
	else if (second.denominator_ % denominator_ == 0) {
		return second.denominator_;
	}
	for (int i = 2; i <= denominator_ && i <= second.denominator_; ++i) {
		if (denominator_ % i == 0 && second.denominator_ % i == 0) {
			gcd_ = i;
			flag = true;
		}
	}
	if (flag)
		return gcd_;
	else
		return denominator_ * second.denominator_;
}

Fractional Fractional::addition(Fractional second) {
	Fractional result(1, 1);
	result.denominator_ = gcd(second);
	result.numerator_ = numerator_ * (result.denominator_ / denominator_) + second.numerator_ * (result.denominator_ / second.denominator_);
	if (result.denominator_ % result.numerator_ == 0) {
		result.denominator_ /= result.numerator_;
		result.numerator_ = 1;
	}
	return result;
}

Fractional Fractional::subtraction(Fractional second) {
	Fractional result(1, 1);
	result.denominator_ = gcd(second);
	result.numerator_ = numerator_ * (result.denominator_ / denominator_) - second.numerator_ * (result.denominator_ / second.denominator_);
	if (result.denominator_ % result.numerator_ == 0) {
		result.denominator_ /= result.numerator_;
		result.numerator_ = 1;
	}
	return result;
}

Fractional Fractional::multiplication(Fractional second) {
	Fractional result(1, 1);
	result.numerator_ = numerator_ * second.numerator_;
	result.denominator_ = denominator_ * second.denominator_;
	if (result.denominator_ % result.numerator_ == 0) {
		result.denominator_ /= result.numerator_;
		result.numerator_ = 1;
	}
	return result;
}

Fractional Fractional::division(Fractional second) {
	Fractional inverse(second.denominator_, second.numerator_);
	return multiplication(inverse);
}

void Fractional::print() {
	for (int i = 2; i <= denominator_; i++) {
		if (numerator_ > denominator_) {
			if (numerator_ / i == denominator_) {
				numerator_ = denominator_;
				denominator_ = 1;
				break;
			}
		}
		else if (numerator_ < denominator_) {
			if (denominator_ / i == numerator_) {
				denominator_ = numerator_;
				numerator_ = 1;
				break;
			}
		}
		else {
			numerator_ = 1;
			denominator_ = 1;
			break;
		}
	}
	cout << numerator_ << "/" << denominator_ << endl;
}

int main() {
	Fractional f1(4, 5);
	Fractional f2(5, 8);
	Fractional f3(1, 8);
	Fractional f4(2, 3);
	Fractional f5(1, 7);
	f1.addition(f3).subtraction(f2).division(f4.multiplication(f5)).print();
	return 0;
}