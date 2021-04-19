#include <stdio.h>

const int MAX_N = 1000;
int NUM_N = 0;
int MAX_WEIGHT = 0;

int weight[MAX_N] = { 0, };
bool visit[MAX_N] = { false, };
bool isPossible = true;
bool isEnded = false;

void swap_weight(int idx1, int idx2) {
	int tmp = weight[idx1];
	weight[idx1] = weight[idx2];
	weight[idx2] = tmp;
}

void sort_weight() {
	for (int i = 1; i < NUM_N; i++) {
		for (int j = i + 1; j <= NUM_N; j++) {
			if (weight[i] > weight[j])
				swap_weight(i, j);
		}
	}
}

void init_DFS() {
	for (int i = 0; i < NUM_N; i++) {
		visit[i] = false;
	}
}

void DFS(int obj, int w, int level) {
	if (isEnded) return;

	if (level == NUM_N) {
		if (w != obj) isPossible = false;
		return;
	}

	if (w == obj) {
		isPossible = true;
		isEnded = true;
		return;
	}

	for (int i = 0; i < NUM_N; i++) {
		if (visit[i]) continue;

		visit[i] = true;
		DFS(obj, w + weight[i], level + 1);
		visit[i] = false;
		DFS(obj, w, level + 1);
	}
}


int solution() {
	sort_weight();

	int object = 0;

	while (++object <= MAX_WEIGHT) {
		isEnded = false;
		DFS(object, 0, 0);

		if (isPossible) 
			init_DFS();
		else 
			break;
	}
	
	return object;
}

int main() {
	freopen("sample.txt", "r", stdin);

	int N;
	scanf("%d", &N);

	NUM_N = N;
	for (int i = 0; i < N; i++) {
		scanf("%d", &weight[i]);
		MAX_WEIGHT += weight[i];
	}

	int answer = solution();

	printf("%d \n", answer);

	return 0;
}