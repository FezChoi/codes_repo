#include <iostream>

using namespace std;

void printArray(int  arr[], int n) {
	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}


void merge(int *a, int *r, int begin, int mid, int end) {
	int i = begin;
	int j = mid + 1;
	int idx = 0;

	// 양쪽 다 남아 있는 경우
	while (i <= mid && j <= end) {
		if (a[i] < a[j])
			r[idx++] = a[i++];
		else
			r[idx++] = a[j++];
	}

	// 왼쪽만 남아 있는 경우
	while (i <= mid) {
		r[idx++] = a[i++];
	}

	// 오른만 남아 있는 경우
	while (j <= end) {
		r[idx++] = a[j++];
	}

	// a[] <-- result
	idx = 0;
	for (int i = begin; i <= end; i++) {
		a[i] = r[idx++];
	}
}

void mergeSort(int *a, int* r, int begin, int end) {
	// 원수의 수가 1개 이하면 리턴
	if (end - begin <= 0) return;

	int mid = (begin + end) >> 1;
	mergeSort(a, r, begin, mid);
	mergeSort(a, r, mid + 1, end);

	merge(a, r, begin, mid, end);
}

void mergeSortOne(int *a, int* r, int begin, int end) {
	// 원수의 수가 1개 이하면 리턴
	if (end - begin <= 0) return;

	int mid = (begin + end) >> 1;
	mergeSort(a, r, begin, mid);
	mergeSort(a, r, mid + 1, end);

	// 함수 호출 오버헤드 생략 (inline화)
	// 불필요한 계산 피하기
	if (a[mid] >= a[mid + 1]) {
		//merge(a, r, begin, mid, end);

		int i = begin;
		int j = mid + 1;
		int idx = 0;

		// 양쪽 다 남아 있는 경우
		while (i <= mid && j <= end) {
			if (a[i] < a[j])
				r[idx++] = a[i++];
			else
				r[idx++] = a[j++];
		}

		// 왼쪽만 남아 있는 경우
		while (i <= mid) {
			r[idx++] = a[i++];
		}

		// 오른만 남아 있는 경우
		while (j <= end) {
			r[idx++] = a[j++];
		}

		// a[] <-- result
		idx = 0;
		for (int i = begin; i <= end; i++) {
			a[i] = r[idx++];
		}

	}
}

int partition(int *a, int begin, int end) {
	int pivot = a[begin];
	int i = begin;
	int j = end;

	while (i <= j) {
		while (i <= end	&& a[i] <= pivot) i++;		// pivot 쪽에는 equal이 포함되어야 함.??
		while (j >= begin && pivot < a[j]) j--;			// 범위검사 먼저, 비교나 참조는 나중에.

		if (i < j)
			swap(a[i], a[j]);
	}

	swap(a[begin], a[j]);

	return j;
}

void quickSort(int *a, int begin, int end) {
	if (begin < end) {
		int pivot = partition(a, begin, end);
		
		quickSort(a, begin, pivot - 1);
		quickSort(a, pivot + 1, end);
	}
}

// inline화 -> 함수 호출에 따른 오버헤드 감소.
void quickSortOne(int *a, int begin, int end) {
	if (begin < end) {
		int pivot = a[begin];
		int i = begin;
		int j = end;

		while (i <= j) {
			while (i <= end && a[i] <= pivot) i++;		
			while (j >= begin && pivot < a[j]) j--;		

			if (i < j)
				swap(a[i], a[j]);
		}

		swap(a[begin], a[j]);
		
		quickSort(a, begin, j - 1);
		quickSort(a, j + 1, end);
	}
}

int main() {
	int arr[] = { 1, 5, 8, 9, 3, 4, 2, 7, 6, 10 };
	int n = sizeof(arr) / sizeof(arr[0]);

	printArray(arr, n);

	//int *result = new int[n + 1]{ 0 };
	//mergeSort(arr, result, 0, n - 1);
	//quickSort(a, 0, n - 1);
	quickSortOne(a, 0, n - 1);

	printArray(arr, n);

	return 0;
}