#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int m, n;
int tomato[1001][1001];
queue<pair<int, int> > points;
int bfsOnes;  // 현재 처리해야 할 1의 개수 
int nextOnes; // 다음 1이 몇개 생기는지
int days; // 토마토가 익는 일수
int dx[4] = { 1, 0, -1, 0 }; // 상화좌우 참조 위함 
int dy[4] = { 0, 1, 0, -1 };

void bfs(int y, int x) {

	for (int i = 0; i < 4; i++) { // 상하좌우를 돌면서 범위 체크
		int nextX = x + dx[i];
		int nextY = y + dy[i];

		if (nextX >= m || nextY >= n || nextX < 0 || nextY < 0) continue;

		// 범위를 벗어나지 않고 값이 0일경우
		// 해당 좌표값을 1로 바꾸고 다음 처리해야 할 1 개수 증가 후 좌표값을 queue에 삽입
		else if (tomato[nextY][nextX] == 0) { 
			tomato[nextY][nextX] = 1;
			nextOnes++;
			points.push({ nextY, nextX });
		}
	}
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> m >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> tomato[i][j];
			if (tomato[i][j] == 1) points.push({ i, j });
		}
	}

	bfsOnes = points.size(); // 첫 처리해야 할 1의 개수를 초기화
	days = nextOnes = 0; 
	while (!points.empty()) { // queue가 빌 때까지 
		pair<int, int> cor = points.front(); // 좌표값을 받아와서
		bfs(cor.first, cor.second); // 해당 좌표에 대해서 bfs수행
		bfsOnes--; // 처리한 1의 개수를 하나 줄이고
		if (bfsOnes == 0) { // 1을 다 처리했으면
			//cout << nextOnes << endl;
			bfsOnes = nextOnes; // 다음 처리해야 할 1 개수를 초기화 해주고
			nextOnes = 0; 
			days++; // 하루를 늘려줌
		}
		points.pop();
	}
	days--;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (tomato[i][j] == 0) days = -1; // 만약 행렬에 0이 하나라도 있으면 값을 -1로 출력
		}
	}
	cout << days << endl;
	return 0;
}
