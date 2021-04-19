#include <stdio.h>

const int INFI = 9999;
const int MAX_SIZE = 501;

int graph[MAX_SIZE][MAX_SIZE] = { 0, };
int D[MAX_SIZE][MAX_SIZE] = { 0, };
int MAX_PAGE = 0;


int get_min(int a, int b) {
	return (a < b) ? a : b;
}

int floyd_algorithm() {
	for (int i = 1; i <= MAX_PAGE; i++) {
		for (int j = 1; j <= MAX_PAGE; j++) {
			if (i == j) continue;

			D[i][j] = (graph[i][j]) ? 1 : INFI;
		}
	}

	for (int k = 1; k <= MAX_PAGE; k++) {
		for (int i = 1; i <= MAX_PAGE; i++) {
			if (i == k) continue;
			for (int j = 1; j <= MAX_PAGE; j++) {
				if (j == k || j == i) continue;

				D[i][j] = get_min(D[i][k] + D[k][j], D[i][j]);
			}
		}
	}

	int total_click = 0;

	for (int i = 1; i <= MAX_PAGE; i++) {
		for (int j = 1; j <= MAX_PAGE; j++) {
			total_click += D[i][j];
		}
	}

	return total_click;
}

int main() {
	freopen("sample.txt", "r", stdin);

	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		int src, dst;
		scanf("%d %d", &src, &dst);

		graph[src][dst] = 1;
		MAX_PAGE = (src > MAX_PAGE) ? src : MAX_PAGE;
		MAX_PAGE = (dst > MAX_PAGE) ? dst : MAX_PAGE;
	}

	float answer = (float)floyd_algorithm() / (MAX_PAGE * (MAX_PAGE - 1));

	printf("%.3f \n", answer);

	return 0;
}