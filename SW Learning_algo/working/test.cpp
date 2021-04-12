#include <iostream>

using namespace std;

int workload[1001] = { 0, };

void TwoPoint(int S, int N) {
	int front = 1;
	int rear = 1;

	while (rear < N) {
		int cache_size = rear - front + 1;

		while (cache_size < S) {
			int work = workload[++rear];

			for (int i = front; i < rear; i++) {
				//cache_hit
				if (workload[i] == work) {
					workload[i] = 0;
					break;
				}
			}
		}

		bool cache_hit = false;


		if (cache_size < S)
			continue;
		else if (cache_size > S) {

		}

		//cache_miss
		if (!cache_hit && rear - front > S) 
			front++;
	}
	
	for (int i = rear; i >= front; i--) {
		if (workload[i] != 0)
			cout << workload[i] << " ";
	}
}

int main() {
	ios::sync_with_stdio(false);
	
	freopen("input.txt", "r", stdin);

	int S, N;
	cin >> S >> N;

	for (int i = 1; i <= N; i++)
		cin >> workload[i];

	TwoPoint(S, N);

	return 0;
}