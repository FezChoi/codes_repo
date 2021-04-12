#include <iostream>

using namespace std;

struct Node {
	int data;
	Node *left;
	Node *right;
};

Node *root = nullptr;

Node *makeNode(int value) {
	Node *newNode = new Node;
	if (newNode != nullptr) {
		newNode->data = value;
		newNode->left = nullptr;
		newNode->right = nullptr;
	}
	return newNode;
}

Node *searchBST(Node *node, int key) {
	if (node == nullptr) 
		return nullptr;

	if (node->data == key)
		return node;
	else if (node->data > key)
		return searchBST(node->left, key);
	else
		return searchBST(node->right, key);

	return node;	// 걸리지 않았을 때, 마지막으로 찾은 위치
}

Node *insertBST(Node *node, int value) {
	// 삽입하고자 하는 노드 탐색하고, 탐색 실패 위치에 추가
	if (node == nullptr)
		return makeNode(value);

	if (node->data > value)
		node->left = insertBST(node->left, value);
	else if (node->data < value)
		node->right = insertBST(node->right, value);
	else
		cout << "Duplicate Key !! \n";		// 중복되는 경우 (중복 허용 x)

	return node;	// 주의!! 
}

Node *findMostBiggestNode(Node *node) {
	while (node->right != nullptr)
		node = node->right;

	return node;
}

Node *deleteBST(Node *node, int value) {
	if (node == nullptr) return nullptr;

	if (node->data > value)
		node->left = deleteBST(node->left, value);
	else if (node->data < value)
		node->right = deleteBST(node->right, value);
	else {
		// 삭제 대상 노드를 찾은 경우
		if (node->left != nullptr && node->right != nullptr) {
			// degree = 2
			Node *replaceNode = findMostBiggestNode(node->left);
			node->data = replaceNode->data;
			node->left = deleteBST(node->left, replaceNode->data);
		}
		else {
			// degree = 0 or 1
			Node *delNode = node;

			node = node->left;
			if (node == nullptr)
				node = delNode->right;

			delete delNode;
		}
	}

	return node;
}

void printTree(Node *node, int level, int depth) {
	if (node == nullptr) return;
	if (level < depth) return;

	if (level == depth) {
		printf("%d ", node->data);
	}

	printTree(node->left, level, depth + 1);
	printTree(node->right, level, depth + 1);
}

void printBST(Node *node) {
	const int depth = 5;

	for (int i = 0; i < depth; i++) {
		printTree(node, i, 0);
		cout << endl;
	}
	cout << endl;
}


int main() {

	root = insertBST(root, 9);
	root = insertBST(root, 4);
	root = insertBST(root, 12);
	root = insertBST(root, 15);
	root = insertBST(root, 6);
	root = insertBST(root, 3);
	root = insertBST(root, 13);

	Node *node = searchBST(root, 6);
	if (node != nullptr)
		cout << "0x" << node << " = " << node->data << endl;
	else
		cout << "Not found!!" << endl;

	printBST(root);

	root = insertBST(root, 17);
	root = insertBST(root, 5);

	printBST(root);

	root = deleteBST(root, 13);
	printBST(root);

	root = deleteBST(root, 12);
	printBST(root);	

	root = deleteBST(root, 9);
	printBST(root);


	return 0;
}