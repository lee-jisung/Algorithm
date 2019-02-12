#include <iostream>
#include <cstdio>
#include <stack>
#include <string>

using namespace std;

stack<int> s;

int main(void) {

	string str;
	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		cin >> str;

		if (str == "push") {
			int num;
			scanf("%d", &num);
			s.push(num);
		}
		else if (str == "top") {
			if (s.empty()) {
				printf("-1\n");
			}else printf("%d\n", s.top());
		}
		else if (str == "pop") {
			if (s.empty())
				printf("-1\n");
			else {
				printf("%d\n", s.top());
				s.pop();
			}
		}
		else if (str == "size") {
			printf("%d\n", s.size());
		}
		else {
			if (s.empty()) printf("1\n");
			else printf("0\n");
		}

	}
    return 0;

}
