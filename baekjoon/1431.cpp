#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int N;
string serial[1001];
int sum;

int parsing(string str) {
	sum = 0;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] - '0' <= 9 && str[i] - '0' >= 0) {
			sum += str[i] - '0';
		}
	}
	return sum;
}

bool compare(string a, string b) {
	if (a.length() < b.length()) {
		return 1;
	}
	else if (a.length() > b.length()) {
		return 0;
	}
	else {
		if (parsing(a) != parsing(b))
			return parsing(a) < parsing(b);
		else
			return a < b;
	}
}

int main(void) {

	cin >> N;
	
	for (int i = 0; i < N; i++) {
		cin >> serial[i];
	}

	sort(serial, serial + N, compare);

	for (int i = 0; i < N; i++) {
		cout << serial[i] << endl;
	}

	return 0;
}
