#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
	int m, n;
	cin >> m >> n;
	std::vector<int> a, b;
	a.resize(m);
	b.resize(n);
	for (int i = 0; i < m; ++i) {
		cin >> a[i];
	}
	for (int i = 0; i < n; ++i) {
		cin >> b[i];
	}
	std::sort(a.begin(), a.end());
	std::sort(b.begin(), b.end());
	int max_a = *a.rbegin();
	int min_b = *b.begin();
	int cnt = 0;
	for (int i = max_a; i <= min_b; ++i) {
		bool state = true;
		while (state) {
			for (const auto elem : a) {
				if (i % elem != 0) {
					state = false;
					break;
				}
			}
			if (state == false) {
				break;
			}
			for (const auto elem : b) {
				if (elem % i != 0) {
					state = false;
					break;
				}
			}
			if (state == true) {
				++cnt;
			}
			state = false;
		}
	}
	std::cout << cnt << std::endl;
	return 0;
}
