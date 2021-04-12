#include <stdio.h>
#include <algorithm>

using namespace std;

int arr[5] = { 3, 5, 8 };
int t[5] = { 0, };

void printArray(int *a, int n) {
	printf("{ ");
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("} \n");
}

// nPn
void perm_loop() {
	for (int i = 1; i < 4; i++) {
		for (int j = 1; j < 4; j++) {
			if (j == i) continue;

			for (int k = 1; k < 4; k++) {
				if (k == j || k == i) continue;

				printf("{ %d %d %d } \n", i, j, k);
			}
		}
	}
}

// nPn
void perm_recursive(int k, int n) {
	if (k == n)
		printArray(arr, 3);
	else {
		for (int i = k; i < n; i++) {
			swap(arr[i], arr[k]);
			perm_recursive(k + 1, n);
			swap(arr[i], arr[k]);
		}
	}
}

// nPr = n * (n-1)P(r-1)
void nPr(int n, int r, int q) {
	if (r == 0)
		printArray(t, q);
	else {
		for (int i = n - 1; i >= 0; i--) {
			swap(arr[i], arr[n - 1]);
			t[r - 1] = arr[n - 1];				// n
			nPr(n - 1, r - 1, q);				// (n-1)P(r-1)
			swap(arr[i], arr[n - 1]);
		}
	}

}

// nPIr = n * (n)PI(r-1)
void nPIr(int n, int r, int q) {
	if (r == 0)
		printArray(t, q);
	else {
		for (int i = n - 1; i >= 0; i--) {
			swap(arr[i], arr[n - 1]);
			t[r - 1] = arr[n - 1];				// n
			nPIr(n, r - 1, q);						// (n)P(r-1)
			swap(arr[i], arr[n - 1]);
		}
	}

}

int main() {

	printf("순열(반복) \n");
	perm_loop();

	printf("\n순열(재귀) \n");
	perm_recursive(0, 3);

	printf("\n순열(점화식) \n");
	nPr(3, 3, 3);

	printf("\n중복순열(점화식) \n");
	nPIr(3, 3, 3);

	return 0;
}