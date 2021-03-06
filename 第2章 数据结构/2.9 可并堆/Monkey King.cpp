#include <algorithm>
#include <cstdio>

const int N = (int) (1e5);

template<int N, class T>
struct LeftistTree {
	int at, l[N], r[N], p[N], s[N];
	T v[N];
	void init() {
		at = -1;
	}
	int add(T val) {
		at++, l[at] = r[at] = -1, p[at] = at, s[at] = 1;
		v[at] = val;
		return at;
	}
	int root(int x) {
		return x == p[x] ? x : root(p[x]);
	}
	int merge(int x, int y) {
		if (x == -1) {
			return y;
		}
		if (y == -1) {
			return x;
		}
		if (v[x] < v[y]) {
			std::swap(x, y);
		}
		r[x] = merge(r[x], y);
		p[r[x]] = x;
		if (l[x] == -1 || s[l[x]] < s[r[x]]) {
			std::swap(l[x], r[x]);
		}
		s[x] = (r[x] == -1 ? 1 : s[r[x]] + 1);
		return x;
	}
	T top(int x) {
		return v[x];
	}
	int pop(int x) {
		if (l[x] != -1) {
			p[l[x]] = l[x];
		}
		if (r[x] != -1) {
			p[r[x]] = r[x];
		}
		int rt = merge(l[x], r[x]);
		l[x] = r[x] = -1, s[x] = 1;
		v[x] /= 2;
		return rt;
	}
};

LeftistTree<N, int> lt;

int n, m, val[N], at[N];

int main() {
	while (scanf("%d", &n) == 1) {
		lt.init();
		for (int i = 0; i < n; ++i) {
			scanf("%d", &val[i]);
			at[i] = lt.add(val[i]);
		}
		scanf("%d", &m);
		for (int i = 0, x, y; i < m; ++i) {
			scanf("%d %d", &x, &y);
			--x, --y;
			x = lt.root(at[x]);
			y = lt.root(at[y]);
			if (x != y) {
				int root = lt.merge(lt.pop(x), lt.pop(y));
				root = lt.merge(root, x);
				root = lt.merge(root, y);
				printf("%d\n", lt.top(root));
			} else {
				puts("-1");
			}
		}
	}
	return 0;
}

