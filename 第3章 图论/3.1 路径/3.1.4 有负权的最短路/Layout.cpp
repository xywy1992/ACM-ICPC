#include <algorithm>
#include <cstdio>
#include <iterator>
#include <limits>
#include <utility>
#include <vector>

typedef std::pair<int, int> PII;
typedef std::vector<PII> VPII;

#define PB push_back
#define MP std::make_pair
#define F first
#define S second
#define FOR(i, v) for(__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++i)

const int N = 1000;
const int INF = std::numeric_limits<int>::max();

int n, m1, m2, dis[N], cnt[N], q[N * 1000];
VPII e[N];
bool mark[N];

std::pair<bool, int> spfa() {
	std::fill(dis, dis + n, INF);
	std::fill(cnt, cnt + n, 0);
	std::fill(mark, mark + n, false);
	int st = 0, ed = 0;
	dis[0] = 0, q[ed++] = 0, mark[0] = true;
	while (st != ed) {
		int u = q[st++];
		mark[u] = false;
		FOR(i, e[u])
		{
			int v = i->F;
			if (dis[v] > dis[u] + i->S) {
				dis[v] = dis[u] + i->S;
				cnt[v]++;
				if (cnt[v] >= n) {
					return MP(false, 0);
				}
				if (!mark[v]) {
					q[ed++] = v, mark[v] = true;
				}
			}
		}
	}
	return MP(true, dis[n - 1]);
}

int main() {
	while (scanf("%d %d %d", &n, &m1, &m2) == 3) {
		for (int i = 0; i < n; ++i) {
			e[i].clear();
		}
		for (int i = 0; i < n - 1; ++i) {
			e[i + 1].PB(MP(i, 0));
		}
		for (int i = 0, u, v, w; i < m1; ++i) {
			scanf("%d %d %d", &u, &v, &w);
			--u, --v;
			e[u].PB(MP(v, w));
		}
		for (int i = 0, u, v, w; i < m2; ++i) {
			scanf("%d %d %d", &u, &v, &w);
			--u, --v;
			e[v].PB(MP(u, -w));
		}
		std::pair<bool, int> ans = spfa();
		if (ans.F) {
			if (ans.S == INF) {
				puts("-2");
			} else {
				printf("%d\n", ans.S);
			}
		} else {
			puts("-1");
		}
	}
	return 0;
}

