#include <iostream>

using namespace std;

const int JAMS = 1000;

int weight[JAMS + 1] = { 0, };
int profit[JAMS + 1] = { 0, };
int profit_per[JAMS + 1] = { 0, };

int max_jams = 0;
int max_weight = 0;

int pq[JAMS + 1] = { 0, };
int pq_count = 0;
int front = -1;
int rear = -1;

void init_PQ() {
	for (int i = 0; i < max_jams; i++) {
		pq[i] = 0;
	}
}

void push(int idx) {
	int i = pq_count++;

	while (i >= 0 && profit_per[idx] > profit_per[pq[i]]) {
		pq[i + 1] = pq[i];
		i--;
	}
	i++;

	pq[i] = idx;
}

void pop(int idx) {
	for (int i = 0; i < pq_count; i++) {
		if (pq[i] == idx) {
			for (int j = i; j < pq_count - 1; j++) {
				pq[j] = pq[j + 1];
			}
		}
	}
}

void BestFirst_Bound() {
	init_PQ();

	int v = 0;
	int max_profit = value(v);
	push(v);

	int level = 1;
	while (!empty_PQ()) {
		pop(v);

		if (bound(v) > max_profit) {
			for (int i = 0; i <= 1; i++) {
				int u =
					if (value(u) > max_profit) max_profit = value(u);
				if (bound(u) > max_profit) push(u);
			}
		}

	}

}


int main() {
	int N, W;
	cin >> N >> W;

	max_jams = N;
	max_weight = W;

	for (int i = 1; i <= N; i++) {
		cin >> weight[i] >> profit[i];
		profit_per[i] = profit[i] / weight[i];
	}

	BestFirst_Bound();

	return 0;
}
