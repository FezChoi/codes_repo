#include <iostream>

using namespace std;

void printArray(int  arr[], int n) {
	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

// O(n^2), 빠르고 간단
void bubbleSortSimple(int *a, int n) {
	for (int i = 0; i < n - 2; i++) {
		for (int j = 0; j < n - 1; j++) {
			if (a[j] > a[j + 1])
				swap(a[j], a[j + 1]);
		}
	}
}

// O(n^2)
void bubbleSort(int *a, int n) {
	for (int i = n - 2; i > 0; i--) {
		for (int j = 0; j <= i; j++) {
			if (a[j] > a[j + 1])
				swap(a[j], a[j + 1]);
		}
	}
}

// O(n^2)
void selectionSort(int *a, int n) {
	for (int i = 0; i < n; i++) {
		int minIdx = i;
		for (int j = i + 1; j < n; j++) {
			if (a[j] < a[minIdx])
				minIdx = j;
		}
		swap(a[i], a[minIdx]);
	}
}

// O(kn), 이중목적.
void selectionAlgorithm(int *a, int n, int k) {
	for (int i = 0; i < k; i++) {
		int minIdx = i;
		for (int j = i + 1; j < n; j++) {
			if (a[j] < a[minIdx])
				minIdx = j;
		}
		swap(a[i], a[minIdx]);
	}
}

// O(n + k), 빠름 but 데이터가 정수거나 정수화 가능한 경우만 적용가능.
void countingSort(int *a, int n) {
	// 가장 큰 값 k 구하기
	int k = 0;
	for (int i = 0; i < n; i++) {
		if (k < a[i]) {
			k = a[i];
		}
	}

	int *cnt = new int[k + 1]{ 0, };

	// 빈도 수 카운트
	for (int i = 0; i < n; i++) {
		cnt[a[i]]++;
	}

	// 정렬 결과를 복사
	int j = 0;
	for (int i = 0; i <= k; i++) {
		while (cnt[i] > 0) {
			a[j++] = i;
			cnt[i]--;
		}
	}

	// 메모리 회수
	delete[] cnt;
}

void insertionSort(int *a, int n) {

	for (int i = 1; i < n; i++) {			// U
		int tmp = a[i];

		int j = i - 1;			// S
		while (j >= 0 && a[j] >= tmp) {
			a[j + 1] = a[j];
			j--;
		}

		a[j + 1] = tmp;
	}
}

int main() {
	int arr[] = { 1, 5, 8, 9, 3, 4, 2, 7, 6, 10 };
	int n = sizeof(arr) / sizeof(arr[0]);


	printArray(arr, n);

	//bubbleSortSimple(arr, n);
	//bubbleSort(arr, n);
	//selectionSort(arr, n);
	//selectionAlgorithm(arr, n, 3);
	//countingSort(arr, n);
	insertionSort(arr, n);

	printArray(arr, n);

	return 0;
}

