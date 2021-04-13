#include <iostream>

using namespace std;

int fibo(int n) {
	static int memo[100] = { 0, 1, };  // 전역변수이면서 fibo 함수에서만 접근가능.

	if (n >= 2 && memo[n] == 0)
		return memo[n] = fibo(n - 1) + fibo(n - 2);

	return memo[n];
}

int main() {
	int n = 50;
	
	for (int i = 1; i <= n; i++) {
		cout << i << " : " << fibo(i) << endl;
	}

	return 0;
}