#include <cstdio>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

template<int N, class Flow, class Cost>
struct MinCostMaxFlow {
	struct NegativeCostCircuitExistsException {
	};

	struct Edge {
		int v;
		Flow c;
		Cost w;
		int b;
		Edge(int v, Flow c, Cost w, int b) :
				v(v), c(c), w(w), b(b) {
		}
	};

	int n, s, t;
	std::vector<Edge> e[N];

	void init(int n, int s, int t) {
		this->n = n;
		this->s = s;
		this->t = t;
		for (int i = 0; i < n; ++i) {
			e[i].clear();
		}
	}

	void add(int a, int b, Flow c, Cost w) {
		e[a].push_back(Edge(b, c, w, e[b].size()));
		e[b].push_back(Edge(a, 0, -w, e[a].size() - 1));
	}

	bool mark[N];
	Flow maxc[N];
	Cost minw[N];
	int dist[N];
	Edge* prev[N];

	bool spfa() {
		std::queue<int> q;
		std::fill(mark, mark + n, false);
		std::fill(maxc, maxc + n, 0);
		std::fill(minw, minw + n, std::numeric_limits<Cost>::max());
		std::fill(dist, dist + n, 0);
		std::fill(prev, prev + n, (Edge*) NULL);
		mark[s] = true;
		maxc[s] = std::numeric_limits<Cost>::max();
		minw[s] = 0;

		q.push(s);
		while (!q.empty()) {
			int cur = q.front();
			mark[cur] = false;
			q.pop();
			for (typename std::vector<Edge>::iterator it = e[cur].begin();
					it != e[cur].end(); ++it) {
				Flow c = std::min(maxc[cur], it->c);
				if (c == 0) {
					continue;
				}

				int v = it->v;
				Cost w = minw[cur] + it->w;
				if (minw[v] > w || (minw[v] == w && maxc[v] < c)) { // TODO
					maxc[v] = c;
					minw[v] = w;
					dist[v] = dist[cur] + 1;
					if (dist[v] >= n) {
						return false;
					}
					prev[v] = &*it;
					if (!mark[v]) {
						mark[v] = true;
						q.push(v);
					}
				}
			}
		}
		return true;
	}

	std::pair<Flow, Cost> gao() {
		Flow sumc = 0;
		Cost sumw = 0;
		while (true) {
			if (!spfa()) {
				throw NegativeCostCircuitExistsException();
			} else if (maxc[t] == 0) {
				break;
			} else {
				Flow c = maxc[t];
				sumc += c;
				sumw += c * minw[t];

				int cur = t;
				while (cur != s) {
					Edge* e1 = prev[cur];
					e1->c -= c;
					Edge* e2 = &e[e1->v][e1->b];
					e2->c += c;
					cur = e2->v;
				}
			}
		}
		return std::make_pair(sumc, sumw);
	}
};

const int N = 40;
const int M = 2000;
#define L(X) ((X) * 2)
#define R(X) ((X) * 2 + 1)

int T, n, m, k, a[M], b[M], c[M];
MinCostMaxFlow<N * 2 + 2, int, int> mcmf;

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d %d", &n, &m, &k);
		for (int i = 0; i < m; ++i) {
			scanf("%d %d %d", &a[i], &b[i], &c[i]);
		}
		int s = n * 2, t = n * 2 + 1;
		mcmf.init(n * 2 + 2, s, t);
		for (int i = 0; i < n; ++i) {
			mcmf.add(s, L(i), k, 0);
			mcmf.add(R(i), t, k, 0);
		}
		for (int i = 0; i < m; ++i) {
			mcmf.add(L(a[i]), R(b[i]), 1, c[i]);
		}
		std::pair<int, int> ans = mcmf.gao();
		if (ans.first < k * n) {
			puts("-1");
		} else {
			printf("%d\n", ans.second);
		}
	}
	return 0;
}

