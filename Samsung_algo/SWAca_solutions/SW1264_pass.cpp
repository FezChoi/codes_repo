#include <stdio.h>
#define get_max(a, b) ( ((a) > (b)) ? (a) : (b) )

const int MAX_LEN = 500;
char source[MAX_LEN + 1] = { ' ', };
char target[MAX_LEN + 1] = { ' ', };
int LCS[MAX_LEN + 1][MAX_LEN + 1] = { 0, };

void init(int N) {
	char* ptr1 = source;
	char* ptr2 = target;
	for (int i = 1; i <= N; i++) {
		*++ptr1 = 0; 
		*++ptr2 = 0;
		for (int j = 1; j <= N; j++)
			LCS[i][j] = 0;
	}
}

int LCS_algo(int N) {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (source[i] == target[j])
				LCS[i][j] = LCS[i - 1][j - 1] + 1;
			else
				LCS[i][j] = get_max(LCS[i - 1][j], LCS[i][j - 1]);
		}
	}

	return LCS[N][N];
}

int main() {
	freopen("sample.txt", "r", stdin);

	int T;
	scanf("%d", &T);

	for (int tc = 1; tc <= T; tc++) {
		int N;
		scanf("%d", &N);
		scanf("%s %s", source + 1, target + 1);

		float answer = (float)LCS_algo(N) / N * 100;
		
		printf("#%d %.2f \n", tc, answer);

		init(N);
	}
	   
	return 0;
}