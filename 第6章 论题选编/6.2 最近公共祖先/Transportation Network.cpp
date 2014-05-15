#include <algorithm>
#include <cstdio>
#include <cstring>

template<int N, int M, class T>
struct DisjointSet {
	int p[N], dep[N], anc[N][M];
	T dis[N];
	void init(int n) {
		for (int i = 0; i < n; ++i) {
			p[i] = i;
			dep[i] = 0;
			memset(anc[i], 0xff, sizeof(anc[i]));
			dis[i] = 0;
		}
	}
	int find(int u) {
		if (p[u] != u) {
			int v = p[u];
			p[u] = find(v);
			dep[u] += dep[v];
			dis[u] += dis[v];
		}
		return p[u];
	}
	void merge(int u, int v, T w) {
		u = find(u);
		v = find(v);
		if (u != v) {
			p[u] = v;
			dep[u] = 1;
			anc[u][0] = v;
			dis[u] = w;
		}
	}
	int ancestor(int u, int k) {
		if (anc[u][k] == -1) {
			anc[u][k] = ancestor(ancestor(u, k - 1), k - 1);
		}
		return anc[u][k];
	}
	int up(int u, int m) {
		for (int i = M - 1; i >= 0; --i) {
			if ((m >> i) & 1) {
				u = ancestor(u, i);
			}
		}
		return u;
	}
	int lca(int u, int v) {
		find(u), find(v);
		if (dep[u] > dep[v]) {
			std::swap(u, v);
		}
		v = up(v, dep[v] - dep[u]);
		if (u == v) {
			return u;
		} else {
			for (int i = M - 1; i >= 0; --i) {
				if ((1 << i) > dep[u]) {
					continue;
				}
				if (ancestor(u, i) != ancestor(v, i)) {
					u = ancestor(u, i);
					v = ancestor(v, i);
					find(u), find(v);
				}
			}
			return ancestor(u, 0);
		}
	}
	T howfar(int u, int v) {
		int w = lca(u, v);
		find(u);
		find(v);
		find(w);
		return dis[u] + dis[v] - 2 * dis[w];
	}
};

const int N = (int) (2e4);
const int M = 15;
DisjointSet<N, M, int> ds;

int T, n, m;

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		ds.init(n);
		char cmd[100];
		int ans = 0, u, v, w;
		for (int i = 0; i < m; ++i) {
			scanf("%s %d %d", cmd, &u, &v);
			if (cmd[0] == 'Q') {
				--u, --v;
				if (ds.find(u) == ds.find(v)) {
					ans = ds.howfar(u, v);
					printf("%d\n", ans);
				} else {
					puts("Not connected.");
				}
			} else {
				u -= ans % n + 1;
				if (u <= 0) {
					u += n;
				}
				v -= ans % n + 1;
				if (v <= 0) {
					v += n;
				}
				--u, --v;
				scanf("%d", &w);
				ds.merge(u, v, w);
			}
		}
	}
	return 0;
}

