#include <queue>
#include <string>
#include <cstdio>
#include <cstring>

using namespace std;

#define FOR(i, n) for(int i = 0; i < (n); ++i)

int n, m, k, rev;
char s[100];
deque<string> a, b;

void insert(string & s, bool head) {
	if (head) {
		a.push_front(s);
	} else {
		a.push_back(s);
	}
	if (a.size() > k) {
		if (head) {
			b.push_front(a.back());
			a.pop_back();
		} else {
			b.push_front(a.front());
			a.pop_front();
		}
	}
}

void out(deque<string> & q, bool head) {
	if (head) {
		while (!q.empty()) {
			puts(q.front().c_str());
			q.pop_front();
		}
	} else {
		while (!q.empty()) {
			puts(q.back().c_str());
			q.pop_back();
		}
	}
}

int main() {
	while (scanf("%d %d %d", &n, &m, &k) == 3) {
		a.clear();
		b.clear();
		rev = 1;
		FOR(i, n)
		{
			scanf("%s", s);
			if (i < k) {
				a.push_back(s);
			} else {
				b.push_back(s);
			}
		}
		FOR(i, m)
		{
			scanf("%s", s);
			if (s[0] == 'R') {
				rev ^= 1;
			} else {
				string what = "";
				for (int j = 4, l = strlen(s); j < l - 1; ++j) {
					what += s[j];
				}
				insert(what, rev);
			}
		}
		out(a, rev);
		out(b, true);
	}
	return 0;
}
