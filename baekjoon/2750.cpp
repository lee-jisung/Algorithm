#include <cstdio>

using namespace std;

int N;

void sorting(int*arr, int number) {
	for (int i = 0; i < number; i++) {
		for (int j = i; j < number; j++) {
			if (arr[i] > arr[j]) {
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

int main(void) {

	scanf("%d", &N);
	int * arr = new int[N];

	for (int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
	}

	sorting(arr, N);
	for (int i = 0; i < N; i++) {
		printf("%d\n", arr[i]);
	}


}
