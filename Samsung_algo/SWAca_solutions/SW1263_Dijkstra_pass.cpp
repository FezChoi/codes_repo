#include <stdio.h>

const int INF_I = 9999;
const int MAX_USER = 1000;

int Net[MAX_USER + 1][MAX_USER + 1] = { 0, };

int extract_min(int D[], bool visited[], int N) {
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

int Dijkstra(int N) {
	bool visited[MAX_USER + 1] = { false, };
	int D[MAX_USER + 1] = { 0, };
	int CC_min = INF_I;

	for (int src = 1; src < N; src++) {
		int selected = 0;

		visited[src] = true;
		selected++;
		for (int v = 1; v <= N; v++) {
			if (Net[src][v] == 0)
				D[v] = INF_I;
			else
				D[v] = Net[src][v];
		}
		D[src] = 0;

		while (selected < N) {
			int w = extract_min(D, visited, N);
			visited[w] = true;
			selected++;

			for (int v = 1; v <= N; v++) {
				if (Net[w][v] && D[v] > D[w] + Net[w][v])
					D[v] = D[w] + Net[w][v];
			}
		}

		bool isMin = true;
		for (int i = 1; i <= N; i++) {
			D[0] += D[i];

			if (D[0] > CC_min) {
				isMin = false;
				break;
			}
		}

		if (isMin) CC_min = D[0];

		for (int i = 0; i <= N; i++) {
			visited[i] = false;
			D[i] = 0;
		}
	}

	return CC_min;
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

		int answer = Dijkstra(N);

		printf("#%d %d \n", tc, answer);

		for (int i = 1; i <= N; i++) Net[i][0] = 0;
	}

	return 0;
}