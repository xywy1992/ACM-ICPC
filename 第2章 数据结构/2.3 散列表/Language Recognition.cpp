#include <cstdio>
#include <cstring>
#include <set>
#include <utility>

const int MAGIC = (int) (1e9 + 7);

#define F first
#define S second

template<int N, int M>
struct Trie {
	int at;
	bool final[N];
	int next[N][M], hash[N];
	int hashCode(int u) {
		if (hash[u]) {
			return hash[u];
		}
		hash[u] = 1;
		for (int i = 0; i < M; ++i) {
			hash[u] *= 31;
			if (next[u][i] != -1) {
				hash[u] += hashCode(next[u][i]);
			}
		}
		if (final[u]) {
			hash[u] ^= MAGIC;
		}
		return hash[u];
	}
	int add() {
		final[at] = false;
		memset(next[at], 0xff, sizeof(next[at]));
		hash[at++] = 0;
		return at - 1;
	}
	void init() {
		at = 0;
		add();
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

const int N = 150001;
const int M = 26;

Trie<N, M> trie;

int n, len, word[100];
char s[100];

struct Elem {
	int x;
	Elem(int _x = 0) :
			x(_x) {
	}
	bool operator<(const Elem & rhs) const {
		if (trie.hashCode(x) != trie.hashCode(rhs.x)) {
			return trie.hashCode(x) < trie.hashCode(rhs.x);
		}
		if (trie.final[x] != trie.final[rhs.x]) {
			return trie.final[x] < trie.final[rhs.x];
		}
		for (int i = 0; i < M; ++i) {
			int a = trie.next[x][i] == -1 ? 0 : 1;
			int b = trie.next[rhs.x][i] == -1 ? 0 : 1;
			if (a != b) {
				return a < b;
			}
		}
		return false;
	}
};

std::set<Elem> elems;

void addAll(int u) {
	if (elems.insert(Elem(u)).S) {
		for (int i = 0; i < M; ++i) {
			int v = trie.next[u][i];
			if (v != -1) {
				addAll(v);
			}
		}
	}
}

int main() {
	while (scanf("%d", &n) == 1) {
		trie.init();
		for (int i = 0; i < n; ++i) {
			scanf("%s", s);
			len = strlen(s);
			for (int j = 0; j < len; ++j) {
				word[j] = s[j] - 'a';
			}
			trie.insert(len, word);
		}
		elems.clear();
		addAll(0);
		printf("%d\n", elems.size());
	}
	return 0;
}

