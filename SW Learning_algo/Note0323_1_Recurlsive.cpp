#include <iostream>

using namespace std;

// 재귀유형 1 : top-down, return 과정에서 계산
int recurl(int n) {
	if (n == 1) 
		return 1;
	else
		return n + recurl(n - 1);
}

// 재귀유형 2 : bottom-up, return 과정에서 계산
int recurl2(int k, int n) {
	if (k == n)
		return n;
	else
		return k + recurl2(k + 1, n);
}

// 재귀유형 3 : { 유형 1 | 유형 2 ) + 호출 시점에 계산
int recurl3(int n, int sum) {
	if (n == 1)
		return sum + n;
	else
		return recurl3(n - 1, sum + n);
}

/* 
	<유의사항>
	1. 반드시 종료 조건에 수렴해야 한다.
	2. 지역변수 사용은 최소화 해야한다.
	3. 매개변수의 변경은 반드시 호출 시점에 변경한다.
		- 선택지가 여러가지인 경우, 원하는 값을 못 구할 가능성이 존재.
		- Staging에 이용되는 변수를 주로 매개변수로 사용. ??
*/

int main() {
	int n = 10;

	cout << "1 : sum of " << n << " = " << recurl(n) << endl;
	cout << "2 : sum of " << n << " = " << recurl2(1, n) << endl;
	cout << "3 : sum of " << n << " = " << recurl3(n, 0) << endl;

	return 0;
}