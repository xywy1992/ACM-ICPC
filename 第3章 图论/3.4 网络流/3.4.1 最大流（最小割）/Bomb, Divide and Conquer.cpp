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
	void init(int _n) {
		n = _n;
		std::fill(first, first + n, -1);
		e = 0;
	}
	Flow gao(int _s, int _t) {
		s = _s, t = _t;
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

const int N = 150;
const int M = N * (N - 1) / 2;
Dinic<N, M * 2, int> dinic;
int T, n, m, a[M], b[M], c[M];

int gao() {
	int t = n - 1, ans = std::numeric_limits<int>::max();
	for (int s = 0; s < n - 1; ++s) {
		dinic.init(n);
		for (int i = 0; i < m; ++i) {
			dinic.add(a[i], b[i], c[i]);
			dinic.add(b[i], a[i], c[i]);
		}
		ans = std::min(ans, dinic.gao(s, t));
	}
	return ans;
}

int main() {
	scanf("%d", &T);
	for (int t = 1; t <= T; ++t) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < m; ++i) {
			scanf("%d %d %d", &a[i], &b[i], &c[i]);
			--a[i], --b[i];
		}
		printf("Case #%d: %d\n", t, gao());
	}
	return 0;
}

