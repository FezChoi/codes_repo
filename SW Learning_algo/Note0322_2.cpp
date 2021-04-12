#include <iostream>
#include <cmath>

using namespace std;

// O(n - 2)
bool isPrime1(int n) {
	if (n == 1) return false;

	for (int i = 2; i < n; i++) {
		if (n % i == 0) return false;
	}

	return true;
}

// O(sqrt(n - 2))
bool isPrime2(int n) {
	if (n == 1) return false;

	for (int i = 2; i < sqrt(n); i++) {
		if (n % i == 0) return false;
	}

	return true;
}

// sqrt 대체
bool isPrime2_1(int n) {
	if (n == 1) return false;

	for (int i = 2; i * i < n; i++) {
		if (n % i == 0) return false;
	}

	return true;
}

// 짝수 거르기
bool isPrime3(int n) {
	if (n == 1) return false;
	if (n == 2) return true;
	if (n % 2 == 0) return false;

	for (int i = 3; i * i < n; i += 2) {
		if (n % i == 0) return false;
	}

	return true;
}

int main() {
	int n = 7127;

	printf("%d = %s \n", n, (isPrime1(n) ? "Prime" : "Composite"));
	printf("%d = %s \n", n, (isPrime2(n) ? "Prime" : "Composite"));
	printf("%d = %s \n", n, (isPrime2_1(n) ? "Prime" : "Composite"));
	printf("%d = %s \n", n, (isPrime3(n) ? "Prime" : "Composite"));

	return 0;
}