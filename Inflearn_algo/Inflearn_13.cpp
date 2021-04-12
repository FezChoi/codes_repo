#include <iostream>

using namespace std;

int main() {
	int num_count[10] = { 0, };

	char str[101] = { 0, };
	cin >> str;

	char* ptr = str;
	while (*ptr != NULL) {
		if (*ptr != '0')
			num_count[*ptr - '0']++;

		ptr++;
	}

	int max_count = 0;
	int max_number = 0;
	for (int i = 9; i >= 1; i--) {
		if (num_count[i] > max_count) {
			max_count = num_count[i];
			max_number = i;
		}
	}

	cout << max_number << endl;

	return 0;
}