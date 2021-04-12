#include <iostream>

using namespace std;

const int VERTEX = 100;
const int INFI = 999999;
const int dir_x[] = { 0, 1,  0, -1 };
const int dir_y[] = { 1, 0, -1,  0 };

int graph[VERTEX + 2][VERTEX + 2] = { 0, };
int cost_min = INFI;

void DFS(int x, int y, int dst, int cost_total) {
	//cout << "( " << x << ", " << y << " ) : " << cost_total << endl;
	if (x == dst && y == dst) {
		//cout << "cost total : " << cost_total << endl << endl;
		if (cost_total < cost_min)
			cost_min = cost_total;
		return;
	}

	int cost_new = graph[x][y];

	for (int i = 0; i < 4; i++) {
		int x_new = x + dir_x[i];
		int y_new = y + dir_y[i];

		if (graph[x_new][y_new] == INFI) continue;
		if (cost_total + graph[x_new][y_new] > cost_min) continue;

		graph[x][y] = INFI; //visited
		DFS(x_new, y_new, dst, cost_total + cost_new);
		graph[x][y] = cost_new;
	}
}

int main() {
	freopen("input.txt", "r", stdin);

	for (int i = 0; i <= 101; i++) {
		graph[0][i] = INFI;
		graph[i][0] = INFI;
	}

	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		int N;
		cin >> N;

		for (int i = 0; i <= 101; i++) {
			graph[N + 1][i] = INFI;
			graph[i][N + 1] = INFI;
		}

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				char c;
				cin >> c;

				graph[i][j] = c - '0';
			}
		}

		DFS(1, 1, N, 0);

		cout << "#" << tc << " " << cost_min << endl;

		cost_min = INFI;
		for (int i = 1; i <= N + 1; i++) {
			int* ptr = (int*)graph[i];
			while (*ptr == NULL) *ptr++ = 0;
		}
	}

	return 0;
}