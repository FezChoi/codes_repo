#include <stdio.h>

const int INF_I = 987654321;
const int MAX_USER = 1000;

int Net[MAX_USER + 1][MAX_USER + 1] = { 0, };

int get_min(int a, int b) {
	return (a < b) ? a : b;
}

int Floyd(int N) {
	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			if (i == k) continue;

			for (int j = 1; j <= N; j++) {
				if (j == k || j == i) continue;

				Net[i][j] = get_min(Net[i][k] + Net[k][j], Net[i][j]);
			}
		}
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			Net[i][0] += Net[i][j];
		}
	}

	//for (int i = 1; i <= N; i++) {
	//	for (int j = 0; j <= N; j++) {
	//		printf("%d ", Net[i][j]);
	//	}
	//	printf("\n");
	//}

	int min_CC = INF_I;
	for (int i = 1; i <= N; i++) {
		if (min_CC > Net[i][0])
			min_CC = Net[i][0];
	}
	
	return min_CC;
}


int main() {
	freopen("sample.txt", "r", stdin);

	int T;
	scanf("%d", &T);

	for (int tc = 1; tc <= T; tc++) {
		int N;
		scanf("%d", &N);

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				scanf("%d", &Net[i][j]);
				
				if (Net[i][j] == 0 && i != j)
					Net[i][j] = INF_I;
			}
		}

		int answer = Floyd(N);
		printf("#%d %d \n", tc, answer);

		for (int i = 1; i <= N; i++) Net[i][0] = 0;
	} 

	return 0;
}