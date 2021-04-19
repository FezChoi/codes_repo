#include <stdio.h>

const int MAX_LEN = 101;

char num_str[MAX_LEN] = { 0, };
int num_plus, num_pos;

void print_error() {
	printf("INPUT ERROR! \n");
}

void print_answer(int start, int end) {
	int len = end - start - 1;

	while (4 - len++ > 0) {
		printf("%c", num_plus + '0');
	}

	for (int i = start + 1; i < end; i++) {
		int number = (num_str[i] - '0' + num_plus) % 10;
		printf("%c", number + '0');
	}
	printf("\n");
}

void solution() {
	if (num_pos <= 0) {
		print_error();
		return;
	}

	int hyphen[MAX_LEN] = { -1, };
	int num_cnt = 1;
	int num_len = 0;

	int i = 0;
	while (num_str[i] != NULL) {
		if (num_str[i] == '-') {
			hyphen[num_cnt++] = i;
			num_len = 0;
		}
		else {
			if (++num_len > 4) {
				print_error();
				return;
			}
		}

		i++;
	}

	if (num_cnt < num_pos) {
		print_error();
		return;
	}

	hyphen[num_cnt] = i;

	print_answer(hyphen[num_pos - 1], hyphen[num_pos]);
}


int main() {
	freopen("sample.txt", "r", stdin);

	scanf("%s %d %d", num_str, &num_plus, &num_pos);

	solution();

	return 0;
}