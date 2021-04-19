#include <stdio.h>
#include <stdlib.h>
#define SWAP(a, b) { int tmp = a; a = b; b = tmp; }

const int MAX_N = 1000;
int NUM_N = 0;
int MAX_WEIGHT = 0;

int weight[MAX_N] = { 0, };

bool isPossible = true;
bool isEnded = false;

void sort_weight(int i, int j) {
	if (i >= j) return;

	int left = i;
	int right = j;
	int pivot = weight[left + (right - left) / 2];
	
	while (left <= right) {
		while (weight[left]  < pivot) left++;
		while (weight[right] > pivot) right--;
		if (left <= right) {
			SWAP(weight[left], weight[right]);
			left++; right--;
		}
	}

	sort_weight(i, right);
	sort_weight(left, j);
}

void DFS(int obj, int w, int level) {
	if (isEnded) return;

	if (level == NUM_N) {
		printf("%d ", w);

		if (w == obj) {
			isPossible = true;
			isEnded = true;
		}

		return;
	}
	
	if (w == obj) {
		isPossible = true;
		isEnded = true;
		return;
	}

	DFS(obj, w, level + 1);
	DFS(obj, w + weight[level], level + 1);
}


int solution() {
	//sort_weight(0, NUM_N - 1);

	//for (int i = 0; i < NUM_N; i++)
	//	printf("%d ", weight[i]);
	//printf("\n");

	int object = 0;

	while (++object <= MAX_WEIGHT) {
		printf("%d : ", object);

		isPossible = false;
		isEnded = false;
		DFS(object, 0, 0);

		printf("%s \n", isPossible ? "poss" : "not poss");

		if (!isPossible) break;
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

	system("pause");

	return 0;
}