#include <iostream>

using namespace std;

const int VERTEX = 101;
const int INFI = 999999;
const int x_dir[] = { 0, 1,  0, -1 };
const int y_dir[] = { 1, 0, -1,  0 };
const int q_size = VERTEX * VERTEX;

int graph[VERTEX][VERTEX] = { 0, };
int dist[VERTEX][VERTEX] = { 0, };

void algo(int src, int dst) {
	bool visited[VERTEX][VERTEX] = { false, };

	int q_x[q_size] = { 0, };
	int q_y[q_size] = { 0, };
	int front = -1;
	int rear = -1;

	dist[src][src] = 0;

	++rear % q_size;
	q_x[rear] = src;
	q_y[rear] = src;

	while (front != rear) {
		++front % q_size;
		int x_cur = q_x[front];
		int y_cur = q_y[front];

		visited[x_cur][y_cur] = true;

		for (int i = 0; i < 4; i++) {
			int x_new = x_cur + x_dir[i];
			int y_new = y_cur + y_dir[i];

			if (x_new < src || x_new > dst || y_new < src || y_new > dst) continue;
			//if (graph[x_new][y_new] == INFI) continue;
			if (visited[x_new][y_new] == true) continue;

			if (dist[x_new][y_new] > dist[x_cur][y_cur] + graph[x_new][y_new]) {
				dist[x_new][y_new] = dist[x_cur][y_cur] + graph[x_new][y_new];
				if (x_new == dst && y_new == dst)
					return;
				else {
					++rear % q_size;
					q_x[rear] = x_new;
					q_y[rear] = y_new;
				}	
			}
		}
	}
}


int main() {
	freopen("input.txt", "r", stdin);

	int T;
	cin >> T;

	for (int tc = 1; tc <= 10; tc++) {
		int N;
		cin >> N;

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				char c;
				cin >> c;

				graph[i][j] = c - '0';
				dist[i][j] = INFI;
			}
		}

		algo(1, N);

		//for (int i = 1; i <= N; i++) {
		//	for (int j = 1; j <= N; j++) {
		//		cout << dist[i][j];
		//	}
		//	cout << endl;
		//}

		cout << "#" << tc << " " << dist[N][N] << endl;

		for (int i = 1; i <= N + 1; i++) {
			int* ptr = (int*)graph[i];
			while (*ptr == NULL) *ptr++ = 0;
		}
	}

	return 0;
}