#include <stdio.h>

const int prime[5] = { 17, 31, 53, 79, 97 };
const int bucket_size = 100;

char bucket[bucket_size][52] = { 0, };
int counter = 0;

int sumStr(char* str);
bool compareStr(char* str1, char* str2);
void pushStr(char* src, char* dst);
void hash(char* str, int level, int hashValue);

int main() {
	freopen("input.txt", "r", stdin);

	int T;
	scanf("%d", &T);

	for (int tc = 1; tc <= T; tc++) {
		int N, M;
		scanf("%d %d", &N, &M);

		for (int i = 0; i < N; i++) {
			char str[51] = { 0, };
			scanf("%s", str);

			hash(str, 1, sumStr(str));
		}

		for (int i = 0; i < M; i++) {
			char str[51] = { 0, };
			scanf("%s", str);

			hash(str, 1, sumStr(str));
		}

		printf("#%d %d \n", tc, counter);

		counter = 0;
		for (int i = 0; i < bucket_size; i++)
			bucket[i][0] = 0;
	}


	return 0;
}

int sumStr(char* str) {
	int str_sum = 0;
	int base = 37;

	while (*str != NULL) {
		str_sum += *str++ * base;
		str_sum %= bucket_size;
	}

	return str_sum;
}

bool compareStr(char* str1, char* str2) {
	while (*str1 != NULL && *str2 != NULL) {
		if (*str1 != *str2)
			return false;

		str1++;
		str2++;
	}

	if (*str1 != NULL || *str2 != NULL)
		return false;
	else
		return true;
}

void pushStr(char* src, char* dst) {
	while (*src != NULL) {
		*dst++ = *src++;
	}
}

void hash(char* str, int level, int hashValue) {
	if (bucket[hashValue][0] == 0) {
		bucket[hashValue][0]++;
		pushStr(str, bucket[hashValue] + 1);
		return;
	}

	if (bucket[hashValue][0] == level) {
		if (compareStr(str, bucket[hashValue] + 1)) {
			printf("%s \n", str);
			counter++;
			return;
		}
	}

	int mod = prime[level % 5];
	hashValue += hashValue % mod;
	hashValue %= bucket_size;
	hash(str, level + 1, hashValue);
}
