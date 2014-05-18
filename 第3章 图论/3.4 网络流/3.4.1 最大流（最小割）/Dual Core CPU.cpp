#include <algorithm>
#include <cstdio>
#include <limits>

template<int N, int M, class Flow>
struct Dinic {
	int n, e, first[N], next[M], to[M], s, t, pre[N], level[N], q[N], sign;
	Flow cap[M], cur[N], flow;
	void add(int u, int v, Flow w) {
		to[e] = v;
		cap[e] = w;
		next[e] = first[u];
		first[u] = e++;
	}
	bool bfs(int s, int t) {
		std::fill(level, level + n, -1);
		sign = t;
		level[t] = 0;
		int head = 0, tail = 0;
		q[tail++] = t;
		while (head != tail && level[s] == -1) {
			int u = q[head++];
			for (int it = first[u]; it != -1; it = next[it]) {
				if (cap[it ^ 1] > 0 && level[to[it]] == -1) {
					level[to[it]] = level[u] + 1;
					q[tail++] = to[it];
				}
			}
		}
		return level[s] != -1;
	}
	void push() {
		Flow delta = std::numeric_limits<Flow>::max();
		int u, p;
		for (u = t; u != s; u = to[p ^ 1]) {
			p = pre[u];
			delta = std::min(delta, cap[p]);
		}
		for (u = t; u != s; u = to[p ^ 1]) {
			p = pre[u];
			cap[p] -= delta;
			if (!cap[p]) {
				sign = to[p ^ 1];
			}
			cap[p ^ 1] += delta;
		}
		flow += delta;
	}
	void dfs(int u) {
		if (u == t) {
			push();
		} else {
			for (int & it = cur[u]; it != -1; it = next[it]) {
				if (cap[it] > 0 && level[u] == level[to[it]] + 1) {
					pre[to[it]] = it;
					dfs(to[it]);
					if (level[sign] > level[u]) {
						return;
					}
					sign = t;
				}
			}
			level[u] = -1;
		}
	}
	void init(int _n, int _s, int _t) {
		n = _n, s = _s, t = _t;
		std::fill(first, first + n, -1);
		e = 0;
	}
	Flow solve() {
		flow = 0;
		while (bfs(s, t)) {
			for (int i = 0; i < n; ++i) {
				cur[i] = first[i];
			}
			dfs(s);
		}
		return flow;
	}
};

Dinic<(int) (1e6), (int) (1e6), int> dinic;
const int N = (int) (2e4);
const int M = (int) (2e5);
int n, m, a[N], b[N], c[M], d[M], e[M];

int gao() {
	int s = n, t = n + 1;
	dinic.init(n + 2, s, t);
	for (int i = 0; i < n; ++i) {
		dinic.add(s, i, a[i]);
		dinic.add(i, s, 0);
		dinic.add(i, t, b[i]);
		dinic.add(t, i, 0);
	}
	for (int i = 0; i < m; ++i) {
		dinic.add(c[i], d[i], e[i]);
		dinic.add(d[i], c[i], e[i]);
	}
	return dinic.solve();
}

int main() {
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i < n; ++i) {
			scanf("%d %d", &a[i], &b[i]);
		}
		for (int i = 0; i < m; ++i) {
			scanf("%d %d %d", &c[i], &d[i], &e[i]);
			--c[i], --d[i];
		}
		printf("%d\n", gao());
	}
	return 0;
}

