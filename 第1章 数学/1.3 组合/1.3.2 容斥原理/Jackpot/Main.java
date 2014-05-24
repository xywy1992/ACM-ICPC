import java.math.BigInteger;
import java.util.Scanner;

class Fraction {
	BigInteger num, den;

	BigInteger gcd(BigInteger a, BigInteger b) {
		return b.signum() != 0 ? gcd(b, a.mod(b)) : a;
	}

	Fraction() {
		this.num = BigInteger.ZERO;
		this.den = BigInteger.ONE;
	}

	Fraction(BigInteger num, BigInteger den) {
		if (den.signum() == -1) {
			num = num.multiply(BigInteger.valueOf(-1));
			den = den.multiply(BigInteger.valueOf(-1));
		}
		assert den.signum() != 0;
		BigInteger g = gcd(num.abs(), den);
		this.num = num.divide(g);
		this.den = den.divide(g);
	}

	Fraction add(Fraction o) {
		return new Fraction(num.multiply(o.den).add(den.multiply(o.num)),
				den.multiply(o.den));
	}

	void out() {
		System.out.println(num + "\n" + den);
	}
};

class Solver {
	int n;
	BigInteger[] a;

	BigInteger gcd(BigInteger a, BigInteger b) {
		return b.signum() != 0 ? gcd(b, a.mod(b)) : a;
	}

	BigInteger lcm(BigInteger a, BigInteger b) {
		return a.multiply(b).divide(gcd(a, b));
	}

	Fraction dfs(int dep, int cnt, BigInteger cur) {
		if (dep == n) {
			if (cnt == 0) {
				return new Fraction();
			} else if (cnt % 2 == 1) {
				return new Fraction(BigInteger.valueOf(+1), cur);
			} else {
				return new Fraction(BigInteger.valueOf(-1), cur);
			}
		} else {
			return dfs(dep + 1, cnt + 1, lcm(a[dep], cur)).add(
					dfs(dep + 1, cnt, cur));
		}
	}

	void go(int n, BigInteger[] a) {
		this.n = n;
		this.a = a;
		dfs(0, 0, BigInteger.ONE).out();
	}
}

public class Main {
	public static void main(String[] args) {
		Scanner reader = new Scanner(System.in);
		Solver solver = new Solver();
		while (reader.hasNext()) {
			int n = reader.nextInt();
			BigInteger[] a = new BigInteger[n];
			for (int i = 0; i < n; ++i) {
				a[i] = reader.nextBigInteger();
			}
			solver.go(n, a);
		}
		reader.close();
	}
}
