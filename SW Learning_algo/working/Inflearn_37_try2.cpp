#include <iostream>

using namespace std;

int cache_q[11] = { 0, };
int cache_size = 0;

void cache_control(int work) {
	int idx = 1;

	// cache_find
	for (int i = 1; i <= cache_size; i++) {
		if (cache_q[i] == work) {
			idx = i;
			break;
		}
	}

	// cache_hit & cache_miss
	for (int i = idx; i < cache_size; i++)
		cache_q[i] = cache_q[i + 1];

	cache_q[cache_size] = work;
}



int main() {
	ios::sync_with_stdio(false);
	
	freopen("input.txt", "r", stdin);

	int S, N;
	cin >> S >> N;

	cache_size = S;

	for (int i = 1; i <= N; i++) {
		int work;
		cin >> work;

		cache_control(work);
	}

	for (int j = cache_size; j > 0 ; j--)
		cout << cache_q[j] << " ";

	return 0;
}