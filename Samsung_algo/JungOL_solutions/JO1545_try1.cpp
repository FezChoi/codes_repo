#include <iostream>

using namespace std;

const int INFI = 987654321;
const int MAX_SIZE = 20;

int graph[MAX_SIZE][MAX_SIZE] = { 0, };
int parent[MAX_SIZE] = { 0, };
int key[MAX_SIZE] = { 0, };

int q[MAX_SIZE] = { 0, };
int front = 0;
int rear = 0;

void print_visit(unsigned int visit) {
	for (int i = 19; i >= 0; i--) {
		cout << ((visit >> i) & 1) << " ";
	}
	cout << endl;
}

int extract_min(int u, int N) {
	int min_distance = INFI;
	int min_index = 0;

	for (int i = front + 1; i <= rear; i++) {
		if (min_distance > graph[u][q[i]]) {
			min_distance = graph[u][q[i]];
			min_index = i;
		}
	}
	cout << "extract : " << q[min_index];
	cout << " (min distance : " << min_distance << ")" << endl << endl;
	

	parent[q[min_index]] = u;
	q[min_index] = q[++front];

	return min_index;
}

void print_q(int q_end) {
	cout << endl << "queue : ";
	for (int i = front + 1; i <= q_end; i++)
		cout << q[i] << " ";
	cout << endl;
}

void MST_Prim(int src, int N) {
	for (int u = 1; u <= N; u++) {
		key[u] = INFI;
		parent[u] = 0;
		q[++rear] = u;
	}

	key[src] = 0;
	parent[src] = 0;
	q[src] = q[++front];

	int u = src;
	while (front != rear) {
		print_q(rear);
		u = extract_min(u, N);

		for (int i = front + 1; i <= rear; i++) {
			int v = q[i];

			if (graph[u][v] == 0) continue;

			if (key[v] > graph[u][v]) {
				key[v] = graph[u][v];
				parent[v] = u;
			}
		}
	}

	cout << "parent array : " << endl;
	for (int i = 1; i <= N; i++) {
		cout << i << " ";
	}
	cout << endl;
	for (int i = 1; i <= N; i++) {
		cout << parent[i] << " ";
	}
	cout << endl;

}

void DFS(int now, int N, unsigned int visit) {
	if (now == N) {
		q[++rear] = N;
		print_q(rear);
		return;
	}

	visit |= (1 << now);
	q[++rear] = now;
	print_q(rear);

	for (int next = 1; next <= N; next++) {
		if (visit & (1 << next)) continue;

		if (parent[next] == now) DFS(next, N, visit);
	}
}

int find_Path(int src, int N) {
	unsigned int visit = ~((1 << N + 1) - 1) + 1;

	front = rear = 0;

	DFS(1, N, visit);
	q[++rear] = src;
	print_q(rear);

	int dist = 0;
	for (int i = front + 1; i < rear; i++) {
		dist += graph[q[i]][q[i + 1]];
		cout << graph[q[i]][q[i + 1]] << " ";
	}
	cout << endl;

	return dist;
}


int main() {
	freopen("sample.txt", "r", stdin);

	int N;
	cin >> N;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> graph[i][j];
			printf("%2d ", graph[i][j]);
		}
		cout << endl;
	}
	cout << endl;

	MST_Prim(1, N);
	int answer = find_Path(1, N);

	cout << answer << endl;

	return 0;
}