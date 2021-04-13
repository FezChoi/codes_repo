#include <iostream>

using namespace std;

enum OP { PLUS = -5, MINUS, MUL, DIV };
enum TREE { V, L, R };

int tree[1001][3] = { 0, };
int TREE_SIZE = 0;

void checkStr(int node, char str[]);
int calculation(int op, int left, int right);
int postOrder(int node);

int main() {
	ios::sync_with_stdio(false);

	for (int tc = 1; tc <= 10; tc++) {
		int N;
		cin >> N;
		TREE_SIZE = N;

		for (int i = 0; i < N; i++) {
			int node;
			char str[10] = { 0, };
			cin >> node >> str;

			checkStr(node, str);
		}

		int result = postOrder(1);
		cout << "#" << tc << " " << result << endl;

		for (int i = 1; i <= TREE_SIZE; i++) {
			tree[i][V] = 0;
			tree[i][L] = 0;
			tree[i][R] = 0;
		}
	}

	return 0;
}

void checkStr(int node, char str[]) {
	int op = -1;
	int num = 0;

	switch (str[0]) {
	case'+': op = PLUS;     break;
	case'-': op = MINUS;    break;
	case'*': op = MUL;      break;
	case'/': op = DIV;      break;
	default:
		for (int i = 0; str[i] != NULL; i++) {
			num *= 10;
			num += str[i] - '0';
		}
		tree[node][V] = num;
		return;
	}

	tree[node][V] = op;
	cin >> tree[node][L] >> tree[node][R];
}

int calculation(int op, int left, int right) {
	switch (op) {
	case PLUS : return left + right;
	case MINUS: return left - right;
	case MUL  : return left * right;
	case DIV  : return (right != 0) ? left / right : 0;
	default   : return 0;
	}
}

int postOrder(int node) {
	if (node < 1 || node > TREE_SIZE) return 0;
	if (tree[node][V] >= 0) return tree[node][V];

	int op = tree[node][V];
	int L_val = postOrder(tree[node][L]);
	int R_val = postOrder(tree[node][R]);

	return calculation(op, L_val, R_val);
}