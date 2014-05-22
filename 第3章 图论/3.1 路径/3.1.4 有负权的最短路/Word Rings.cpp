#include <cmath>
#include <cstdio>
#include <cstring>
#include <iterator>
#include <utility>
#include <vector>

const int N = 26 * 26;
const int L = 1000;
const double EPS = 1e-4;
int n;
char s[L + 1];

typedef std::pair<int, int> PII;
typedef std::vector<PII> ADJ;
#define MP std::make_pair
#define PB push_back
#define F first
#define S second
#define FOR(i, v) for(__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++i)
ADJ e[N];

int encode(char a, char b) {
	return (a - 'a') * 26 + (b - 'a');
}

double dis[N];
int cnt[N], q[N * 1000];
bool mark[N];
bool spfa(double delta) {
	memset(dis, 0, sizeof(dis));
	memset(cnt, 0, sizeof(cnt));
	int st = 0, ed = 0;
	for (int i = 0; i < N; ++i) {
		q[ed++] = i, mark[i] = true;
	}
	while (st != ed) {
		int u = q[st++];
		mark[u] = false;
		FOR(i, e[u])
		{
			int v = i->F;
			double w = delta - i->S;
			if (dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				cnt[v]++;
				if (cnt[v] >= N) {
					return true;
				}
				if (!mark[v]) {
					q[ed++] = v, mark[v] = true;
				}
			}
		}
	}
	return false;
}

int main() {
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < N; ++i) {
			e[i].clear();
		}
		for (int i = 0; i < n; ++i) {
			scanf("%s", s);
			int l = strlen(s);
			if (l >= 4) {
				e[encode(s[0], s[1])].PB(MP(encode(s[l - 2], s[l - 1]), l));
			}
		}
		if (!spfa(0)) {
			puts("No solution.");
			continue;
		}
		double l = 0, r = 1000, ans;
		while (fabs(r - l) > EPS) {
			ans = (l + r) / 2;
			if (spfa(ans)) {
				l = ans;
			} else {
				r = ans;
			}
		}

		printf("%.2lf\n", ans);
	}
	return 0;
}

