#include <iostream>

using namespace std;

int main() {
	ios::sync_with_stdio(false);

	int N;
	cin >> N;

	int sum = 0;
	for (int i = 1; i < N; i++) {
		if (N % i == 0) {
			sum += i;
			cout << i << " ";

			if (i == N / 2) 
				cout << "= ";
			else 
				cout << "+ ";
		}
	}

	cout << sum << endl;

	return 0;
}