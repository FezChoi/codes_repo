#include <iostream>
#define SWAP(a, b) { a = a ^ b; b = a ^ b; a = a ^ b; }

using namespace std;

int arr[100] = { 0, };

int main() {
	ios::sync_with_stdio(false);

	int N;
	cin >> N;

	int neg_idx = 0;
	int pos_idx = N - 1;
	for (int i = 0; i < N; i++) {
		int number;
		cin >> number;

		if (number < 0)
			arr[neg_idx++] = number;	// front : negative part
		else
			arr[pos_idx--] = number;		// rear : positive part
	}

	// sort negative part (0, neg_idx]
	for (int i = 0; i < neg_idx; i++) {
		for (int j = i + 1; j < neg_idx; j++) {
			if (arr[i] < arr[j])
				SWAP(arr[i], arr[j]);
		}
	}

	// sort positive part (neg_idx, N]
	for (int i = neg_idx; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			if (arr[i] > arr[j])
				SWAP(arr[i], arr[j]);
		}
	}

	// print
	for (int i = 0; i < N; i++)
		cout << arr[i] << " ";

	return 0;
}