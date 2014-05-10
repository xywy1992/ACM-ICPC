#include <cstdio>
#include <vector>
#include <cstring>
#include <utility>
#include <algorithm>

typedef std::pair<int, int> PII;

#define PB push_back
#define MP std::make_pair
#define F first
#define S second
#define FOREACH(i, v) for(__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++i)

const int N_MAX = (int) (3e5);
const int M_MAX = (int) (2e5);
const int Q_MAX = (int) (2e5);

int n, m, q;
PII know[M_MAX], son[N_MAX], at[N_MAX];
std::vector<PII> query;
int dfn, ans[Q_MAX];
bool vis[N_MAX];

template<class T>
struct BIT {
	static const int VAL_MAX = (int) (1e5);
	T a[VAL_MAX + 1];
	void init() {
		memset(a, 0, sizeof(a));
	}
	T read(int idx) {
		T sum = 0;
		for (int i = idx; i; i -= (i & -i)) {
			sum += a[i];
		}
		return sum;
	}
	void update(int idx, T val) {
		for (int i = idx; i <= VAL_MAX; i += (i & -i)) {
			a[i] += val;
		}
	}
	T readSingle(int idx) {
		T sum = a[idx];
		for (int i = idx - 1, j = idx - (idx & -idx); i != j; i -= (i & -i)) {
			sum -= a[i];
		}
		return sum;
	}
};
BIT<int> bit;

struct Event {
	int sign, y, x1, x2, id;
	Event() {
	}
	Event(int _sign, int _y, int _x1, int _x2 = 0, int _id = 0) :
			sign(_sign), y(_y), x1(_x1), x2(_x2), id(_id) {
	}
	bool operator<(const Event & rhs) const {
		if (y != rhs.y) {
			return y < rhs.y;
		} else {
			return sign < rhs.sign;
		}
	}
};
std::vector<Event> event;

void dfs(int u) {
	vis[u] = true;
	if (son[u] == MP(-1, -1)) {
		at[u] = MP(dfn, dfn);
		dfn++;
	} else {
		dfs(son[u].F), dfs(son[u].S);
		at[u] = MP(at[son[u].F].F, at[son[u].S].S);
	}
}

void init() {
	memset(vis, 0, sizeof(vis));
	dfn = 1;
	for (int i = n - 1; i >= 0; --i) {
		if (!vis[i]) {
			dfs(i);
		}
	}
}

void solve() {
	init();
	event.clear();
	for (int i = 0; i < m; ++i) {
		event.PB(Event(0, at[know[i].S].F, at[know[i].F].F));
	}
	for (int i = 0; i < (int) query.size(); ++i) {
		int a = query[i].F, b = query[i].S;
		event.PB(Event(-1, at[b].F, at[a].F, at[a].S, i));
		event.PB(Event(+1, at[b].S, at[a].F, at[a].S, i));
	}
	std::sort(event.begin(), event.end());
	bit.init();
	FOREACH(i, event)
	{
		if (i->sign == -1) {
			ans[i->id] = -(bit.read(i->x2) - bit.read(i->x1 - 1));
		} else if (i->sign == +1) {
			ans[i->id] += (bit.read(i->x2) - bit.read(i->x1 - 1));
		} else {
			bit.update(i->x1, 1);
		}
	}
	for (int i = 0; i < (int) query.size(); ++i) {
		puts(ans[i] > 0 ? "YES" : "NO");
	}
}

int main() {
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i < m; ++i) {
			scanf("%d %d", &know[i].F, &know[i].S);
			--know[i].F, --know[i].S;
		}
		scanf("%d", &q);
		query.clear();
		std::fill(son, son + n, MP(-1, -1));
		for (int i = 0, cmd, a, b; i < q; ++i) {
			scanf("%d %d %d", &cmd, &a, &b);
			--a, --b;
			if (cmd == 1) {
				query.PB(MP(a, b));
			} else {
				son[n++] = MP(a, b);
			}
		}
		solve();
	}
	return 0;
}
