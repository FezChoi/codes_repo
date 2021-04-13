#include <iostream>

using namespace std;

const int VERTEX = 10;
const int INFINITI = 999;		// 987654321

int A[VERTEX][VERTEX] = { 0, }; // 인접행렬
int D[VERTEX] = { 0, };			// 거리 갱신
bool U[VERTEX] = { false, };	// 선택정점 집합
int V;							// 정점의 총 개수

int extractMin() {
	int minVertex = 0;
	int minDistance = INFINITI;

	for (int i = 1; i <= V; i++) {
		// 선택되지 않았고, 거리가 더 작으면
		if (U[i] == false && D[i] < minDistance) { 
			minVertex = i;
			minDistance = D[i];
		}
	}

	return minVertex;
}

// O(V^2)
int dijkstra_basic(int s) {
	U[s] = true;

	for (int v = 1; v <= V; v++) {
		D[v] = A[s][v];
	}
	// D[s] = 0; 출발지점의 거리는 0

	for (int i = 1; i < V; i++) {
		int w = extractMin();
		U[w] = true;

		for (int v = 1; v <= V; v++) {
			// w와 v가 연결되어 있고, s에서 가는 것보다 w 경우하는게 더 짧으면
			if (A[w][v] != INFINITI && D[v] > D[w] + A[w][v])
				D[v] = D[w] + A[w][v];
		}
	}

	return D[V];
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

	int distance = dijkstra_basic(1);

	printDistance();

	cout << "최단거리 : " << distance << endl;

	return 0;
}
