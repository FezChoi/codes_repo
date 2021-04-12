#include <iostream>

using namespace std;

int main() {
	int N;
	cin >> N;

	int cnt = 0;
	for (int i = 2; i <= N; i++) {
		bool isPrime = true;

		for (int j = 2; j < i; j++) {
			if (i % j == 0) {
				isPrime = false;
				break;
			}
		}

		if (isPrime) cnt++;
	}

	cout << cnt << endl;

	return 0;
}