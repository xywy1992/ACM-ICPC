#include <algorithm>
#include <cstdio>
#include <vector>

const int INF = (int) (1e9);

template<int N, int M>
struct LCA {
	std::vector<int> e[N];
	int w[N], d[N], p[N][M], max[N][M], min[N][M], f1[N][M], f2[N][M];
	void init(int n) {
		for (int i = 0; i < n; ++i) {
			e[i].clear();
			scanf("%d", &w[i]);
		}
	}
	void add(int u, int v) {
		e[u].push_back(v);
		e[v].push_back(u);
	}
	void dfs(int u, int f) {
		p[u][0] = f;
		max[u][0] = std::max(w[f], w[u]);
		min[u][0] = std::min(w[f], w[u]);
		f1[u][0] = (u == f ? -INF : w[f] - w[u]);
		f2[u][0] = (u == f ? -INF : w[u] - w[f]);
		for (int i = 1; i < M; ++i) {
			p[u][i] = p[p[u][i - 1]][i - 1];
			max[u][i] = std::max(max[u][i - 1], max[p[u][i - 1]][i - 1]);
			min[u][i] = std::min(min[u][i - 1], min[p[u][i - 1]][i - 1]);
			f1[u][i] = std::max(f1[u][i - 1], f1[p[u][i - 1]][i - 1]);
			f1[u][i] = std::max(f1[u][i],
					max[p[u][i - 1]][i - 1] - min[u][i - 1]);
			f2[u][i] = std::max(f2[u][i - 1], f2[p[u][i - 1]][i - 1]);
			f2[u][i] = std::max(f2[u][i],
					max[u][i - 1] - min[p[u][i - 1]][i - 1]);
		}
		for (int i = 0; i < (int) e[u].size(); ++i) {
			int v = e[u][i];
			if (v != f) {
				d[v] = d[u] + 1;
				dfs(v, u);
			}
		}
	}
	int up(int u, int m) {
		for (int i = 0; i < M; ++i) {
			if ((m >> i) & 1) {
				u = p[u][i];
			}
		}
		return u;
	}
	int lca(int u, int v) {
		if (d[u] > d[v]) {
			std::swap(u, v);
		}
		v = up(v, d[v] - d[u]);
		if (u == v) {
			return u;
		} else {
			for (int i = M - 1; i >= 0; --i) {
				if (p[u][i] != p[v][i]) {
					u = p[u][i];
					v = p[v][i];
				}
			}
			return p[u][0];
		}
	}
	void up(int u, int m, int & a, int & b, int & c, int & d) {
		a = b = c = -INF, d = INF;
		for (int i = 0; i < M; ++i) {
			if ((m >> i) & 1) {
				a = std::max(a, f1[u][i]);
				a = std::max(a, max[u][i] - d);
				b = std::max(b, f2[u][i]);
				b = std::max(b, c - min[u][i]);
				c = std::max(c, max[u][i]);
				d = std::min(d, min[u][i]);
				u = p[u][i];
			}
		}
	}
	int solve(int u, int v) {
		int w = lca(u, v);
		int a1, b1, c1, d1;
		up(u, d[u] - d[w], a1, b1, c1, d1);
		int a2, b2, c2, d2;
		up(v, d[v] - d[w], a2, b2, c2, d2);
		int ans = std::max(a1, b2);
		ans = std::max(ans, c2 - d1);
		ans = std::max(ans, 0);
		return ans;
	}
	void build() {
		d[0] = 0;
		dfs(0, 0);
	}
};

const int N = (int) (5e4);
const int M = 16;
LCA<N, M> lca;
int n, m;

int main() {
	while (scanf("%d", &n) == 1) {
		lca.init(n);
		for (int i = 0, u, v; i < n - 1; ++i) {
			scanf("%d %d", &u, &v);
			--u, --v;
			lca.add(u, v);
		}
		lca.build();
		scanf("%d", &m);
		for (int i = 0, u, v; i < m; ++i) {
			scanf("%d %d", &u, &v);
			--u, --v;
			printf("%d\n", lca.solve(u, v));
		}
	}
	return 0;
}

