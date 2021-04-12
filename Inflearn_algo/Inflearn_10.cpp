#include <iostream>

using namespace std;

int digit_sum(int x) {
	int sum = 0;

	while (x != 0) {
		sum += x % 10;
		x /= 10;
	}

	return sum;
}

int main() {
	int N;
	cin >> N;

	int max_sum = 0;
	int max_num = 0;
	for (int i = 0; i < N; i++) {
		int x;
		cin >> x;
		
		int sum = digit_sum(x);
		if (sum > max_sum) {
			max_sum = sum;
			max_num = x;
		}
		else if (sum == max_sum) {
			if (x > max_num)
				max_num = x;
		}
	}

	cout << max_num;

	return 0;
}