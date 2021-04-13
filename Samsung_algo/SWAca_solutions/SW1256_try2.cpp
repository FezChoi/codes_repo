#include <iostream>
#define SWAP(a, b) { a = a ^ b; b = a ^ b; a = a ^ b; }

using namespace std;

char S[401][401] = { 0, };
int A[401] = { 0, };

int SuffixArray(char str[]) {
	char* ptr = str;

	int idx = 1;
	while (*ptr != NULL) {
		for (int i = 0; *(ptr + i) != NULL; i++) {
			S[idx][i] = *(ptr + i);
		}
		idx++;
		ptr++;
	}

	return --idx;
}

void IndexArray(char* str, int s_count) {
	for (int i = 1; i <= s_count; i++)
		A[i] = i;

	for (int i = s_count; i > 0; i--) {
		for (int j = i - 1; j > 0; j--) {
			int idx = 0;

			while (S[A[i]][idx] == S[A[j]][idx]) {
				if (S[A[i]][idx + 1] == NULL) break;
				idx++;
			}

			if (S[A[i]][idx] <= S[A[j]][idx]) {
				SWAP(A[i], A[j]);
			}
		}
	}
}


int main() {
	freopen("input.txt", "r", stdin);

	int T;
	cin >> T;
	for (int test_case = 1; test_case <= T; test_case++) {
		int K;
		char str[401] = { 0, };
		cin >> K >> str;

		int s_count = SuffixArray(str);
		IndexArray(str, s_count);

		cout << "#" << test_case << " " << S[A[K]] << endl;
	}

	return 0;
}