#include <algorithm>
#include <climits>
#include <cstdio>
#include <iterator>
#include <map>
#include <set>
#include <utility>
#include <vector>

typedef std::set<int>::iterator SIIT;
typedef std::pair<SIIT, bool> P;

#define PB push_back
#define FOR(i, v) for(__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++i)
#define F first
#define S second

const int N = (int) (5e4);
int n, m, w[N];
std::vector<int> adj[N];
std::set<int> set[N];

int merge(std::set<int> & a, std::set<int> & b) {
	if (a.size() < b.size()) {
		std::swap(a, b);
	}
	int ans = INT_MAX;
	SIIT l, r;
	FOR(i, b)
	{
		P p = a.insert(*i);
		if (!p.S) {
			ans = 0;
			continue;
		}
		l = r = p.F;
		if (l != a.begin()) {
			--l;
			ans = std::min(ans, *i - *l);
		}
		++r;
		if (r != a.end()) {
			ans = std::min(ans, *r - *i);
		}
	}
	return ans;
}

void dfs(int u) {
	if (u < n - m) {
		w[u] = INT_MAX;
		set[u].clear();
		FOR(i, adj[u])
		{
			int v = *i;
			dfs(v);
			if (v < n - m) {
				w[u] = std::min(w[u], w[v]);
			}
			w[u] = std::min(w[u], merge(set[u], set[v]));
		}
	} else {
		set[u].clear();
		set[u].insert(w[u]);
	}
}

int main() {
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i < n; ++i) {
			adj[i].clear();
		}
		for (int i = 1, j; i < n; ++i) {
			scanf("%d", &j);
			adj[j - 1].PB(i);
		}
		for (int i = 0; i < m; ++i) {
			scanf("%d", &w[n - m + i]);
		}
		dfs(0);
		for (int i = 0; i < n - m; ++i) {
			printf("%d%s", w[i], i == n - m - 1 ? "\n" : " ");
		}
	}
	return 0;
}

