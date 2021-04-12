#include <stdio.h>

int main() {
	char id[15] = { 0, };
	scanf("%s", id);

	int born = (id[0] - '0') * 10 + (id[1] - '0');

	char sex;
	switch (id[7]) {
	case '1':
		sex = 'M';
		born += 1900;
		break;
	case '2':
		sex = 'W';
		born += 1900;
		break;
	case '3':
		sex = 'M';
		born += 2000;
		break;
	case '4':
		sex = 'W';
		born += 2000;
		break;
	}
	
	int age = 2019 - born + 1;
	printf("%d %c", age, sex);

	return 0;
}