#include <algorithm>
#include <cmath>
#include <cstdio>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

#define PB push_back
#define MP std::make_pair

#define F first
#define S second
#define FOR(i, v) for(__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++i)

template<int N, class T>
struct Prim {
	std::vector<std::pair<int, std::pair<T, T> > > e[N];
	void init(int n) {
		for (int i = 0; i < n; ++i) {
			e[i].clear();
		}
	}
	void add(int u, int v, T w1, T w2) {
		e[u].PB(MP(v, MP(w1, w2)));
		e[v].PB(MP(u, MP(w1, w2)));
	}
	struct Elem {
		int u;
		T d, w1, w2;
		Elem(int _u = 0, T _d = 0, T _w1 = 0, T _w2 = 0):u(_u), d(_d), w1(_w1), w2(_w2) {}
		bool operator<(const Elem & rhs)const {
			return d > rhs.d;
		}
	};
	T dis[N];
	bool vis[N];
	std::priority_queue<Elem> q;
	T gao(T k, int n) {
		while(!q.empty()) {
			q.pop();
		}
		std::fill(dis, dis + n, std::numeric_limits<T>::max());
		std::fill(vis, vis + n, false);
		dis[0] = 0;
		q.push(Elem(0, 0, 0, 0));
		T x = 0, y = 0;
		while(!q.empty()) {
			int u = q.top().u;
			T w1 = q.top().w1, w2 = q.top().w2;
			q.pop();
			if(vis[u]) {
				continue;
			}
			vis[u] = true;
			x += w1;
			y += w2;
			FOR(i, e[u]) {
				int v = i->F;
				T w1 = (i->S).F;
				T w2 = (i->S).S;
				if(!vis[v] && dis[v] > (w2 - k * w1)) {
					dis[v] = (w2 - k * w1);
					q.push(Elem(v, dis[v], w1, w2));
				}
			}
		}
		return y / x;
	}
};

const int N = (int) (1e3);
const int M = (int) (5e5);
const double EPS = (double) (1e-10);
int n, m;
Prim<N, double> prim;

int main() {
	while (scanf("%d %d", &n, &m) == 2) {
		prim.init(n);
		for (int i = 0, u, v, w1, w2; i < m; ++i) {
			scanf("%d %d %d %d", &u, &v, &w1, &w2);
			--u, --v;
			prim.add(u, v, w1, w2);
		}
		double ans = 1.0;
		while (true) {
			double tmp = prim.gao(ans, n);
			if (fabs(ans - tmp) < EPS) {
				break;
			} else {
				ans = tmp;
			}
		}
		printf("%.12lf\n", ans);
	}
	return 0;
}

