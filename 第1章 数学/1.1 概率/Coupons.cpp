#include <algorithm>
#include <cstdio>
#include <cassert>

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

	int bitCnt(T val) {
		int cnt = 0;
		while (val) {
			val /= 10, cnt++;
		}
		return cnt;
	}
	void out(char alpha, int n) {
		for (int i = 0; i < n; ++i) {
			putchar(alpha);
		}
	}
	void out() {
		if (den == 1) {
			printf("%lld\n", num);
		} else {
			out(' ', bitCnt(num / den)), printf(" %lld\n", num % den);
			printf("%lld ", num / den), out('-', bitCnt(den)), puts("");
			out(' ', bitCnt(num / den)), printf(" %lld\n", den);
		}
	}
};

typedef Fraction<long long> F;
int n;

int main() {
	while (scanf("%d", &n) == 1) {
		F ans = F();
		for (int i = 0; i < n; ++i) {
			ans = ans + F(1, n - i);
		}
		ans = ans * F(n, 1);
		ans.out();
	}
	return 0;
}

