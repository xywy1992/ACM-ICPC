#include <algorithm>
#include <cstdio>
#include <iterator>
#include <utility>
#include <vector>

const int N = (int) (5e3);

typedef std::pair<int, int> PII;
typedef std::pair<PII, int> PIII;

#define MP std::make_pair
#define PB push_back
#define F first
#define S second

int n, m, weight;
char s[100];
PIII a[N];
std::vector<int> values;

template<int N>
struct DisjointSet {
	int p[N], w[N];
	void init(int n) {
		for (int i = 0; i < n; ++i) {
			p[i] = i;
			w[i] = 0;
		}
	}
	int getp(int i) {
		if (i == p[i]) {
			return i;
		} else {
			int j = getp(p[i]);
			w[i] = (w[i] + w[p[i]]) % 2;
			p[i] = j;
			return j;
		}
	}
	bool setp(int i, int j) {
		int x = getp(i);
		int y = getp(j);
		if (x == y) {
			return (w[i] + w[j]) % 2 == weight;
		}
		if (x < y) {
			p[x] = y;
			w[x] = (w[i] + w[j] + weight) % 2;
		} else {
			p[y] = x;
			w[y] = (w[i] + w[j] + weight) % 2;
		}
		return true;
	}
};

DisjointSet<N * 2> ds;

int find(int v) {
	return std::lower_bound(values.begin(), values.end(), v) - values.begin();
}

int solve() {
	ds.init(values.size());
	for (int i = 0; i < n; ++i) {
		int x = find(a[i].F.F - 1);
		int y = find(a[i].F.S);
		weight = a[i].S;
		if (!ds.setp(x, y)) {
			return i;
		}
	}
	return n;
}

int main() {
	while (scanf("%d", &m) == 1 && m != -1) {
		scanf("%d", &n);
		values.clear();
		for (int i = 0; i < n; ++i) {
			scanf("%d %d %s", &a[i].F.F, &a[i].F.S, s);
			a[i].S = (s[0] == 'e' ? 0 : 1);
			values.PB(a[i].F.F - 1);
			values.PB(a[i].F.S);
		}
		std::sort(values.begin(), values.end());
		values.erase(std::unique(values.begin(), values.end()), values.end());
		printf("%d\n", solve());
	}
	return 0;
}

