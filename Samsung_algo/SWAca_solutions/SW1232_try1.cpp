#include <iostream>

using namespace std;

enum OP {
	PLUS = -5, MINUS, MUL, DIV
};

enum TREE {
	V, L, R
};


int tree[1001][3] = { 0, };


int checkStr(int node, char str[]) {
	int op = -1;
	int num = 0;

	switch (str[0]) {
	case '+': op = PLUS;	break;
	case '-': op = MINUS;	break;
	case '*': op = MUL;		break;
	case '/': op = DIV;		break;
	default:
		for (int i = 0; str[i] != NULL; i++) {
			num *= 10;
			num += str[i] - '0';
		}
	}

	if (op == -1)
		tree[node][V] = num;
	else {
		tree[node][V] = op;
		cin >> tree[node][L] >> tree[node][R];
	}
}

int main() {

	int N;
	cin >> N;

	for (int i = 0; i < N; i++) {
		int node;
		char str[10] = { 0, };
		cin >> node >> str;

		checkStr(node, str);
	}


	return 0;
}
