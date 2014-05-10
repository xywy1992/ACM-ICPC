template<class T>
struct BIT {
	static const int VAL_MAX = 1 << 20;
	T a[VAL_MAX + 1];
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
		for (int i = idx; i <= VAL_MAX; i += (i & -i)) {
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
