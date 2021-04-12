#include <stdio.h>
#define MAX_int 2147000000

int main() {
	int N;
	scanf("%d", &N);

	int min = MAX_int, max = -1;
	for (int i = 1; i < N; i++) {
		int age;
		scanf("%d", &age);

		if (age < min) min = age;
		if (age > max) max = age;
	}

	printf("%d \n", max - min);

	return 0;
}