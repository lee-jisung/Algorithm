#include <cstdio>

using namespace std;

int N;

int main(void) {

	int arr[3];
	int index, min, temp;

	for (int i = 0; i < 3; i++) {
		scanf("%d", &arr[i]);
	}

	for (int i = 0; i < 3; i++) {
		min = 10000001;
		for (int j = i; j < 3; j++) {
			if (min > arr[j]) {
				min = arr[j];
				index = j;
			}
		}
		temp = arr[index];
		arr[index] = arr[i];
		arr[i] = temp;
	}

	for (int i = 0; i < 3; i++) {
		printf("%d ", arr[i]);
	}
	return 0;
}
