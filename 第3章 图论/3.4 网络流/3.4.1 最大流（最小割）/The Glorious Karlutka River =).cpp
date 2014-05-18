#include <algorithm>
#include <cstdio>
#include <cstring>
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

const int N = (int) (1e6);
const int M = (int) (1e6);

Dinic<N, M, int> dinic;

int no_rub, no_tou, jump, width, x[50], y[50], cap[50];
bool reach[50][50];

int at(int x, int y) {
	return (y - 1) * no_rub + x;
}

#define L(X) ((X) << 1    )
#define R(X) ((X) << 1 | 1)
#define SQR(X) ((X) * (X))

void addEdge(int u, int v, int w) {
	dinic.add(u, v, w);
	dinic.add(v, u, 0);
}

bool check(int time) {
	int n = no_rub * (time - 1) * 2 + 2;
	int s = no_rub * (time - 1) * 2;
	int t = no_rub * (time - 1) * 2 + 1;
	dinic.init(n, s, t);
	for (int i = 0; i < no_rub; ++i) {
		if (y[i] > jump) {
			continue;
		}
		for (int j = 1; j <= time - 1; ++j) {
			addEdge(s, L(at(i, j)), std::numeric_limits<int>::max());
		}
	}
	for (int i = 0; i < no_rub; ++i) {
		if (width - y[i] > jump) {
			continue;
		}
		for (int j = 1; j <= time - 1; ++j) {
			addEdge(R(at(i, j)), t, std::numeric_limits<int>::max());
		}
	}
	for (int i = 0; i < no_rub; ++i) {
		for (int j = 1; j <= time - 1; ++j) {
			addEdge(L(at(i, j)), R(at(i, j)), cap[i]);
		}
	}
	for (int i = 0; i < no_rub; ++i) {
		for (int j = 0; j < no_rub; ++j) {
			if (!reach[i][j]) {
				continue;
			}
			for (int k = 1; k <= time - 2; ++k) {
				addEdge(R(at(i, k)), L(at(j, k + 1)),
						std::numeric_limits<int>::max());
			}
		}
	}
	return dinic.solve() >= no_tou;
}

int main() {
	scanf("%d %d %d %d", &no_rub, &no_tou, &jump, &width);
	for (int i = 0; i < no_rub; ++i) {
		scanf("%d %d %d", &x[i], &y[i], &cap[i]);
		cap[i] = std::min(cap[i], no_tou);
	}
	if (jump >= width) {
		puts("1");
		return 0;
	}
	memset(reach, 0, sizeof(reach));
	for (int i = 0; i < no_rub; ++i) {
		for (int j = 0; j < no_rub; ++j) {
			reach[i][j] |= (SQR(x[i] - x[j]) + SQR(y[i] - y[j]) <= SQR(jump));
		}
	}
	int l = 1, r = no_rub + no_tou + 1;
	while (r - l > 1) {
		int m = (l + r) / 2;
		if (check(m)) {
			r = m;
		} else {
			l = m;
		}
	}
	int ans = check(l) ? l : (check(r) ? r : -1);
	if (ans == -1) {
		puts("IMPOSSIBLE");
	} else {
		printf("%d\n", ans);
	}
	return 0;
}

