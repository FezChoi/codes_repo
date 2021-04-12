#include <iostream>

using namespace std;

// ������� 1 : top-down, return �������� ���
int recurl(int n) {
	if (n == 1) 
		return 1;
	else
		return n + recurl(n - 1);
}

// ������� 2 : bottom-up, return �������� ���
int recurl2(int k, int n) {
	if (k == n)
		return n;
	else
		return k + recurl2(k + 1, n);
}

// ������� 3 : { ���� 1 | ���� 2 ) + ȣ�� ������ ���
int recurl3(int n, int sum) {
	if (n == 1)
		return sum + n;
	else
		return recurl3(n - 1, sum + n);
}

/* 
	<���ǻ���>
	1. �ݵ�� ���� ���ǿ� �����ؾ� �Ѵ�.
	2. �������� ����� �ּ�ȭ �ؾ��Ѵ�.
	3. �Ű������� ������ �ݵ�� ȣ�� ������ �����Ѵ�.
		- �������� ���������� ���, ���ϴ� ���� �� ���� ���ɼ��� ����.
		- Staging�� �̿�Ǵ� ������ �ַ� �Ű������� ���. ??
*/

int main() {
	int n = 10;

	cout << "1 : sum of " << n << " = " << recurl(n) << endl;
	cout << "2 : sum of " << n << " = " << recurl2(1, n) << endl;
	cout << "3 : sum of " << n << " = " << recurl3(n, 0) << endl;

	return 0;
}