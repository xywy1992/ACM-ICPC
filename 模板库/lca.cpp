#include <algorithm>
#include <vector>

template<int N, int M>
struct LCA {
	std::vector<int> e[N];
	int d[N], p[N][M];
	void init(int n) {
		for (int i = 0; i < n; ++i) {
			e[i].clear();
		}
	}
	void add(int u, int v) {
		e[u].push_back(v);
		e[v].push_back(u);
	}
	void dfs(int u, int f) {
		p[u][0] = f;
		for (int i = 1; i < M; ++i) {
			p[u][i] = p[p[u][i - 1]][i - 1];
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
	void build() {
		d[0] = 0;
		dfs(0, 0);
	}
};


#include <algorithm>
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

