#include <iostream>

using namespace std;

// 부분집합의 핵심 개념 : 각 원소가 포함되는 경우(1)와 포함되지 않는 경우(0)의 조합

void printArray(int *a, int n) {
	printf("{ ");
	for (int i = 0; i < n; i++) {
		if (a[i] == 1)
			printf("%d ", i + 1);
	}
	printf("} \n");
}

void powerset_loop() {
	int bit[3] = { 0, };

	for (int i = 0; i <= 1; i++) {
		bit[0] = i;
		for (int j = 0; j <= 1; j++) {
			bit[1] = j;
			for (int k = 0; k <= 1; k++) {
				bit[2] = k;
				printArray(bit, 3);
			}
		}
	}

}

// int는 32bit, 즉 원소의 개수가 31개까지 가능.
// 비트연산자는 우선순위가 낮기 때문에 괄호를 붙여 컴파일러에게 의도를 노출해야 함.
void powerset_bit(unsigned int n) {
	for (unsigned int i = 0; i < (1 << n); i++) {	 // (1 << n) : 2^n
		printf("{ ");
		for (unsigned int j = 0; j < n; j++) {
			if (i & (1 << j)) {					// (i & (1 << j)) : i의 j번째 bit가 1인지 검사
				printf("%d ", j + 1);
			}
		}
		printf("} \n");
	}
}

int main() {

	printf("부분집합(반복) \n");
	powerset_loop();

	printf("\n부분집합(bit) \n");
	powerset_bit(3);


	return 0;
}