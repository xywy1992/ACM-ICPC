#include <algorithm>
#include <cstdio>
#include <utility>
#include <vector>

template<int N, int M, class T>
struct LCA {
	std::vector<std::pair<int, T> > e[N];
	int d[N], p[N][M];
	T l[N];
	void init(int n) {
		for (int i = 0; i < n; ++i) {
			e[i].clear();
		}
	}
	void add(int u, int v, T w) {
		e[u].push_back(std::make_pair(v, w));
		e[v].push_back(std::make_pair(u, w));
	}
	void dfs(int u, int f) {
		p[u][0] = f;
		for (int i = 1; i < M; ++i) {
			p[u][i] = p[p[u][i - 1]][i - 1];
		}
		for (int i = 0; i < (int) e[u].size(); ++i) {
			int v = e[u][i].first;
			if (v != f) {
				d[v] = d[u] + 1;
				l[v] = l[u] + e[u][i].second;
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
	T howfar(int u, int v) {
		int w = lca(u, v);
		return l[u] + l[v] - 2 * l[w];
	}
	void build() {
		d[0] = l[0] = 0;
		dfs(0, 0);
	}
};

const int N = (int) (5e4);
const int M = 16;
LCA<N, M, int> lca;
int n, m;

int main() {
	bool flag = true;
	while (scanf("%d", &n) == 1) {
		if (flag) {
			flag = false;
		} else {
			puts("");
		}
		lca.init(n);
		for (int i = 0, u, v, w; i < n - 1; ++i) {
			scanf("%d %d %d", &u, &v, &w);
			lca.add(u, v, w);
		}
		lca.build();
		scanf("%d", &m);
		for (int i = 0, x, y, z; i < m; ++i) {
			scanf("%d %d %d", &x, &y, &z);
			int ans = (lca.howfar(x, y) + lca.howfar(x, z) + lca.howfar(y, z))
					/ 2;
			printf("%d\n", ans);
		}
	}
	return 0;
}
