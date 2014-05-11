#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;
typedef pair<int, PII> PIII;

#define F first
#define S second

const int N_MAX = (int) (1e5);

int n, m;
PIII a[N_MAX];
LL ans;

struct SegTree {
	static const int NODE_MAX = 1 << 18;
	bool delta[NODE_MAX];
	int f[NODE_MAX], g[NODE_MAX];
	LL sum[NODE_MAX];
	void init(int l, int r, int rt) {
		delta[rt] = false;
		f[rt] = g[rt] = sum[rt] = 0;
		if (l != r) {
			int m = (l + r) / 2;
			init(l, m, rt * 2);
			init(m + 1, r, rt * 2 + 1);
		}
	}
	void modify(int rt, int l, int r, int v) {
		delta[rt] = true;
		f[rt] = g[rt] = v;
		sum[rt] = (LL) v * (r - l + 1);
	}
	void insert(int l, int r, int rt, int sl, int sr, int v) {
		if (sl > r || sr < l) {
			return;
		}
		if (sl <= l && r <= sr) {
			if (v >= f[rt]) {
				modify(rt, l, r, v);
				return;
			}
			if (v <= g[rt]) {
				return;
			}
		}
		int m = (l + r) / 2;
		if (delta[rt]) {
			modify(rt * 2, l, m, f[rt]);
			modify(rt * 2 + 1, m + 1, r, f[rt]);
			delta[rt] = false;
		}
		insert(l, m, rt * 2, sl, sr, v);
		insert(m + 1, r, rt * 2 + 1, sl, sr, v);
		f[rt] = max(f[rt * 2], f[rt * 2 + 1]);
		g[rt] = min(g[rt * 2], g[rt * 2 + 1]);
		sum[rt] = sum[rt * 2] + sum[rt * 2 + 1];
	}
};

SegTree st;

int main() {
	while (scanf("%d %d", &n, &m) == 2) {
		if (!n && !m) {
			break;
		}
		for (int i = 0; i < n; ++i) {
			scanf("%d %d %d", &a[i].F, &a[i].S.F, &a[i].S.S);
		}
		std::sort(a, a + n);
		ans = (LL) m * m * m;
		st.init(1, m, 1);
		int pre = m;
		for (int i = n - 1, j; i >= 0; pre = a[i].F, i = j) {
			ans -= st.sum[1] * (pre - a[i].F);
			for (j = i; j >= 0 && a[j].F == a[i].F; --j) {
				st.insert(1, m, 1, 1, a[j].S.F, a[j].S.S);
			}
		}
		ans -= st.sum[1] * pre;
		printf("%lld\n", ans);
	}
	return 0;
}
