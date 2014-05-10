#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

#define PB push_back

const int N_MAX = 65537;
int n, a[N_MAX];
std::vector<int> values;
long long ans;

template<class T>
struct BIT {
	static const int VAL_MAX = 65537;
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
BIT<int> bit;

int main() {
	while (scanf("%d", &n) == 1) {
		values.clear();
		for (int i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
			values.PB(a[i]);
		}
		std::sort(values.begin(), values.end());
		values.erase(std::unique(values.begin(), values.end()), values.end());
		ans = 0;
		bit.init();
		for (int i = 0; i < n; ++i) {
			int at = std::lower_bound(values.begin(), values.end(), a[i])
					- values.begin();
			ans += i - bit.read(at + 1);
			bit.update(at + 1, 1);
		}
		printf("%I64d\n", ans);
	}
	return 0;
}
