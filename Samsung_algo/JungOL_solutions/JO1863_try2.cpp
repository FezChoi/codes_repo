#include <iostream>

using namespace std;

const int MAX_SIZE = 50000;

int parent[MAX_SIZE + 1] = { 0, };
int p_rank[MAX_SIZE + 1] = { 0, };
int count_set = 0;


void Make_set(int v1, int v2) {
	parent[v1] = v1;
	parent[v2] = v1;
	p_rank[v1] = 1;
}

int Find_set(int v) {
	int p = v;

	while (p != parent[p]) { 
		p = parent[p]; 
	}

	parent[v] = p;
	p_rank[v] = 0;

	return p;
}

void Union_set(int p1, int p2, int v1, int v2) {
	if (p_rank[p1] > p_rank[p2]) {
		parent[p2] = p1;
	}
	else if (p_rank[p1] == p_rank[p2]) {
		parent[p2] = p1;
		p_rank[p1] = p_rank[p2] + 1;
	}
	else {
		parent[p1] = p2;
	}
}

void Disjoint_set(int v1, int v2) {
	int p1 = Find_set(v1);
	int p2 = Find_set(v2);

	if (p1 == 0 && p2 == 0) {
		Make_set(v1, v2);
		return;
	}

	if (p1 == p2) return;

	Union_set(p1, p2, v1, v2);
}

int main() {
	freopen("sample.txt", "r", stdin);
	ios::sync_with_stdio(false);

	int N, M;
	cin >> N >> M;

	for (int k = 0; k < M; k++) {
		int i, j;
		cin >> i >> j;

		Disjoint_set(i, j);
	}

	if (M == 0) 
		count_set = N;
	else {
		bool check[MAX_SIZE + 1] = { false, };
		for (int i = 1; i <= N; i++) {
			check[Find_set(i)] = true;
		}
		for (int i = 1; i <= N; i++) {
			if (check[i] == true) count_set++;
		}
	}

	cout << count_set << endl;

	return 0;
}