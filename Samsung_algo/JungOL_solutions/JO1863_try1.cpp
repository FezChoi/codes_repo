#include <iostream>

using namespace std;

const int MAX_SIZE = 50000;

int parent[MAX_SIZE] = { 0, };
int p_rank[MAX_SIZE] = { 0, };
int count_set = 0;


void Make_set(int v1, int v2) {
	parent[v1] = v1;
	parent[v2] = v1;
	p_rank[v1] = 1;

	count_set++;
}

int Find_set(int v) {
	int v_init = v;
	int count_rank = 0;

	while (v != parent[v]) { 
		v = parent[v]; 
		count_rank++;
	}

	parent[v_init] = v;
	p_rank[v] = (count_rank > p_rank[v]) ? count_rank : p_rank[v];

	return v;
}

void Union_set(int p, int v) {
	parent[v] = p;
	p_rank[p]++;
}

void Compare(int v1, int v2) {
	int p1 = Find_set(v1);
	int p2 = Find_set(v2);
	
	cout << v1 << " " << v2 << " -> ";
	cout << p1 << " " << p2 << endl;

	if (p1 == 0 && p2 == 0) {
		cout << "Make_set" << endl;
		Make_set(v1, v2);
		return;
	}

	if (p1 == p2) return;

	cout << "Union_set" << endl;
	if (p_rank[p1] >= p_rank[p2])
		Union_set(p1, v2);
	else
		Union_set(p2, v1);
}

int main() {
	freopen("sample.txt", "r", stdin);

	int N, M;
	cin >> N >> M;

	for (int k = 0; k < M; k++) {
		int i, j;
		cin >> i >> j;

		Compare(i, j);
	}

	cout << count_set << endl;

	return 0;
}