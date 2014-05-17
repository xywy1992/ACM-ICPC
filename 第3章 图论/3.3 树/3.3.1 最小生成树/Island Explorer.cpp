#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iterator>
#include <utility>
#include <vector>

typedef std::vector<double> VD;
typedef std::pair<int, int> PII;
typedef std::pair<double, double> PDD;
typedef std::pair<double, PII> PDII;
typedef std::vector<PDII> VPDII;
#define F first
#define S second
#define PB push_back
#define MP std::make_pair
#define FOR(i, v) for(__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++i)

template<int N>
struct DisjointSet {
	int p[N];
	void init(int n) {
		for (int i = 0; i < n; ++i) {
			p[i] = i;
		}
	}
	int getp(int i) {
		return i == p[i] ? i : (p[i] = getp(p[i]));
	}
	bool setp(int i, int j) {
		i = getp(i);
		j = getp(j);
		p[i] = j;
		return i != j;
	}
};

const int N = (int) (1e4);
int T, n, m;
PDD a, b, c, d, p1[N], p2[N];
VD t1, t2;
VPDII e;
DisjointSet<2 * N> ds;

PDD at(PDD & a, PDD & b, double t) {
	return MP(a.F * t + b.F * (1 - t), a.S * t + b.S * (1 - t));
}

void init(VD & t, int & n, PDD * p, PDD & a, PDD & b) {
	t.clear();
	double tmp;
	for (int i = 0; i < n; ++i) {
		scanf("%lf", &tmp);
		t.PB(tmp);
	}
	std::sort(t.begin(), t.end());
	t.erase(std::unique(t.begin(), t.end()), t.end());
	n = t.size();
	for (int i = 0; i < n; ++i) {
		p[i] = at(a, b, t[i]);
	}
}

#define SQR(X) ((X) * (X))
double dis2(PDD a, PDD b) {
	return SQR(a.F - b.F) + SQR(a.S - b.S);
}

int ts(int x, int l, int r) {
	while (r - l > 1) {
		int m1 = (l + r) / 2;
		double d1 = dis2(p1[x], p2[m1]);
		int m2 = (m1 + r) / 2;
		double d2 = dis2(p1[x], p2[m2]);
		if (d1 < d2) {
			r = m2;
		} else {
			l = m1;
		}
	}
	double d1 = dis2(p1[x], p2[l]);
	double d2 = dis2(p1[x], p2[r]);
	return d1 < d2 ? l : r;
}

int main() {
	scanf("%d", &T);
	for (int t = 1; t <= T; ++t) {
		scanf("%d %d", &n, &m);
		scanf("%lf %lf %lf %lf %lf %lf %lf %lf", &a.F, &a.S, &b.F, &b.S, &c.F, &c.S, &d.F, &d.S);
		init(t1, n, p1, a, b);
		init(t2, m, p2, c, d);
		e.clear();
		for (int i = 1; i < n; ++i) {
			e.PB(MP(dis2(p1[i - 1], p1[i]), MP(i - 1, i)));
		}
		for (int i = 1; i < m; ++i) {
			e.PB(MP(dis2(p2[i - 1], p2[i]), MP(n + i - 1, n + i)));
		}
		for (int i = 0; i < n; ++i) {
			int p = ts(i, 0, m - 1);
			e.PB(MP(dis2(p1[i], p2[p]), MP(i, n + p)));
			if (p - 1 >= 0) {
				e.PB(MP(dis2(p1[i], p2[p - 1]), MP(i, n + p - 1)));
			}
			if (p + 1 < m) {
				e.PB(MP(dis2(p1[i], p2[p + 1]), MP(i, n + p + 1)));
			}
		}
		std::sort(e.begin(), e.end());
		ds.init(n + m);
		double mst = 0;
		FOR(i, e)
		{
			int u = (*i).S.F, v = (*i).S.S;
			if (ds.setp(u, v)) {
				mst += sqrt((*i).F);
			}
		}
		printf("Case #%d: %.3lf\n", t, mst);
	}
	return 0;
}

