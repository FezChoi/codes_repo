#include <iostream>

using namespace std;

bool arr[101] = { false, };

int main() {
	int N;
	cin >> N;

	for (int i = 0; i < N; i++) {
		int grade;
		cin >> grade;

		arr[grade] = true;
	}

	int cnt = 0;
	int idx = 101;
	while (cnt < 3) {
		if (arr[--idx] == true) cnt++;
	}

	cout << idx << endl;

	return 0;
}