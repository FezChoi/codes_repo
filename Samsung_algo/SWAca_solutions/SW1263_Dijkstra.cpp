#include <stdio.h>

const int INF_I = 9999;
const int MAX_USER = 1000;

int Net[MAX_USER + 1][MAX_USER + 1] = { 0, };



inline int get_min(int a, int b) {
	return (a < b) ? a : b;
}

inline int extract_min(int D[], bool visited[], int N) {
	int D_min = INF_I;
	int D_idx = 0;

	for (int i = 1; i <= N; i++) {
		if (!visited[i] && D_min > D[i]) {
			D_min = D[i];
			D_idx = i;
		}
	}

	return D_idx;
}

int Dijkstra(int src, int N) {
	bool visited[MAX_USER + 1] = { false, };
	int D[MAX_USER + 1] = { 0, };
	int selected = 0;
		
	visited[src] = true;
	selected++;
	for (int v = 1; v <= N; v++) {
		if (v == src)
			D[v] = 0;
		else if (Net[src][v] == 0)
			D[v] = INF_I;
		else 
			D[v] = Net[src][v];
	}

	while (selected < N) {
		int w = extract_min(D, visited, N);
		visited[w] = true;
		selected++;

		for (int v = 1; v <= N; v++) {
			if (Net[w][v])
				D[v] = get_min(D[v], D[w] + Net[w][v]);
		}
	}

	for (int i = 1; i <= N; i++)
		D[0] += D[i];

	return D[0];
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

		int CC_min = INF_I;
		for (int i = 1; i <= N; i++) {
			int CC_i = Dijkstra(i, N);

			if (CC_min > CC_i)
				CC_min = CC_i;
		}

		printf("#%d %d \n", tc, CC_min);

		for (int i = 1; i <= N; i++) Net[i][0] = 0;
	}

	return 0;
}