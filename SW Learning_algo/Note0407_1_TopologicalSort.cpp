#include <iostream>

using namespace std;;

int G[10][10] = { 0, };

int main() {
	freopen("input.txt", "r", stdin);

	int V, E;
	cin >> V >> E;

	for (int i = 1; i <= E; i++) {
		int src, dst;
		cin >> src >> dst;

		G[src][dst] = 1;
		G[0][dst]++;
	}

	int v = V;
	while (v) {
		for (int i = 1; i <= V; i++) {
			if (G[0][i] == 0) {
				printf("%c ", 'A' + i - 1);
				v--;
				G[0][i]--;;

				for (int j = 1; j <= V; j++) {
					if (i == j) continue;
					if (G[i][j] == 1)
						G[0][j]--;

				}
			}
		}
	}

	cout << endl;

	return 0;
}