#include <stdio.h>

#define MAX_N 1000
#define MAX_W 10000	// jungol에서 const로 하면 에러!

typedef struct  {
	int weight;
	int price;
}Jewel;

Jewel jewel[MAX_N + 1] = { 0, };
int maxPi[MAX_N + 1][MAX_W + 1] = { 0, }; // dp table

int N, W;

int get_max(int a, int b) {
	return (a > b) ? a : b;
}

int main() {
	freopen("input.txt", "r", stdin);

	scanf("%d %d", &N, &W);

	for (int i = 1; i <= N; i++) {
		scanf("%d %d", &jewel[i].weight, &jewel[i].price);
	}

	// dp table 초기화
	for (int i = 0; i <= N; i++) {
		maxPi[i][0] = 0;
		maxPi[0][i] = 0;
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= W; j++) {
			if (jewel[i].weight > j)
				maxPi[i][j] = maxPi[i - 1][j];
			else
				maxPi[i][j] = get_max(maxPi[i - 1][j], maxPi[i][j - jewel[i].weight] + jewel[i].price);
				// 보석을 여러개 넣을 수 있기 때문에 
		}
	}

	for (int i = 0; i <= W; i++)
		printf("%d \n", maxPi[N][i]);

	return 0;
}