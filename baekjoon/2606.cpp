#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector<int> PC[101];
int visited[101];
int warmPC = 0;

void dfs(int x) {
	if (visited[x]) return;
	visited[x] = true;
	warmPC++;
	for (int i = 0; i < PC[x].size(); i++) {
		int y = PC[x][i];
		dfs(y);
	}
}

int main(void) {

	int pc, edge;
	cin >> pc >> edge;

	for (int i = 0; i < edge; i++) {
		int pc1, pc2;
		cin >> pc1 >> pc2;
		PC[pc1].push_back(pc2);
		PC[pc2].push_back(pc1);
	}

	dfs(1);
	warmPC--; // 첫 pc가 포함되기 때문에 1을 빼줌
	cout << warmPC << endl;
}
