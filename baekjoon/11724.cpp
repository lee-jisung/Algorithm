#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> edge[1001];
int isVisited[1001] = { 0, };
int n, m, CCcount = 0;
// 연결 요소 - 간선이 연결되어 있는 점들의 집합 개수

int main(void) {

	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	
	// 각 점마다 방문을 했었는지 확인하면서
	// 연결 된 모든 지점을 방문하여 방문 표시한 후 연결 요소 값 증가
	for (int st = 1; st <= n; st++) {
		if (!isVisited[st]) {
			queue<int> Q;
			Q.push(st);
			isVisited[st] = true;
			while (!Q.empty()) {
				int st = Q.front();
				Q.pop();
				for (int i = 0; i < edge[st].size(); i++) {
					int y = edge[st][i];
					if (!isVisited[y]) {
						Q.push(y);
						isVisited[y] = true;
					}
				}
			}
			CCcount++;
		}
	}

	cout << CCcount;

	return 0;
}
