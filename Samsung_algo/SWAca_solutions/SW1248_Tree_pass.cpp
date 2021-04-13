#include <stdio.h>

int tree[10001][2] = { 0, };
int tree_size = 0;
int subtree_size = 0;
int answer = 0;
int node1 = 0;
int node2 = 0;

bool postOrder(int node) {
	if (node < 1 || node > tree_size) return false;

	bool first = postOrder(tree[node][0]);
	bool sec  = postOrder(tree[node][1]);

	if (node == node1) return true;
	else if (node == node2) return true;

	if (first && sec) {
		answer = node;
		first = false;
		sec = false;
	}

	return (first || sec);
}

void preOrder(int node) {
	if (node < 1 || node > tree_size) return;

	subtree_size++;
	preOrder(tree[node][0]);
	preOrder(tree[node][1]);
}

int main() {
	freopen("input.txt", "r", stdin);

	int T;
	scanf("%d", &T);

	for (int test_case = 1; test_case <= T; test_case++) {
		int V, E;
		scanf("%d %d %d %d", &V, &E, &node1, &node2);
		tree_size = V;

		for (int i = 0; i < E; i++) {
			int parent, child;
			scanf("%d %d", &parent, &child);

			if (tree[parent][0] == 0)
				tree[parent][0] = child;
			else
				tree[parent][1] = child;
		}

		postOrder(1);
		preOrder(answer);

		printf("#%d %d %d\n", test_case, answer, subtree_size);
		
		int* ptr = (int*)tree;
		int size = 10001 * 2 - 1;
		while (size-- > 0) *ptr++ = 0;
		answer = 0;
		node1 = 0;
		node2 = 0;
		tree_size = 0;
		subtree_size = 0;
	}

	return 0;
}