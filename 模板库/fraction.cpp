template<class T>
struct Fraction {
	T num, den;
	T gcd(T a, T b) {
		return b ? gcd(b, a % b) : a;
	}
	Fraction(T num = 0, T den = 1) {
		if (den < 0) {
			num = -num;
			den = -den;
		}
		assert(den != 0);
		T g = gcd(std::abs(num), den);
		this->num = num / g;
		this->den = den / g;
	}
	Fraction operator+(const Fraction & o) const {
		return Fraction(num * o.den + den * o.num, den * o.den);
	}
	Fraction operator-(const Fraction & o) const {
		return Fraction(num * o.den - den * o.num, den * o.den);
	}
	Fraction operator*(const Fraction & o) const {
		return Fraction(num * o.num, den * o.den);
	}
	Fraction operator/(const Fraction & o) const {
		return Fraction(num * o.den, den * o.num);
	}
	bool operator<(const Fraction & o) const {
		return num * o.den < den * o.num;
	}
	bool operator==(const Fraction & o) const {
		return num * o.den == den * o.num;
	}
};

