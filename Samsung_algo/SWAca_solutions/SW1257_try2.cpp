#include <iostream>
#include <stdlib.h>
#define SWAP(a, b) { a = a ^ b; b = a ^ b; a = a ^ b; }

using namespace std;

char str[401][401] = { 0, };
char ans[401] = { 0, };
int A[401] = { 0, };
int LCP[401] = { 0, };

int SuffixArray(char* tmp) {
	char* ptr = tmp;

	int idx = 2;
	while (*++ptr != NULL) {
		for (int i = 0; *(ptr + i) != NULL; i++) {
			str[idx][i] = *(ptr + i);
		}
		idx++;
	}

	return --idx;
}

void IndexArray(int s_count) {
	for (int i = 1; i <= s_count; i++)
		A[i] = i;

	for (int i = s_count; i > 0; i--) {
		for (int j = i - 1; j > 0; j--) {
			int idx = 0;
			int cnt = 0;

			while (str[A[i]][idx] == str[A[j]][idx]) {
				cnt++;

				if (str[A[i]][idx + 1] == NULL) 
					break;
				idx++;
			}

			if (str[A[i]][idx] <= str[A[j]][idx]) {
				SWAP(A[i], A[j]);
				LCP[i] = cnt;
			}
		}
	}
}

void Powerset(int s_count, int K) {
	int cnt = 0;

	for (int i = 1; i <= s_count; i++) {
		char* ptr = str[A[i]];
		int len = LCP[i];

		while (*(ptr + len) != NULL) {
			if (++cnt == K) {
				for (int j = 0; j <= len; j++) {
					if (*(ptr + j) == NULL) break;
					ans[j] = *(ptr + j);
				}
				return;
			}
			len++;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);

	freopen("input.txt", "r", stdin);

	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		int K;
		cin >> K >> str[1];

		int s_count = SuffixArray(str[1]);
		IndexArray(s_count);
		Powerset(s_count, K);

		cout << "#" << tc << " ";
		if (ans[0] == NULL)
			cout << "none" << endl;
		else
			cout << ans << endl;

		for (int i = 1; i <= s_count + 1; i++) {
			char* ptr = str[i];
			while (*ptr != NULL) *ptr++ = 0;
		}
		char* ptr = ans;
		while (*ptr != NULL) *ptr++ = 0;
	}


	return 0;
}