#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

const int N = 200;
const int M = N * (N - 1) / 2;
int n, m, a[M], b[M], cnt[N][N];
bool g[N][N], cur[N][N];

bool judge(int u, int v) {
	if (!cnt[u][v]) {
		return false;
	}
	for (int i = 0; i < n; ++i) {
		if (i != v && cur[i][u] && !cur[i][v] && g[i][v]
				&& cnt[i][v] - 1 <= 0) {
			return false;
		}
		if (i != u && cur[i][v] && !cur[i][u] && g[i][u]
				&& cnt[i][u] - 1 <= 0) {
			return false;
		}
	}
	return true;
}

int main() {
	while (scanf("%d %d", &n, &m) == 2) {
		if (!n && !m) {
			break;
		}
		memset(g, 0, sizeof(g));
		memset(cur, 0, sizeof(cur));
		for (int i = 0; i < m; ++i) {
			scanf("%d %d", &a[i], &b[i]);
			--a[i], --b[i];
			g[b[i]][a[i]] = g[a[i]][b[i]] = cur[b[i]][a[i]] = cur[a[i]][b[i]] =
					true;
		}
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (i == j) {
					continue;
				}
				for (int k = 0; k < n; ++k) {
					if (g[i][k] && g[j][k]) {
						cnt[i][j]++;
					}
				}
			}
		}
		std::vector<int> ans;
		for (int i = m - 1; i >= 0; --i) {
			if (judge(a[i], b[i])) {
				ans.push_back(i);
				cur[a[i]][b[i]] = cur[b[i]][a[i]] = false;
				for (int j = 0; j < n; ++j) {
					if (cur[j][a[i]]) {
						cnt[j][b[i]]--, cnt[b[i]][j]--;
					}
					if (cur[j][b[i]]) {
						cnt[j][a[i]]--, cnt[a[i]][j]--;
					}
				}
			}
		}

		std::reverse(ans.begin(), ans.end());
		printf("%d", (int) ans.size());
		for (int i = 0; i < (int) ans.size(); ++i) {
			printf(" %d", ans[i] + 1);
		}
		puts("");
	}
	return 0;
}

