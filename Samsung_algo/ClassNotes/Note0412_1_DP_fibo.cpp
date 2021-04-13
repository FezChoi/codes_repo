#include <iostream>

using namespace std;


long long fibo(int n) {
	long long tbl[51] = { 0, 1 };

	for (int i = 2; i <= n; i++) {
		tbl[i] = tbl[i - 1] + tbl[i - 2];
	}

	return tbl[n];
}

// Sliding Window
// 시간을 줄이는 것이 아닌, 메모리를 줄이는 방법
long long fibo_slide(int n) {
	const int WIN_SZ = 3;
	long long tbl[WIN_SZ] = { 0, 1 };

	for (int i = 2; i <= n; i++) {
		tbl[i % WIN_SZ] = tbl[(i - 1) % WIN_SZ] + tbl[(i - 2) % WIN_SZ];
	}

	return tbl[n % WIN_SZ];
}


int main() {

	int n = 50;

	cout << fibo_slide(n) << endl;

	return 0;
}