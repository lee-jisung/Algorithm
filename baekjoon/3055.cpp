#include <iostream>
#include <queue>
#include <vector>

#define MAX 51

using namespace std;

struct point {
	int y;
	int x;
};

int r, c;
point st, dst;
int map[MAX][MAX];
bool isVisit[MAX][MAX];

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

vector<point> water;

bool isRange(int y, int x) {
	if (y < 0 || x < 0 || y >= r || x >= c)
		return false;
	return true;
}

// 물이 들어가 있는 위치마다 
// queue에 담아서 bfs로 사방으로 퍼뜨리는 함수
void spread_water() { 
	queue<point> wt;
	int wsize;
	for (int i = 0; i < water.size(); i++)
		wt.push(water[i]);
	water.clear();
	wsize = wt.size();
	for (int i = 0; i < wsize; i++) {
		point w = wt.front();
		wt.pop();
		for (int a = 0; a < 4; a++) {
			int nextX = w.x + dx[a];
			int nextY = w.y + dy[a];
			if (isRange(nextY, nextX)) {
				if (map[nextY][nextX] == 0 || map[nextY][nextX] == 2) {
					map[nextY][nextX] = 1;
					water.push_back({ nextY, nextX });
				}
			}
		}
	}
}

void bfs() {

	queue<pair<point, int> >q;
	q.push(make_pair(st, 0));
	isVisit[st.y][st.x] = true;
	while (!q.empty()) {
		int end = q.size();
		spread_water();
		// q에 고슴도치가 4방향으로 이동하면서 4의 배수씩 쌓이게 되므로
		// 모든 방향을 전부다 이동시켜서 q에넣고 돌리고 나서 물을 퍼뜨려야 하는거기 때문에
		// q 사이즈만큼 for문을 돌려서 q를 비우게 하고 물을 퍼뜨리는거야
		// 이문제 처럼 bfs를 동시에 두개 퍼뜨릴 때는
		// 하나를 다 퍼뜨리고 나머지 하나도 퍼뜨릴 때 q크기만큼 다 돌면서 쌓인걸 다 해줘야하는 듯
		for (int i = 0; i < end; i++) { 
			point s = q.front().first;
			int dis = q.front().second;
			if (s.y == dst.y && s.x == dst.x) {
				cout << dis << "\n";
				return;
			}
			q.pop();
			for (int a = 0; a < 4; a++) {
				int nextX = s.x + dx[a];
				int nextY = s.y + dy[a];
				if (isRange(nextY, nextX) && !isVisit[nextY][nextX]) {
					if (map[nextY][nextX] == 0 || map[nextY][nextX] == 3) {
						isVisit[nextY][nextX] = true;
						point temp = { nextY, nextX };
						q.push(make_pair(temp, dis + 1));
					}
				}
			}
		}
	}
	cout << "KAKTUS\n";
}

int main(void) {

	cin >> r >> c;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			char temp;
			cin >> temp;
			if (temp == 'D') {
				map[i][j] = 3;
				dst.y = i; dst.x = j;
			}
			if (temp == '*') {
				map[i][j] = 1;
				water.push_back({ i, j });
			}
			if (temp == 'S') {
				map[i][j] = 2;
				st.y = i; st.x = j;
			}
			if (temp == 'X') map[i][j] = 4;
		}
	}

    bfs();


	return 0;
}
