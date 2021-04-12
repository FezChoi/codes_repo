#include <stdio.h>

int main() {
	char str[100] = { 0, };
	char str2[100] = { 0, };

	scanf("%[^\n]", str);

	char* ptr = str;
	char* ptr2 = str2;
	while (*ptr != 0) {
		char c = *ptr++;

		if (c == ' ') continue;
		if (c >= 'A' && c <= 'Z')
			*ptr2++ = c - ('A' - 'a');
		else
			*ptr2++ = c;
	}

	printf("%s \n", str2);

	return 0;
}