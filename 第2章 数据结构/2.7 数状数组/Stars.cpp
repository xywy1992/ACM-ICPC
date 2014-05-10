#include <cstdio>
#include <cstring>
#include <utility>
#include <algorithm>

#define PII std::pair<int, int>
#define F first
#define S second

const int N_MAX = 15000;

template<class T>
struct BIT {
	static const int VAL_MAX = 32001;
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

int n, cnt[N_MAX];
PII pt[N_MAX];
BIT<int> bit;

int main() {
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; ++i) {
			scanf("%d %d", &pt[i].F, &pt[i].S);
		}
		memset(cnt, 0, sizeof(cnt));
		bit.init();
		for (int i = 0, j; i < n; i = j) {
			int c = 0;
			for (j = i; j < n && pt[j] == pt[i]; ++j) {
				c++;
			}
			c = 1, j = i + 1;
			cnt[bit.read(pt[i].F + 1)] += c;
			bit.update(pt[i].F + 1, c);
		}
		for (int i = 0; i < n; ++i) {
			printf("%d\n", cnt[i]);
		}
	}
	return 0;
}
