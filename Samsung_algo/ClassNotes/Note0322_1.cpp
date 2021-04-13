#include <iostream>

using namespace std;

void bit_print(char byte) {
	for (int i = 7; i >= 0; i--) {
		if (byte & (1 << i))
			printf("1 ");
		else
			printf("0 ");
	}
}

// ºÎºÐÁýÇÕ
void powerset_bit(int n) {
	for (int i = 0; i < (1 << n); i++) {
		printf("{ ");
		for (int j = 0; j < n; j++) {
			if (i & (1 << j))
				printf("%d ", j + 1);
		}
		printf(" } \n");
	}
}


int main() {
	//
	printf("------ bit print ------\n");
	for (int i = -3; i < 3; i++) {
		printf("%2d = ", i);
		bit_print((char)i);
		printf("\n");
	}

	//
	printf("\n------ Â¦¼ö È¦¼ö ------\n");
	int n = 2127;

	printf("%d \n", n);
	printf("%s \n", (n % 2) ? "È¦¼ö" : "Â¦¼ö");
	printf("%s \n", (n & 1) ? "È¦¼ö" : "Â¦¼ö");

	//
	printf("\n------ xor ------");
	int a = 23;
	int b = 17;

	printf("\n %3d : ", a);
	bit_print((char)a);

	printf("\n %3d : ", b);
	bit_print((char)b);

	a ^= b; // xor È¦¼ö¹ø
	printf("\n %3d : ", a);
	bit_print((char)a);

	a ^= b; // xor Â¦¼ö¹ø
	printf("\n %3d : ", a);
	bit_print((char)a);

	//
	printf("\n\n------ ºÎºÐÁýÇÕ ------\n");
	powerset_bit(3);


	return 0;
}