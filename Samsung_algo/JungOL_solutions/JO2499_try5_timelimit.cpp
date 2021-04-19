#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_SIZE = 1000;

vector<int> weight;
vector<vector<int>> w_poss(MAX_SIZE);


void DFS(int w, int level, int max_level) {
	if (level == max_level) {
		w_poss[w % MAX_SIZE].push_back(w);
		sort(w_poss[w % MAX_SIZE].begin(), w_poss[w % MAX_SIZE].end());
		return;
	}

	DFS(w, level + 1, max_level);
	DFS(w + weight[level], level + 1, max_level);
}

int solution(int N, int MAX_W) {
	DFS(0, 0, N);

	for (int i = 1; i <= MAX_W; i++) {
		bool isExist = false;
		int idx = i % MAX_SIZE;

		for (auto iter = w_poss[idx].begin(); iter != w_poss[idx].end(); iter++) {
			if (*iter == i) {
				isExist = true;
				break;
			}
		}

		if (!isExist) return i;
	}
}

int main() {
	freopen("sample.txt", "r", stdin);

	int N;
	scanf("%d", &N);

	int MAX_WEIGHT = 0;
	for (int i = 0; i < N; i++) {
		int w;
		scanf("%d", &w);

		weight.push_back(w);
		MAX_WEIGHT += w;
	}

	int answer = solution(N, MAX_WEIGHT);

	printf("%d \n", answer);

	return 0;
}