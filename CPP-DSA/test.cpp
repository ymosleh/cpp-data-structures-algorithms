#include <iostream>
#include <vector>
#include <ranges>

using namespace std;

int main() {
	vector<int> nums = { 1, 2, 3, 4, 5 };

		// size() == size_t == unsigned 64 bit type.
	for (auto i : views::iota(0uLL, nums.size())) {
		cout << "Index: " << i << ", Value: " << nums[i] << endl;
	}

	return 0;
}