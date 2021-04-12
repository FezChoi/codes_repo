#include <stdio.h>

int tree[10001][100] = { 0, };
int tree_size = 0;
int node1 = 0;
int node2 = 0;
int answer = 0;

int postOrder(int node) {
	if (node < 1 || node > tree_size) return 0;

	int checkSum = 0;
	for (int i = 1; i <= tree[node][0]; i++) {
		checkSum += postOrder(tree[node][i]);
	}

	if (node == node1) return 1;
	else if (node == node2) return 1;

	if (checkSum == 2) {
		answer = node;
		return 1;
	}

	return checkSum;
}


int main() {
	freopen("input.txt", "r", stdin);

	int N;
	scanf("%d", &N);
	tree_size = N;

	for (int i = 0; i < N - 1; i++) {
		int parent, child;
		scanf("%d %d", &parent, &child);

		int cnt = ++tree[parent][0];
		tree[parent][cnt] = child;
	}
	scanf("%d %d", &node1, &node2);

	int root = 1;
	while (answer == 0) {
		postOrder(root++);
	}

	printf("%d \n", answer);

	return 0;
}