#include <algorithm>
#include <cstdio>
#include <limits>

#define L(X) ((X) * 2)
#define R(X) ((X) * 2 + 1)

template<int N, int M, class Flow>
struct FordFulkerson {
	int n, e, first[N], next[M], to[M], s, t, q[N], pre[N];
	Flow cap[M], flow;
	bool vis[N];
	void init(int _n, int _s, int _t) {
		n = _n, s = _s, t = _t;
		std::fill(first, first + n, -1);
		e = 0;
	}
	void add(int u, int v, Flow w) {
		next[e] = first[u], to[e] = v, cap[e] = w, first[u] = e++;
		next[e] = first[v], to[e] = u, cap[e] = 0, first[v] = e++;
	}
	Flow findPath() {
		std::fill(vis, vis + n, false);
		int st = 0, ed = 0;
		pre[s] = -1, q[ed++] = s, vis[s] = true;
		while (st != ed) {
			int u = q[st++];
			if (u == t) {
				break;
			}
			for (int edge = first[u]; edge != -1; edge = next[edge]) {
				int v = to[edge];
				if (!vis[v] && cap[edge] > 0) {
					pre[v] = edge, q[ed++] = v, vis[v] = true;
				}
			}
		}
		if (!vis[t]) {
			return 0;
		}
		Flow f = std::numeric_limits<Flow>::max();
		for (int u = t; pre[u] != -1; u = to[pre[u] ^ 1]) {
			f = std::min(f, cap[pre[u]]);
		}
		for (int u = t; pre[u] != -1; u = to[pre[u] ^ 1]) {
			cap[pre[u]] -= f;
			cap[pre[u] ^ 1] += f;
		}
		return f;
	}
	Flow solve() {
		flow = 0;
		while (true) {
			Flow f = findPath();
			if (!f) {
				break;
			}
			flow += f;
		}
		return flow;
	}
	void dfs(int u) {
		vis[u] = true;
		for (int edge = first[u]; edge != -1; edge = next[edge]) {
			int v = to[edge];
			if (!vis[v] && cap[edge]) {
				dfs(v);
			}
		}
	}
	void gao(int fuck) {
		std::fill(vis, vis + n, false);
		dfs(s);
		int cnt = 0;
		for (int i = 0; i < fuck; ++i) {
			if (!vis[L(i)]) {
				cnt++;
			}
			if (vis[R(i)]) {
				cnt++;
			}
		}
		printf("%d\n%d\n", flow, cnt);
		for (int i = 0; i < fuck; ++i) {
			if (!vis[L(i)]) {
				printf("%d -\n", i + 1);
			}
			if (vis[R(i)]) {
				printf("%d +\n", i + 1);
			}
		}
	}
};

const int N = 100;
const int M = 5000;

FordFulkerson<N * 2 + 2, (M + N * 2) * 2, int> ff;
int n, m, w[2][N], a[M], b[M];

int main() {
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < n; ++j) {
				scanf("%d", &w[i][j]);
			}
		}
		for (int i = 0; i < m; ++i) {
			scanf("%d %d", &a[i], &b[i]);
			--a[i], --b[i];
		}
		int s = n * 2, t = n * 2 + 1;
		ff.init(n * 2 + 2, s, t);
		for (int i = 0; i < n; ++i) {
			ff.add(s, L(i), w[1][i]);
			ff.add(R(i), t, w[0][i]);
		}
		for (int i = 0; i < m; ++i) {
			ff.add(L(a[i]), R(b[i]), std::numeric_limits<int>::max());
		}
		ff.solve();
		ff.gao(n);
	}
	return 0;
}

