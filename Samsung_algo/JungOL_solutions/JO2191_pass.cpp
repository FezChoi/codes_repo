#include <stdio.h>

const int MAX_LEN = 1000;

int dist[MAX_LEN + 1][MAX_LEN + 1] = { 0, };

inline int get_min(int a, int b, int c) {
	int t = (a < b) ? a : b;
	return (t < c) ? t : c;
}

int EditDistance(char source[], int s_len, char target[], int t_len) {
	for (int j = 1; j <= s_len; j++) dist[0][j] = j;
	for (int i = 1; i <= t_len; i++) dist[i][0] = i;

	for (int i = 1; i <= t_len; i++) {
		for (int j = 1; j <= s_len; j++) {
			if (source[j - 1] == target[i - 1])
				dist[i][j] = dist[i - 1][j - 1];
			else
				dist[i][j] = get_min(dist[i - 1][j], dist[i][j - 1], dist[i - 1][j - 1]) + 1;
		}
	}

	return dist[t_len][s_len];
}


int main() {
	int a_len, b_len;
	char a[MAX_LEN + 1] = { 0, };
	char b[MAX_LEN + 1] = { 0, };

	scanf("%d %s", &a_len, a);
	scanf("%d %s", &b_len, b);

	int answer = EditDistance(a, a_len, b, b_len);

	printf("%d \n", answer);

	return 0;
}