#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

int N;
int M;
queue<int> q;
vector<int> degree;
vector<vector<int> > graph;

int main(void) {

	scanf("%d %d", &N, &M);

	degree.resize(N + 1);
	graph.resize(N + 1);

	while (M--) {
		int u, v;
		scanf("%d %d", &u, &v);
		graph[u].push_back(v);
		degree[v]++;
	}

	for (int i = 1; i <= N; i++) {
		if (degree[i] == 0)
			q.push(i);
	}

	while (!q.empty()) {
		int now = q.front();
		q.pop();
		printf("%d ", now);

		int length = graph[now].size();
		for (int i = 0; i < length; i++) {
			int next = graph[now][i];
			degree[next]--;
			if (degree[next] == 0)
				q.push(next);
		}
	}
	return 0;
}
