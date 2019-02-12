#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> v[1001];
int check[1001];

void bfs(int start) {

	queue<int> q;
	q.push(start);
	check[start] = true; // 방문처리
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		cout << x << ' ';
		for (int i = 0; i < v[x].size(); i++) {
			int y = v[x][i];
			if (!check[y]) {
				q.push(y);
				check[y] = true;
			}
		}
	}
}

void dfs(int start) {
	if (check[start]) return;
	check[start] = true; // 방문 처리 
	cout << start << ' ';
	for (int i = 0; i < v[start].size(); i++) {
		int y = v[start][i];
		dfs(y);
	}
}

int main(void) {

	int node, edge, start;
	cin >> node >> edge >> start;

	for (int i = 0; i < edge; i++) {
		int n1, n2;
		cin >> n1 >> n2;
		v[n1].push_back(n2); // 양방향으로 연결
		v[n2].push_back(n1);
	}

	// 작은 점부터 방문하기 위해 sorting
	for (int i = 0; i < 1001; i++) {
		sort(v[i].begin(), v[i].end());
	}

	dfs(start); // DFS 후 방문처리한 배열을 다시 초기화 
	for (int i = 0; i < 1001; i++) {
		check[i] = false;
	}

	cout << endl;
	bfs(start); // BFS 처리

	return 0;
}
