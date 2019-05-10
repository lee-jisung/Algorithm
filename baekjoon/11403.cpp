#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int adj[101][101];
int edge[101][101];
int n;

void floyd() {

	for (int k = 1; k <= n; k++) { // k = 거쳐가는 노드
		for (int i = 1; i <= n; i++) { // i = 출발 노드
			for (int j = 1; j <= n; j++) { // j = 도착 노드 
				if (edge[i][k] && edge[k][j])
					edge[i][j] = 1;
			}
		}
	}
}

int main(void){

	cin >> n;

	for (int i =1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> edge[i][j];
		}
	}

	// 각 정점을 시작 점으로 보고
	// 연결된 점들을 방문하면서 연결된 점을 기준으로 모든 점을 보고
	// 또 다른 점이 연결되어 있으면 시작점에서 그 점으로 갈 수 있기 때문에 
	// 시작점에서 해당 점으로에 대한 adj를 1로 setting
	/*for (int st = 1; st <= n; st++) {
		int isVisited[101] = { 0, }; 
		queue<int> Q;
		Q.push(st);
		while (!Q.empty()) {
			int cur = Q.front();
			Q.pop();
			for (int i = 1; i <= n; i++) {
				if (edge[cur][i] && !isVisited[i]) { 
					Q.push(i);
					adj[st][i] = 1;
					isVisited[i] = true;
				}	
			}
		}
	}*/

	/*for (int i = 1; i <=n; i++) {
		for (int j = 1; j <=n; j++) {
			cout << adj[i][j] << " ";
		}
		cout << endl;
	}*/

	//플로이드-와샬
	floyd();
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << edge[i][j] << " ";
		}
		cout << endl;
	}

	return 0;

}
