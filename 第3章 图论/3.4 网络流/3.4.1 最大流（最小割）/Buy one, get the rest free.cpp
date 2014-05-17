#include <algorithm>
#include <cstdio>
#include <iterator>
#include <limits>
#include <vector>

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

#define PB push_back

const int N = 400;
const int M = N * N;
Dinic<N, M, int> dinic;

struct flight_st {
	int from, to, carry, cost, time;
	void read() {
		scanf("%d %d %d %d %d", &from, &to, &carry, &cost, &time);
		--from, --to;
	}
} flight[1000];

int T, city_cnt, deadline, flight_cnt, people[30], people_cnt;
std::vector<int> cost;

int at(int city, int day) {
	return city * deadline + day;
}

bool check(int cost) {
	int t = at(city_cnt - 1, deadline - 1);
	int s = t + 1;
	int n = s + 1;
	dinic.init(n, s, t);
	for (int i = 0; i < city_cnt; ++i) {
		dinic.add(s, at(i, 0), people[i]);
		dinic.add(at(i, 0), s, 0);
	}
	for (int i = 0; i < flight_cnt; ++i) {
		if (flight[i].cost > cost) {
			continue;
		}
		dinic.add(at(flight[i].from, flight[i].time), at(flight[i].to, flight[i].time + 1), flight[i].carry);
		dinic.add(at(flight[i].to, flight[i].time + 1), at(flight[i].from, flight[i].time), 0);
	}
	for (int i = 0; i < city_cnt; ++i) {
		for (int j = 0; j < deadline - 1; ++j) {
			dinic.add(at(i, j), at(i, j + 1), std::numeric_limits<int>::max());
			dinic.add(at(i, j + 1), at(i, j), 0);
		}
	}
	return dinic.solve() == people_cnt;
}

int bs(int l, int r) {
	while (r - l > 1) {
		int m = (l + r) >> 1;
		if (check(cost[m])) {
			r = m;
		} else {
			l = m;
		}
	}
	return check(cost[l]) ? cost[l] : (check(cost[r]) ? cost[r] : -1);
}

int main() {
	scanf("%d", &T);
	for (int t = 1; t <= T; ++t) {
		scanf("%d %d %d", &city_cnt, &deadline, &flight_cnt);
		++deadline;
		cost.clear();
		cost.PB(0);
		for (int i = 0; i < flight_cnt; ++i) {
			flight[i].read();
			cost.PB(flight[i].cost);
		}
		std::sort(cost.begin(), cost.end());
		cost.erase(std::unique(cost.begin(), cost.end()), cost.end());
		people_cnt = 0;
		for (int i = 0; i < city_cnt; ++i) {
			scanf("%d", &people[i]);
			people_cnt += people[i];
		}
		int ans = bs(0, cost.size() - 1);
		if (ans == -1) {
			printf("Case #%d: Impossible\n", t);
		} else {
			printf("Case #%d: %d\n", t, ans);
		}
	}
	return 0;
}

