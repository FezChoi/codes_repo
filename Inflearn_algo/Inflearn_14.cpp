#include <iostream>

using namespace std;

int reverse(int number) {
	int num_ori = number;
	int num_new = 0;
	while (num_ori != 0) {
		num_new *= 10;
		num_new += num_ori % 10;
		num_ori /= 10;
	}

	return num_new;
}

bool isPrime(int number) {
	if (number < 2) return false;
	if (number % 2 == 0) return false;

	for (int i = 3; i < number; i += 2) {
		if (number % i == 0) return false;
	}

	return true;
}


int main() {
	int N;
	cin >> N;

	for (int i = 0; i < N; i++) {
		int number;
		cin >> number;

		number = reverse(number);
		if (isPrime(number))
			cout << number << " ";
	}

	cout << endl;

	return 0;
}