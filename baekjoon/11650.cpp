#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
vector<pair<int, int> > v;

bool compare(pair<int,int> a, pair<int, int> b) {
	if (a.first < b.first)
		return 1;
	else if (a.first > b.first)
		return 0;
	else if (a.first == b.first) {
		return a.second < b.second;
	}
}

int main(void) {

	int N;
	scanf("%d", &N);

	int num1, num2;

	for (int i = 0; i < N; i++) {
		scanf("%d %d", &num1, &num2);
		v.push_back(pair<int, int>(num1, num2));
	}
	
	sort(v.begin(), v.end(), compare);

	for (int i = 0; i < N; i++) {
		printf("%d %d\n", v[i].first, v[i].second);
	}
	return 0;
}
