#include <stdio.h>

int main() {
	char str[51] = { 0, };
	scanf("%s", str);

	char* ptr = str;
	int number = 0;
	while (*ptr != 0) {
		char c = *ptr++;

		if (c >= 48 && c <= 57) {
			number *= 10;
			number += c - '0';
		}
	}

	printf("%d \n", number);

	int cnt = 2;
	for (int i = 2; i < number; i++) {
		if (number % i == 0)
			cnt++;
	}

	printf("%d \n", cnt);

	return 0;
}