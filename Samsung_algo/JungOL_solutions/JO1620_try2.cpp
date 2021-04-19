#include <iostream>

using namespace std;

char num_str[101] = { 0, };
int num_plus, num_pos;

void print_error() {
	printf("INPUT ERROR! \n");
}

void print_answer(int end, int len) {
	for (int idx = end - len; idx < end; idx++) {
		int number = (num_str[idx] - '0' + num_plus) % 10;
		printf("%c", number + '0');
	}
	printf("\n");
}

void solution() {
	bool isError = true;
	int num_idx = 0;
	int num_len = 0;

	int pos = 1;
	int len = 0;
	int i = 0;
	while (num_str[i] != NULL) {
		printf("%c", num_str[i]);

		if (num_str[i] == '-') {
			if (pos == num_pos) {
				num_idx = i;
				num_len = len;
				isError = false;
			}
			
			pos++;
			len = 0;
		}
		else {
			if (++len > 4) {
				isError = true;
				break;
			}
		}

		i++;
	}
	printf("\n");

	if (isError)
		print_error();
	else
		print_answer(num_idx, num_len);
}


int main() {
	freopen("sample.txt", "r", stdin);

	cin >> num_str >> num_plus >> num_pos;

	solution();

	system("pause");
	return 0;
}