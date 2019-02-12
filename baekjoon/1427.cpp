#include <iostream>
#include <algorithm>
#include <functional>
#include <utility>
#include <string>

using namespace std;

bool compare(int a, int b) {
	return a > b;
}

int main(void) {

	string num;
	cin >> num;

	int * arr = new int[num.size()];
	for (int i = 0; i < num.size(); i++) {
		arr[i] = num[i] - '0';
	}
	sort(arr, arr + num.size(), compare);
	for (int i = 0; i < num.size(); i++) {
		cout << arr[i];
	}
	return 0;
}
