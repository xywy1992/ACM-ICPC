#include <algorithm>
#include <cstdio>
#include <iterator>
#include <limits>
#include <vector>

const int N = 100;
const int M = 400;
const double EPS = 1e-9;

typedef std::vector<int> VI;

#define PB push_back
#define FOR(i, v) for(__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++i)

int signum(double x) {
	return x > EPS ? 1 : (x < -EPS ? -1 : 0);
}

template<int N, int M, class Flow>
struct Dinic {
	int n, e, first[N], cur[N], next[M], to[M], id[M], s, t;
	int pre[N], level[N], q[N], sign;
	Flow cap[M], flow;
	void add(int u, int v, Flow w, int i) {
		to[e] = v;
		cap[e] = w;
		id[e] = i;
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

	bool vis[N];
	void go(int u) {
		vis[u] = true;
		for (int it = first[u]; it != -1; it = next[it]) {
			int v = to[it];
			if (!vis[v] && signum(cap[it])) {
				go(v);
			}
		}
	}
	void cut(VI & set) {
		std::fill(vis, vis + n, false);
		go(s);
		for (int i = 0; i < n; ++i) {
			if (vis[i]) {
				for (int it = first[i]; it != -1; it = next[it]) {
					if (!vis[to[it]]) {
						set.PB(id[it]);
					}
				}
			}
		}
	}
};

int n, m, a[M], b[M], c[M];
Dinic<N, M * 2, double> dinic;

bool check(int s, int t, double delta) {
	dinic.init(n, s, t);
	double ans = 0;
	for (int i = 0; i < m; ++i) {
		if (signum(c[i] - delta) <= 0) {
			ans += c[i] - delta;
		} else {
			dinic.add(a[i], b[i], c[i] - delta, i);
			dinic.add(b[i], a[i], c[i] - delta, i);
		}
	}
	ans += dinic.solve();
	return signum(ans) <= 0;
}

double gao(int s, int t) {
	double l = 1, r = 1e7, ans;
	for (int i = 0; i < 100; ++i) {
		ans = (l + r) / 2.0;
		if (check(s, t, ans)) {
			r = ans;
		} else {
			l = ans;
		}
	}
	return ans;
}

VI findCut(double delta) {
	VI ans;
	for (int i = 0; i < m; ++i) {
		if (signum(c[i] - delta) <= 0) {
			ans.PB(i);
		}
	}
	dinic.cut(ans);
	return ans;
}

int main() {
	bool flag = true;
	while (scanf("%d %d", &n, &m) == 2) {
		if (flag) {
			flag = false;
		} else {
			puts("");
		}
		for (int i = 0; i < m; ++i) {
			scanf("%d %d %d", &a[i], &b[i], &c[i]);
			--a[i], --b[i];
		}
		double ans = gao(0, n - 1);
		VI v = findCut(ans);
		printf("%d\n", (int) v.size());
		for (int i = 0; i < (int) v.size(); ++i) {
			printf("%d%s", v[i] + 1, i == (int) v.size() - 1 ? "\n" : " ");
		}
	}
	return 0;
}
