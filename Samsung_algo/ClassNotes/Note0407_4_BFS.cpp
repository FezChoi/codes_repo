#include <iostream>

using namespace std;

const int VERTEX = 10;
const int INFINITI = 999;				// 987654321

int A[VERTEX][VERTEX] = { 0, };	// 인접행렬
int D[VERTEX] = { 0, };					// 거리 갱신, visit array is not needed
int V;											// 정점의 총 개수

// BFS shows better performance than priority queue
int shortest_BFS(int s) {
	int q[100] = { 0, };
	int front = -1;
	int rear = -1;

	for (int v = 1; v <= V; v++) {
		D[v] =INFINITI;
	}
	D[s] = 0;

	q[++rear] = s;

	while (front != rear) {
		int w = q[++front];

		if (w == V) return D[V];

		for (int v = 1; v <= V; v++) {
			if (A[w][v] != INFINITI && D[v] > D[w] + A[w][v]) {		// update distance & enqueue
				D[v] = D[w] + A[w][v];
				q[++rear] = v;
			}
		}
	}

	// no path found
	return -1;
}

void printDistance() {
	for (int i = 0; i < V; i++) {
		printf("%3c ", 'A' + i);
	}
	printf("\n");

	for (int i = 1; i <= V; i++) {
		printf("%3d ", D[i]);
	}
	printf("\n \n");
}


int main() {
	freopen("input.txt", "r", stdin);

	cin >> V;

	for (int i = 1; i <= V; i++) {
		for (int j = 1; j <= V; j++) {
			cin >> A[i][j];

			if (i != j && A[i][j] == 0)
				A[i][j] = INFINITI;
		}
	}

	int distance = shortest_BFS(1);

	printDistance();

	cout << "최단거리 : " << distance << endl;

	return 0;
}