#include <iostream>

using namespace std;

int arr[50001] = { 0, };

int main() {
	int N;
	cin >> N;

	for (int i = 1; i <= N; i++) {
		arr[i]++;

		for (int j = 2; i * j <= N; j++)
			arr[i * j]++;

		cout << arr[i] << " ";
	}

	return 0;
}