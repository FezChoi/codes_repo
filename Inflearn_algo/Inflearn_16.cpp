#include <iostream>

using namespace std;

// A = 65, z = 122 -> 0 ~ 57 : 64 bit
unsigned long long mask1 = 0;
unsigned long long mask2 = 0;
unsigned long long one = 1;

int main() {
	char str1[101] = { 0, };
	char str2[101] = { 0, };

	cin >> str1;

	cout << "first" << endl;

	char* ptr = str1;
	while (*ptr != 0) {
		int shifter = *ptr++ - 'A';
		mask1 |= (one << shifter);
	}

	cin >> str2;
	ptr = str2;
	while (*ptr != 0) {
		int shifter = *ptr++ - 'A';
		mask2 |= (one << shifter);
	}

	if (mask1 == mask2)
		cout << "YES" << endl;
	else
		cout << "NO" << endl;

	return 0;
}