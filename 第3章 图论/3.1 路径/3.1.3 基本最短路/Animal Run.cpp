#include <algorithm>
#include <cstdio>
#include <iterator>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

typedef std::pair<int, int> EDGE;
typedef std::vector<EDGE> ADJ;

#define PB push_back
#define MP std::make_pair
#define F first
#define S second
#define FOR(i, n) for(int i = 0; i < n; ++i)
#define FOREACH(i, v) for(__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++i)

const int N = 1000;

int n, m, a[N][N], b[N][N], c[N][N];
ADJ e[N * N * 2];

int at(int r, int c, int f) {
	return (r * (m - 1) + c) * 2 + f;
}

void add(int u, int v, int w) {
	e[u].PB(MP(v, w));
	e[v].PB(MP(u, w));
}

const int INF = std::numeric_limits<int>::max();

int dis[N * N * 2];
std::priority_queue<std::pair<int, int> > q;
int dijkstra(int n, int s, int t) {
	while (!q.empty()) {
		q.pop();
	}
	std::fill(dis, dis + n, INF);
	dis[s] = 0, q.push(MP(0, s));
	while (!q.empty()) {
		int u = q.top().S;
		int cur = -q.top().F;
		if (u == t) {
			return cur;
		}
		q.pop();
		if (cur > dis[u]) {
			continue;
		}
		FOREACH(i, e[u])
		{
			int v = i->F;
			if (dis[v] > dis[u] + i->S) {
				dis[v] = dis[u] + i->S, q.push(MP(-dis[v], v));
			}
		}
	}
	return dis[t];
}

int gao() {
	int s = (n - 1) * (m - 1) * 2;
	int t = (n - 1) * (m - 1) * 2 + 1;
	int v = (n - 1) * (m - 1) * 2 + 2;
	FOR(i, v)
	{
		e[i].clear();
	}
	FOR(i, n)
		FOR(j, m - 1)
		{
			if (i == 0) {
				add(at(0, j, 1), t, a[i][j]);
			} else if (i == n - 1) {
				add(s, at(n - 2, j, 0), a[i][j]);
			} else {
				add(at(i - 1, j, 0), at(i, j, 1), a[i][j]);
			}
		}
	FOR(i, n - 1)
		FOR(j, m)
		{
			if (j == 0) {
				add(s, at(i, 0, 0), b[i][j]);
			} else if (j == m - 1) {
				add(at(i, m - 2, 1), t, b[i][j]);
			} else {
				add(at(i, j - 1, 1), at(i, j, 0), b[i][j]);
			}
		}

	FOR(i, n - 1)
		FOR(j, m - 1)
		{
			add(at(i, j, 0), at(i, j, 1), c[i][j]);
		}
	return dijkstra(v, s, t);
}

int main() {
	int t = 1;
	while (scanf("%d %d", &n, &m) == 2) {
		if (!n && !m) {
			break;
		}
		FOR(i, n)
			FOR(j, m - 1)
				scanf("%d", &a[i][j]);
		FOR(i, n - 1)
			FOR(j, m)
				scanf("%d", &b[i][j]);
		FOR(i, n - 1)
			FOR(j, m - 1)
				scanf("%d", &c[i][j]);
		printf("Case %d: Minimum = %d\n", t++, gao());
	}
	return 0;
}

