#include <iostream>
#include <vector>
#include <algorithm>

int get_optimal(std::vector<int> arr, int pivot, int k, int l) {
	int inc, dec, cost;
	inc = dec = cost = 0;
	for (const auto i : arr) {
		if (i < pivot) {
			inc += (pivot - i);
		} else  if (i > pivot) {
			dec += (i - pivot);
		}
	}
	if (dec > inc) {
		return std::numeric_limits<int>::max();
	}
	cost += dec * k;
	inc -= dec;
	cost += inc * l;
	return cost;
}

int main() {
	int a, k, l;
	std::cin >> a >> k >> l;
	std::vector<int> arr;
	arr.resize(a);
	for (int i = 0; i < a; ++i) {
		std::cin >> arr[i];
	}
	std::sort(arr.begin(), arr.end());
	int min = *arr.begin();
	int max = *arr.rbegin();
	int optimal = std::numeric_limits<int>::max();
	for (int i = min; i <= max; i++) {
		int temp = get_optimal(arr, i, k, l);
		if (optimal > temp) {
			optimal = temp;
		}
	}
	std::cout << optimal << std::endl;
}