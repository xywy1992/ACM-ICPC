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

