#include <iostream>

using namespace std;

int cache_q[10] = { 0, };
int front = -1;
int rear = -1;

bool cache_full() {

}

void cache_miss(int work) {
	if (cache_full()) dequeue();
	
	enqueue(work);
}

void cache_find(int work) {


}


int main() {
	ios::sync_with_stdio(false);
	
	int S, N;
	cin >> S >> N;

	for (int i = 0; i < N; i++) {
		int work;
		cin >> work;

		cache_find(work);
	}



	return 0;
}