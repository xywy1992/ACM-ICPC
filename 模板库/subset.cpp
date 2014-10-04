#include <iostream>

using namespace std;

int main() {
	int s;
	cin >> s;
	for (int i = s; i; i = (i - 1) & s) {
		cout << i << " " << (i ^ s) << endl;
	}
	return 0;
}
