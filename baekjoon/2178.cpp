#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int n, m;
int maze[101][101];
int visited[101][101];
queue<pair<int, int> > points;
int load, bfsNode, nextNode;
int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };


void bfs(int y, int x) {

	for (int i = 0; i < 4; i++) {
		int nextX = x + dx[i];
		int nextY = y + dy[i];

		if (nextX >= m || nextY >= n || nextX < 0 || nextY < 0) continue;
		//방문한적 없고 0이 아니면 해당 좌표를 큐에 넣고 방문처리
		if (visited[nextY][nextX] == false && maze[nextY][nextX] != 0) {
			points.push({ nextY, nextX });
			visited[nextY][nextX] = true;
			nextNode++;
		}

	}
}

int main(void) {

	string num;
	cin >> n >> m; // n이 y, m이 x 좌표

	for (int i = 0; i < n; i++) {
		cin >> num;
		for (int j = 0; j < m; j++) {
			maze[i][j] = num[j] - '0';
		}
	}

	load = bfsNode = 1;
	nextNode = 0;
	points.push({ 0, 0 });
	visited[0][0] = true;
	while (!points.empty()) {
		pair<int, int> cor = points.front();
		// 최종 좌표에 도착하면 중단
		if (cor.first == n - 1 && cor.second == m - 1)
			break;
		bfs(cor.first, cor.second);
		bfsNode--;
		// 한번에 bfs를 처리해야 하는 수 - bfsNode가 0이 되면 다음 bfs를 돌릴 수로 초기화
		if (bfsNode == 0) {
			bfsNode = nextNode;
			nextNode = 0;
			load++;
		}
		points.pop();
	}
	cout << load << endl;
}
