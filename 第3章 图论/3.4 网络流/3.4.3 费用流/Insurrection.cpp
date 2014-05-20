#include <algorithm>
#include <cstdio>
#include <limits>

template<int N, int M, class Flow>
struct Dinic {
	int n, e, first[N], cur[N], next[M], to[M], s, t;
	int pre[N], level[N], q[N], sign;
	Flow cap[M], flow;
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

const int N = 50;
const int M = 300;
const double INF = std::numeric_limits<double>::max();
int T, n, m, a[M], b[M];
double w[N], d[2][N], f[N][N];
Dinic<N * 2, N * 2 + M * 4, double> dinic;

void bellmanFord(int s, double * d) {
	std::fill(d, d + n, INF);
	d[s] = 0;
	for (int i = 0; i < n - 1; ++i) {
		for (int j = 0; j < m; ++j) {
			if (d[a[j]] != INF) {
				d[b[j]] = std::min(d[b[j]], d[a[j]] + w[b[j]]);
			}
			if (d[b[j]] != INF) {
				d[a[j]] = std::min(d[a[j]], d[b[j]] + w[a[j]]);
			}
		}
	}
}

#define L(X) ((X) * 2)
#define R(X) ((X) * 2 + 1)

double gao() {
	bellmanFord(0, d[0]);
	bellmanFord(n - 1, d[1]);
	dinic.init(n * 2, R(0), L(n - 1));
	for (int i = 1; i < n - 1; ++i) {
		if (d[0][i] != INF && d[1][i] != INF) {
			dinic.add(L(i), R(i), d[0][i] + d[1][i]);
			dinic.add(R(i), L(i), 0);
		}
	}
	for (int i = 0; i < m; ++i) {
		dinic.add(R(a[i]), L(b[i]), INF);
		dinic.add(L(b[i]), R(a[i]), 0);
		dinic.add(R(b[i]), L(a[i]), INF);
		dinic.add(L(a[i]), R(b[i]), 0);
	}
	return dinic.solve();
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		w[0] = w[n - 1] = 0;
		for (int i = 1; i < n - 1; ++i) {
			scanf("%lf", &w[i]);
		}
		bool flag = false;
		for (int i = 0; i < m; ++i) {
			scanf("%d %d", &a[i], &b[i]);
			--a[i], --b[i];
			if (a[i] > b[i]) {
				std::swap(a[i], b[i]);
			}
			if (a[i] == 0 && b[i] == n - 1) {
				flag = true;
			}
		}
		if (flag) {
			puts("No Solution!");
		} else {
			printf("%.4lf\n", gao());
		}
	}
	return 0;
}

