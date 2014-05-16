#include <cstring>

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
	//[0, n]
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
};

