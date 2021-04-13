#include <iostream>
#define SWAP(a, b) { a = a ^ b; b = a ^ b; a = a ^ b; }

using namespace std;

char str[401][401] = { 0, };
char ans[401] = { 0, };

int A[401] = { 0, };
int LCP[401] = { 0, };

int SuffixArray(char* tmp);
void IndexArray(int s_count);
void LCPArray(int s_count);
void FindSuffix(int s_count, int K);
void ResetArray(int s_count);

int main() {
	ios::sync_with_stdio(false);

	freopen("input.txt", "r", stdin);

	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		int K;
		char tmp[401] = { 0, };
		cin >> K >> tmp;

		int s_count;
		s_count = SuffixArray(tmp);

		IndexArray(s_count);
		LCPArray(s_count);

		FindSuffix(s_count, K);

		cout << "#" << tc << " ";
		if (ans[0] == NULL)
			cout << "none" << endl;
		else
			cout << ans << endl;

		ResetArray(s_count);
	}

	return 0;
}

int SuffixArray(char* tmp) {
	char* ptr = tmp;

	int idx = 1;
	while (*ptr != NULL) {
		for (int i = 0; *(ptr + i) != NULL; i++)
			str[idx][i] = *(ptr + i);

		idx++;
		ptr++;
	}

	return idx;
}

void IndexArray(int s_count) {
	for (int i = 1; i <= s_count; i++)
		A[i] = i;

	for (int i = s_count; i > 0; i--) {
		for (int j = i - 1; j > 0; j--) {
			int idx = 0;
			int cnt = 0;

			while (str[A[i]][idx] == str[A[j]][idx]) {
				if (str[A[i]][idx + 1] == NULL)
					break;
				idx++;
			}

			if (str[A[i]][idx] <= str[A[j]][idx])
				SWAP(A[i], A[j]);
		}
	}
}

void LCPArray(int s_count) {
	for (int i = 1; i <= s_count; i++)
		LCP[i] = 0;

	for (int i = 2; i <= s_count; i++) {
		char* str1 = str[A[i - 1]];
		char* str2 = str[A[i]];

		int cnt = 0;
		while (*str1 != NULL && *str2 != NULL) {
			if (*str1 == *str2) {
				LCP[i]++;
				str1++;
				str2++;
			}
			else
				break;
		}
	}
}


void FindSuffix(int s_count, int K) {
	int cnt = 0;

	for (int i = 1; i <= s_count; i++) {
		char* ptr = str[A[i]];
		int len = LCP[i];

		while (*(ptr + len) != NULL) {
			cnt++;
			if (cnt == K) {
				for (int j = 0; j <= len; j++) {
					if (*(ptr + j) == NULL)
						break;

					ans[j] = *(ptr + j);
				}
				return;
			}
			len++;
		}
	}
}

void ResetArray(int s_count) {
	char* ptr;
	for (int i = 1; i <= s_count + 1; i++) {
		ptr = str[i];
		while (*ptr != NULL) *ptr++ = 0;
	}
	ptr = ans;
	while (*ptr != NULL) *ptr++ = 0;
}