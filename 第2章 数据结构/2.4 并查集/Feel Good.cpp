#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

typedef long long lint;
typedef std::pair<int, int> PII;
typedef std::vector<PII>::reverse_iterator RIT;

#define PB push_back
#define MP std::make_pair
#define F first
#define S second

const int N = (int) (1e5);
int n, a[N];
std::vector<PII> at;
lint ans;
int minv, al, ar;

template<int N>
struct DisjointSet {
	int p[N], l[N], r[N];
	lint sum[N];
	void init(int n) {
		for (int i = 0; i < n; ++i) {
			l[i] = r[i] = p[i] = i;
			sum[i] = a[i];
			if ((lint) a[i] * a[i] > ans) {
				ans = (lint) a[i] * a[i];
				al = ar = i;
			}
		}
	}
	int getp(int i) {
		return i == p[i] ? i : (p[i] = getp(p[i]));
	}
	void setp(int i, int j) {
		i = getp(i);
		j = getp(j);
		if (i == j) {
			return;
		}
		p[i] = j;
		l[j] = std::min(l[j], l[i]);
		r[j] = std::max(r[j], r[i]);
		sum[j] += sum[i];

		bool update = false;
		update |= (sum[j] * minv > ans);
		if (sum[j] * minv == ans) {
			update |= (r[j] - l[j] < ar - al);
			if (r[j] - l[j] == ar - al) {
				update |= (l[j] < al);
			}
		}

		if (update) {
			ans = sum[j] * minv;
			al = l[j], ar = r[j];
		}
	}
};

DisjointSet<N> ds;

int main() {
	bool flag = true;
	while (scanf("%d", &n) == 1) {
		if (flag) {
			flag = false;
		} else {
			puts("");
		}
		at.clear();
		for (int i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
			at.PB(MP(a[i], i));
		}
		std::sort(at.begin(), at.end());
		ans = al = ar = 0;
		ds.init(n);
		for (RIT i = at.rbegin(); i != at.rend(); ++i) {
			minv = i->F;
			int id = i->S;
			if (id - 1 >= 0 && a[id - 1] >= minv) {
				ds.setp(id - 1, id);
			}
			if (id + 1 < n && a[id + 1] >= minv) {
				ds.setp(id + 1, id);
			}
		}
		printf("%lld\n%d %d\n", ans, al + 1, ar + 1);
	}
	return 0;
}
