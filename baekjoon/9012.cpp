#include <iostream>
#include <stack>
#include <string>

using namespace std;

stack<char> s;

int main(void) {

	int n;
	string str;

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> str;
		for (int j = 0; j < str.length(); j++) {
			if (str[j] == '(' || s.empty()) s.push(str[j]);
			else if (s.top() == '(') s.pop();
		}

		if (s.empty()) cout << "YES" << endl;
		else cout << "NO" << endl;
		while (!s.empty())
			s.pop();
	}
	return 0;

}
