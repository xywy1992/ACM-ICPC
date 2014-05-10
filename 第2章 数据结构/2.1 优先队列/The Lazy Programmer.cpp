#include <queue>
#include <cstdio>
#include <utility>
#include <algorithm>

#define PII std::pair<int, int>
#define MP std::make_pair
#define F first
#define S second

const int N_MAX = (int) (1e5);

int n;
std::pair<int, PII> work[N_MAX];
std::priority_queue<PII> q;

int main() {
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; ++i) {
			scanf("%d %d %d", &work[i].S.F, &work[i].S.S, &work[i].F);
		}
		std::sort(work, work + n);
		while (!q.empty()) {
			q.pop();
		}
		double ans = 0;
		for (int i = 0, j, t = 0; i < n; i = j) {
			int need = 0;
			for (j = i; j < n && work[i].F == work[j].F; ++j) {
				need += work[j].S.S;
				q.push(MP(work[j].S.F, work[j].S.S));
			}
			if (work[i].F - t >= need) {
				t += need;
			} else {
				need -= (work[i].F - t);
				t = work[i].F;
				while (need > 0) {
					int cost = q.top().F, left = q.top().S;
					q.pop();
					if (need >= left) {
						ans += ((double) left) / cost;
						need -= left;
					} else {
						ans += ((double) need) / cost;
						left -= need;
						q.push(MP(cost, left));
						need = 0;
					}
				}
			}
		}
		printf("%.2f\n", ans);
	}
	return 0;
}
