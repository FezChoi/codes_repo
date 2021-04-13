#include <stdio.h>

const int MAX_NUMBER = 200;

int number[MAX_NUMBER + 1] = { 0, };


int binary_search(int arr[], int size, int num) {
	int low = 0;
	int high = size;

	while (low <= high) {
		int mid = low + (high - low) / 2;
		if (arr[mid] < num)
			low = mid + 1;
		else
			high = mid - 1;
	}
	
	return low;
}

int LIS_algo(int N) {
	int c[MAX_NUMBER + 1] = { 0, };
	int c_size = 0;

	for (int i = 0; i < N; i++) {
		int lower_bound = binary_search(c, c_size, number[i]);

		c[lower_bound] = number[i];
		c_size = (lower_bound > c_size) ? lower_bound : c_size;
	}

	return c_size;
}


int main() {
	freopen("sample.txt", "r", stdin);

	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; i++) 
		scanf("%d", &number[i]);

	int answer = N - LIS_algo(N);

	printf("%d \n", answer);

	return 0;
}