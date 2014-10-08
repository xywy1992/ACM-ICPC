struct StringHash {
	const unsigned long long MAGIC = 31;
	vector<unsigned long long> h, b;
	void init(string &s) {
		int n = s.size();
		h = vector<unsigned long long>(n + 1);
		b = vector<unsigned long long>(n + 1);
		h[0] = 0;
		b[0] = 1;
		for (int i = 1; i <= n; ++i) {
			h[i] = h[i - 1] * MAGIC + s[i - 1];
			b[i] = b[i - 1] * MAGIC;
		}
	}
	//[l, r), from 0.
	unsigned long long hash(int l, int r) {
		return h[r] - h[l] * b[r - l];
	}
};
