#include <cstdio>
#include <algorithm>

using namespace std;

int N;
int arr[1000001];

int main(void) {

	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
	}

	sort(arr, arr + N);

	for (int i = 0; i < N; i++) {
		printf("%d\n", arr[i]);
	}

	
	return 0;
}
