#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <set>
#include <string>
#include <utility>

const int N = 100;
const int L = 20;

#define FOR(i, v) for(__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++i)
typedef std::set<std::string>::iterator SSIT;
typedef long long LONG;
const LONG INF = std::numeric_limits<long long>::max();

std::string s, t;
int l, n;
std::string a[N], b[N];
std::set<std::string> set[L + 1];

void insert(std::string & s) {
	int n = s.size();
	for (int i = 0; i < n; ++i) {
		set[n - i].insert(s.substr(i));
	}
}

const int S = N * 2 + 2;
std::map<std::string, int> at[2];
LONG f[2][S][S];

void floyd(int n, LONG f[S][S]) {
	for (int k = 0; k < n; ++k) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (f[i][k] != INF && f[k][j] != INF) {
					f[i][j] = std::min(f[i][j], f[i][k] + f[k][j]);
				}
			}
		}
	}
}

LONG gao() {
	int x = 0, y = 1;
	at[x].clear();
	for (int i = 1; i <= l; ++i, std::swap(x, y)) {
		int cur = set[i].size();
		SSIT it = set[i].begin();
		at[y].clear();
		for (int j = 0; j < cur; ++j, ++it) {
			at[y][*it] = j;
			std::fill(f[y][j], f[y][j] + cur, INF);
			f[y][j][j] = 0;
		}

		for (int j = 0; j < n; ++j) {
			if ((int) a[j].size() == i) {
				int u = at[y][a[j]];
				int v = at[y][b[j]];
				f[y][u][v] = std::min(f[y][u][v], (LONG) 1);
			}
		}

		if (i > 1) {
			SSIT u = set[i].begin();
			for (int u1 = 0; u1 < cur; ++u1, ++u) {
				SSIT v = set[i].begin();
				for (int v1 = 0; v1 < cur; ++v1, ++v) {
					if ((*u)[0] != (*v)[0]) {
						continue;
					}
					int i1 = at[x][(*u).substr(1)];
					int i2 = at[x][(*v).substr(1)];
					f[y][u1][v1] = std::min(f[y][u1][v1], f[x][i1][i2]);
				}
			}
		}

		floyd(cur, f[y]);

	}
	return f[x][at[x][s]][at[x][t]];
}

int main() {
	int test = 1;
	while (std::cin >> s && s != ".") {
		std::cin >> t >> n;
		l = s.size();
		for (int i = 1; i <= l; ++i) {
			set[i].clear();
		}
		insert(s);
		insert(t);
		for (int i = 0; i < n; ++i) {
			std::cin >> a[i] >> b[i];
			if ((int) a[i].size() <= l) {
				insert(a[i]);
				insert(b[i]);
			}
		}
		LONG ans = gao();
		if (ans == INF) {
			std::cout << "Case " << test++ << ": No solution" << std::endl;
		} else {
			std::cout << "Case " << test++ << ": " << ans << std::endl;
		}
	}
	return 0;
}

