#include <algorithm>
#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>
#include <climits>

typedef std::pair<int, int> PII;
typedef std::pair<int, PII> PIII;
typedef std::vector<PII> VII;
#define F first
#define S second
#define PB push_back
#define MP std::make_pair
#define FOR(i, v) for(__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++i)

const int N = 500;
const int M = N * (N - 1) / 2;

template<int N>
struct DisjointSet {
	int p[N];
	void init(int n) {
		for (int i = 0; i < n; ++i) {
			p[i] = i;
		}
	}
	int getp(int i) {
		return i == p[i] ? i : (p[i] = getp(p[i]));
	}
	bool setp(int i, int j) {
		i = getp(i);
		j = getp(j);
		p[i] = j;
		return i != j;
	}
};

template<int N>
struct Tree {
	VII e[N];
	int f[N][N];
	void init(int n) {
		for (int i = 0; i < n; ++i) {
			e[i].clear();
		}
	}
	void add(int u, int v, int w) {
		e[u].PB(MP(v, w));
		e[v].PB(MP(u, w));
	}
	void dfs(int u, int p, int s) {
		FOR(i, e[u]) {
			int v = i->F;
			if(v != p) {
				f[s][v] = std::max(f[s][u], i->S);
				dfs(v, u, s);
			}
		}
	}
	void gao(int n) {
		memset(f, 0, sizeof(f));
		for(int i = 0; i < n; ++i) {
			dfs(i, -1, i);
		}
	}
	int maxedge(int u, int v) {
		return f[u][v];
	}
};

int n, m;
PIII e[M];
bool flag[M];
DisjointSet<N> ds;
Tree<N> tree;

int main() {
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i < m; ++i) {
			scanf("%d %d %d", &e[i].S.F, &e[i].S.S, &e[i].F);
			e[i].S.F--, e[i].S.S--;
		}
		std::sort(e, e + m);
		ds.init(n);
		tree.init(n);
		memset(flag, 0, sizeof(flag));
		int mst = 0;
		for (int i = 0; i < m; ++i) {
			int u = e[i].S.F, v = e[i].S.S;
			if (ds.setp(u, v)) {
				flag[i] = true;
				mst += e[i].F;
				tree.add(u, v, e[i].F);
			}
		}
		tree.gao(n);
		int sst = INT_MAX;
		if (m == n - 1) {
			sst = -1;
		} else {
			for (int i = 0; i < m; ++i) {
				if (!flag[i]) {
					int u = e[i].S.F, v = e[i].S.S;
					sst = std::min(sst, mst + e[i].F - tree.maxedge(u, v));
				}
			}
		}
		printf("Cost: %d\nCost: %d\n", mst, sst);
	}
	return 0;
}
