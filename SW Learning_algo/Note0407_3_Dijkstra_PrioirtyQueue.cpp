#include <iostream>

#define swap(a, b) { int tmp; tmp = a; a = b; b = tmp; }

using namespace std;

const int VERTEX = 10;
const int INFINITI = 999;		// 987654321

int A[VERTEX][VERTEX] = { 0, }; // 인접행렬
int D[VERTEX] = { 0, };			// 거리 갱신
bool U[VERTEX] = { false, };	// 선택정점 집합
int V;							// 정점의 총 개수


/* Heap */
const int HEAP_SIZE = 50;
int heap[HEAP_SIZE] = { 0, };
int heapCount = 0;

void push(int value) {
	heap[++heapCount] = value;

	int child = heapCount;
	int parent = child >> 1;

	// Up Heap
	while (parent > 0 && D[heap[parent]] > D[heap[child]]) {
		swap(heap[parent], heap[child]);

		child = parent;
		parent = child >> 1;
	}
}

int pop() {
	int parent = 1;
	int ret = heap[parent];

	heap[parent] = heap[heapCount];
	heap[heapCount--] = 0;

	int child = parent << 1;	   // left child
	if (child + 1 <= heapCount) {  // if right child exists
		child = (D[heap[child]] < D[heap[child + 1]]) ? child : child + 1;
	}

	// Down Heap
	while (child <= heapCount && D[heap[parent]] > D[heap[child]]) {
		swap(heap[parent], heap[child]);

		parent = child;
		child = parent << 1;

		if (child + 1 <= heapCount) {  // if right child exists
			child = (D[heap[child]] < D[heap[child + 1]]) ? child : child + 1;
		}
	}

	return ret;
}

void printHeap() {
	int pow2[] = { 1, 2, 4, 8, 16, 32, 64 };
	int nextLevel = 1;

	for (int i = 1; i < HEAP_SIZE; i++) {
		if (i == pow2[nextLevel]) {
			cout << endl;
			nextLevel++;
		}
		if (heap[i]) {
			cout << heap[i] << " ";
		}
	}
	cout << endl;
}


/* Dijkstra (Priority Queue) */
int dijkstra_pq(int s) {
	/*U[s] = true;

	for (int v = 1; v <= V; v++) {
		D[v] = A[s][v];
	}*/
	D[s] = 0; 
	push(s);

	while (heapCount > 0) {		// !pq.empty()
		int w = pop();

		if (U[w] == false) {
			U[w] = true;

			for (int v = 1; v <= V; v++) {
				// w와 v가 연결되어 있고, s에서 가는 것보다 w 경우하는게 더 짧으면
				if (A[w][v] != INFINITI && D[v] > D[w] + A[w][v]) {
					D[v] = D[w] + A[w][v];
					push(v);
				}
			}
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

		D[i] = INFINITI;
		U[i] = false;
	}

	int distance = dijkstra_pq(1);

	printDistance();

	cout << "최단거리 : " << distance << endl;

	return 0;
}