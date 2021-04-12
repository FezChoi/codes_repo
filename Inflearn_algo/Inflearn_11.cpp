#include <iostream>

using namespace std;

int main() {
	int N;
	cin >> N;

	int cnt = 0;
	for (int i = 1; i <= N; i++) {
		int num = i;
		do {
			cnt++;
			num /= 10;
		} while (num != 0);
	}

	cout << cnt;

	return 0;
}