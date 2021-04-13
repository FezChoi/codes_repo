#include <stdio.h>
#include <stdlib.h>

const int prime[5] = { 17, 31, 53, 79, 97 };
const int bucket_size = 100;

char bucket[bucket_size][52] = { 0, };
int counter = 0;


void copy_string(char* dst, char* src) {
	while (*src != NULL) { *dst++ = *src++; }
}

bool compare_string(char* s1, char* s2) {
	while (*s1 != NULL && *s2 != NULL) {
		if (*s1 != *s2) 
			return false;

		s1++;
		s2++;
	}

	if (*s1 != NULL || *s2 != NULL) 
		return false;
	else
		return true;
}


int sum_string(char* str) {
	int sum = 0;
	int base = 37;

	while (*str != NULL) {
		sum += *str++ * base;
		sum %= bucket_size;
	}

	return sum;
}

void hash_function(char* str, int hash) { //stack overflow
	int level = 0;
	while (level++ <= bucket_size) {
		if (bucket[hash][0] == 0) {
			bucket[hash][0] = level;
			copy_string(bucket[hash] + 1, str);
			return;
		}

		if (bucket[hash][0] == level) {
			if (compare_string(bucket[hash] + 1, str)) {
				counter++;
				printf("%d : %s \n", counter, str);
				return;
			}
		}

		int mod = prime[level % 5];
		hash += hash % mod;
		hash %= bucket_size;
	}
}

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

			hash_function(str, sum_string(str));
		}

		for (int i = 0; i < M; i++) {
			char str[51] = { 0, };
			scanf("%s", str);

			hash_function(str, sum_string(str));
		}

		printf("#%d %d \n", tc, counter);

		for (int i = 0; i < bucket_size; i++)
			bucket[i][0] = 0;
		counter = 0;
	}
	return 0;
}