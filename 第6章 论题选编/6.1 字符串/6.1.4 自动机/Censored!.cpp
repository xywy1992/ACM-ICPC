#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>

struct BigNum {
	int size, bit[200];
	BigNum() {
	}
	BigNum(bool flag) {
		size = 1;
		memset(bit, 0, sizeof(bit));
		if (flag) {
			bit[0] = 1;
		}
	}
	void print() {
		for (int i = size - 1; i >= 0; --i) {
			printf("%d", bit[i]);
		}
		puts("");
	}
};
BigNum operator+(BigNum & a, BigNum & b) {
	BigNum c = BigNum(false);
	c.size = 0;
	int carry = 0;
	for (int i = 0; i < std::max(a.size, b.size); ++i) {
		carry += a.bit[i] + b.bit[i];
		c.bit[c.size++] = carry % 10;
		carry /= 10;
	}
	while (carry) {
		c.bit[c.size++] = carry % 10;
		carry /= 10;
	}
	return c;
}

template<int N, int M>
struct AC {
	int n, child[N][M], fail[N], q[N];
	bool accept[N];
	int add() {
		n++;
		memset(child[n], 0xff, sizeof(child[n]));
		fail[n] = -1;
		accept[n] = false;
		return n;
	}
	void init() {
		n = -1;
		add();
	}
	void insert(int * s, int l) {
		int at = 0;
		for (int i = 0; i < l; ++i) {
			if (child[at][s[i]] == -1) {
				child[at][s[i]] = add();
			}
			at = child[at][s[i]];
		}
		accept[at] = true;
	}
	int find(int u, int ch) {
		while (u > 0) {
			u = fail[u];
			if (child[u][ch] != -1) {
				return child[u][ch];
			}
		}
		return u;
	}
	void build() {
		int st = 0, ed = 0;
		q[ed++] = 0;
		while (st != ed) {
			int u = q[st++];
			for (int i = 0; i < M; ++i) {
				if (child[u][i] == -1) {
					child[u][i] = find(u, i);
				} else {
					int v = child[u][i];
					q[ed++] = v;
					fail[v] = find(u, i);
					accept[v] |= accept[fail[v]];
				}
			}
		}
	}

	BigNum f[2][N], ans;

	void solve(int l, int m) {
		int x = 0, y = 1;
		f[x][0] = BigNum(true);
		for (int i = 1; i <= n; ++i) {
			f[x][i] = BigNum(false);
		}
		for (int i = 0; i < l; ++i, std::swap(x, y)) {
			for (int j = 0; j <= n; ++j) {
				f[y][j] = BigNum(false);
			}
			for (int j = 0; j <= n; ++j) {
				if (accept[j]) {
					continue;
				}
				for (int k = 0; k < m; ++k) {
					if (accept[child[j][k]]) {
						continue;
					}
					f[y][child[j][k]] = f[y][child[j][k]] + f[x][j];
				}
			}
		}
		ans = BigNum(false);
		for (int i = 0; i <= n; ++i) {
			ans = ans + f[x][i];
		}
		ans.print();
	}
};

AC<501, 50> ac;
std::map<char, int> map;
int n, m, p, s[100], l;
char buf[100];

int main() {
	while (scanf("%d %d %d %s", &n, &m, &p, buf) == 4) {
		map.clear();
		for (int i = 0; i < n; ++i) {
			map[buf[i]] = i;
		}
		ac.init();
		for (int i = 0; i < p; ++i) {
			scanf("%s", buf);
			l = strlen(buf);
			for (int i = 0; i < l; ++i) {
				s[i] = map[buf[i]];
			}
			ac.insert(s, l);
		}
		ac.build();
		ac.solve(m, n);
	}
	return 0;
}

