#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iterator>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

typedef std::vector<int> VI;
typedef std::pair<int, int> PII;

#define MP std::make_pair
#define F first
#define S second

#define PB push_back
#define FOR(i, v) for(__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++i)

const int N = (int) (1e5);
const int M = (int) (1e5);
const int INF = std::numeric_limits<int>::max();

int n, m, k, a[M], b[M], c[M];
int e, first[N], next[M * 2], to[M * 2], cost[M * 2], idx[M * 2];
bool set[N];

void init() {
	e = 0;
	std::fill(first, first + n, -1);
}

void add(int u, int v, int w, int i) {
	to[e] = v, cost[e] = w, idx[e] = i, next[e] = first[u], first[u] = e++;
	to[e] = u, cost[e] = w, idx[e] = i, next[e] = first[v], first[v] = e++;
}

int dis[N];
VI pre[N];
std::priority_queue<PII> q;

int dijkstra(int s) {
	while (!q.empty()) {
		q.pop();
	}
	std::fill(dis, dis + n, INF);
	dis[s] = 0, q.push(MP(0, s));
	while (!q.empty()) {
		int u = q.top().S, cur = -q.top().F;
		q.pop();
		if (dis[u] < cur) {
			continue;
		}
		for (int edge = first[u]; edge != -1; edge = next[edge]) {
			int v = to[edge];
			if (dis[v] > dis[u] + cost[edge]) {
				dis[v] = dis[u] + cost[edge];
				q.push(MP(-dis[v], v));
			}
		}
	}
	int t = s, cur = 0;
	for (int i = 0; i < n; ++i) {
		if (set[i] && dis[i] > cur) {
			t = i, cur = dis[i];
		}
	}
	for (int i = 0; i < n; ++i) {
		pre[i].clear();
	}
	for (int i = 0; i < m; ++i) {
		if (dis[a[i]] + c[i] == dis[b[i]]) {
			pre[b[i]].PB(i * 2);
		}
		if (dis[b[i]] + c[i] == dis[a[i]]) {
			pre[a[i]].PB(i * 2 + 1);
		}
	}
	return t;
}

int f[N], g[N];
int dfs(int u) {
	if (f[u] != -1) {
		return f[u];
	}
	FOR(i, pre[u])
	{
		int p = to[(*i) ^ 1];
		int tmp = dfs(p);
		if (f[u] < tmp) {
			f[u] = tmp, g[u] = (*i);
		}
	}
	f[u] += (set[u] ? 1 : 0);
	return f[u];
}

VI find(int s, int t) {
	std::fill(f, f + n, -1);
	f[s] = 1;
	dfs(t);
	VI ans;
	for (int u = t; u != s; u = to[g[u] ^ 1]) {
		ans.PB(idx[g[u]]);
	}
	return ans;
}

int main() {
	while (scanf("%d %d", &n, &m) == 2) {
		init();
		for (int i = 0, u, v, w; i < m; ++i) {
			scanf("%d %d %d", &u, &v, &w);
			add(u - 1, v - 1, w, i);
			a[i] = u - 1, b[i] = v - 1, c[i] = w;
		}
		scanf("%d", &k);
		memset(set, 0, sizeof(set));
		int x = -1;
		for (int i = 0, u; i < k; ++i) {
			scanf("%d", &u);
			set[u - 1] = true;
			x = u - 1;
		}
		int s = dijkstra(x);
		int t = dijkstra(s);
		VI ans = find(s, t);
		printf("%d\n", (int) ans.size());
		for (int i = 0; i < (int) ans.size(); ++i) {
			printf("%d%s", ans[i] + 1, i == (int) ans.size() - 1 ? "\n" : " ");
		}
	}
	return 0;
}

