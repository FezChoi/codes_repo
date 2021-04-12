#include <stdio.h>

enum { ROAD = '0', WALL, START, END, VISIT };
int dir[4][2] = { {0, +1}, {+1, 0}, {0, -1}, {-1, 0} }; // ©Л го аб ╩С

const int GRAPH_SIZE = 100;
char graph[GRAPH_SIZE][GRAPH_SIZE + 1] = { 0, };

bool isEnded = false;
int result = 0;

void Solve(int x, int y);

int main() {
	for (int test_case = 0; test_case < 10; test_case++) {
		int tc;
		scanf("%d", &tc);

		int x = 0, y = 0;
		int x2 = 0, y2 = 0;
		for (int i = 0; i < GRAPH_SIZE; i++) {
			scanf("%s", graph[i]);

			for (int j = 1; j < GRAPH_SIZE; j++) {
				if (graph[i][j] == START) {
					x = i; y = j;
				}
			}
		}

		Solve(x, y);

		printf("#%d %d \n", tc, result);

		char* tmp = (char*)graph;
		while (*tmp != NULL) *tmp++ = 0;
		isEnded = false;
		result = 0;
	}

	return 0;
}

void Solve(int x, int y) {
	if (isEnded) return;

	graph[x][y] = VISIT;

	for (int i = 0; i < 4; i++) {
		int x_new = x + dir[i][0];
		int y_new = y + dir[i][1];

		if (graph[x_new][y_new] == END) {
			isEnded = true;
			result = 1;
			return;
		}
		else if (graph[x_new][y_new] == ROAD)
			Solve(x_new, y_new);
	}
}