#include <iostream>

using namespace std;

const int TREE_SIZE = 50;

int tree[TREE_SIZE] = { 0, };
int V;
int E;

int findNode(int node) {
	for (int i = 1; i < TREE_SIZE; i++) {
		if (tree[i] == node)
			return i;
	}
	return -1;
}

void preOrder(int node) {
	if (node < 1 || node >= TREE_SIZE) return;
	if (tree[node] == 0) return;

	cout << tree[node] << " ";		// V
	preOrder(node << 1);				// L
	preOrder(node << 1 | 1);			// R
}

void inOrder(int node) {
	if (node < 1 || node >= TREE_SIZE) return;
	if (tree[node] == 0) return;

	inOrder(node << 1);					// L
	cout << tree[node] << " ";		// V
	inOrder(node << 1 | 1);			// R
}

void postOrder(int node) {
	if (node < 1 || node >= TREE_SIZE) return;
	if (tree[node] == 0) return;

	postOrder(node << 1);				// L
	postOrder(node << 1 | 1);			// R
	cout << tree[node] << " ";		// V
}

void levelOrder(int node) {
	int pow2[] = { 1, 2, 4, 8, 16, 32, 64 };
	int nextLevel = 1;

	for (int i = 1; i < TREE_SIZE; i++) {
		if (i == pow2[nextLevel]) {
			cout << endl;
			nextLevel++;
		}
		if (tree[i]) {
			cout << tree[i] << " ";
		}
	}
	cout << endl;
}

int main() {
	freopen("input.txt", "r", stdin);

	cin >> V >> E;

	for (int i = 0; i < E; i++) {
		int parent, child;
		cin >> parent >> child;

		int pIdx = findNode(parent);
		if (pIdx < 1) {
			pIdx = 1;
			tree[pIdx] = parent;
		}

		if (tree[2 * pIdx] == 0)
			tree[2 * pIdx] = child;
		else
			tree[2 * pIdx + 1] = child;
	}

	cout << "전위순회 : ";
	preOrder(1);
	cout << endl << endl;

	cout << "중위순회 : ";
	inOrder(1);
	cout << endl << endl;

	cout << "후위순회 : ";
	postOrder(1);
	cout << endl << endl;

	cout << "Level순회 : \n";
	levelOrder(1);
	cout << endl << endl;

	return 0;
}