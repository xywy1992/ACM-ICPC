#include <cmath>
#include <cstdio>
#include <iterator>
#include <utility>
#include <vector>

const int N = 1000;
const int M = 5000;
const double EPS = 1e-4;

int n, m, w[N], a[M], b[M], c[M];

typedef std::pair<int, int> PII;
typedef std::vector<PII> VII;
#define MP std::make_pair
#define PB push_back
#define F first
#define S second
#define FOR(i, v) for(__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++i)

VII e[N];

double dis[N];
bool mark[N];
int cnt[N], q[N * 1000];

bool spfa(double delta) {
	int st = 0, ed = 0;
	for (int i = 0; i < n; ++i) {
		dis[i] = 0, q[ed++] = i, mark[i] = true, cnt[i] = 0;
	}
	while (st != ed) {
		int u = q[st++];
		mark[u] = false;
		FOR(i, e[u])
		{
			int v = i->F;
			double len = i->S * delta - w[u];
			if (dis[v] > dis[u] + len) {
				dis[v] = dis[u] + len;
				cnt[v]++;
				if (cnt[v] >= n) {
					return true;
				}
				if (!mark[v]) {
					q[ed++] = v, mark[v] = true;
				}
			}
		}
	}
	return false;
}

int main() {
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i < n; ++i) {
			scanf("%d", &w[i]);
			e[i].clear();
		}
		for (int i = 0; i < m; ++i) {
			scanf("%d %d %d", &a[i], &b[i], &c[i]);
			--a[i], --b[i];
			e[a[i]].PB(MP(b[i], c[i]));
		}
		double l = 0, r = 2000, ans;
		while (fabs(r - l) > EPS) {
			ans = (l + r) / 2.0;
			if (spfa(ans)) {
				l = ans;
			} else {
				r = ans;
			}
		}
		printf("%.2f\n", ans);
	}
	return 0;
}

