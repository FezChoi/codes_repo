#include <iostream>
#include <cstdlib>

using namespace std;

char str[101] = { 0, };
int num_plus, num_pos;

void print_error() {
	printf("INPUT ERROR! \n");
}

void print_answer(int end, int len) {
	for (int idx = end - len; idx < end; idx++) {
		int number = (str[idx] - '0' + num_plus) % 10;
		printf("%c", number + '0');
	}
	printf("\n");
}

void solution() {
	int num_cnt = 1;
	int num_len = 0;
	int num_idx = 0;

	int i = 0;
	while (str[i] != NULL) {
		if (str[i] == '-') {
			if (num_cnt == num_pos) break;

			num_len = 0;
			num_cnt++;
		}
		else {
			if (++num_len > 4) {
				print_error();
				return;
			}
		}

		i++;
	}

	if (num_cnt != num_pos) {
		print_error();
		return;
	}

	print_answer(i, num_len);

	return;
}


int main() {
	freopen("sample.txt", "r", stdin);

	cin >> str >> num_plus >> num_pos;

	solution();

	system("pause");
	return 0;
}