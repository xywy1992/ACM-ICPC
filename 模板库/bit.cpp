#include <cstring>

template<int N, class T>
struct BIT {
	T a[N + 1];
	void init() {
		memset(a, 0, sizeof(a));
	}
	T read(int idx) {
		T sum = 0;
		for (int i = idx; i; i -= (i & -i)) {
			sum += a[i];
		}
		return sum;
	}
	void update(int idx, T val) {
		for (int i = idx; i <= N; i += (i & -i)) {
			a[i] += val;
		}
	}
	T readSingle(int idx) {
		T sum = a[idx];
		for (int i = idx - 1, j = idx - (idx & -idx); i != j; i -= (i & -i)) {
			sum -= a[i];
		}
		return sum;
	}
};
