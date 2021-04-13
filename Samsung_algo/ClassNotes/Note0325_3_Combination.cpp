#include <iostream>

using namespace std;

int arr[] = { 1, 2, 3, 4, 5 };
int t[5] = { 0, };

void printArray(int *a, int n) {
	printf("{ ");
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("} \n");
}

// nCr = (n-1)C(r-1) + (n-1)C(r)
void nCr(int n, int r, int q) {
	if (r == 0) {
		printArray(t, q);
	}
	else if (n < r) {
		return;
	}
	else {
		t[r - 1] = arr[n - 1];
		nCr(n - 1, r - 1, q);
		nCr(n - 1, r, q);
	}

}

// nHr = (n)H(r-1) + (n-1)H(r)
void nHr(int n, int r, int q) {
	if (r == 0) {
		printArray(t, q);
	}
	else if (n < 1) { // �ϳ��� �־ ��� ���� �� �ִ� ��� ����
		return;
	}
	else {
		t[r - 1] = arr[n - 1];
		nHr(n, r - 1, q);
		nHr(n - 1, r, q);
	}

}

int main() {

	printf("���� \n");
	nCr(4, 3, 3);

	printf("\n�ߺ����� \n");
	nHr(4, 3, 3);


	return 0;
}