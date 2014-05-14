#include <cstring>

template<int N, int M>
struct Trie {
	int at;
	bool final[N];
	int next[N][M];
	void init() {
		at = -1;
		add();
	}
	int add() {
		at++;
		final[at] = false;
		memset(next[at], 0xff, sizeof(next[at]));
		return at;
	}
	void insert(int n, int * word) {
		int u = 0;
		for (int i = 0; i < n; ++i) {
			int & v = next[u][word[i]];
			if (v == -1) {
				v = add();
			}
			u = v;
		}
		final[u] = true;
	}
};

