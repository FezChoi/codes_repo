#include <stdio.h>


const int JAMS = 1000;

int Weight[JAMS + 1] = { 0, };
int Profit[JAMS + 1] = { 0, };

int max_jams = 0;
int max_weight = 0;
int max_profit = 0;


void DFS(int w, int p) {
	for (int i = 0; i < max_jams; i++) {
		int tmp_w = w + Weight[i];

		if (tmp_w > max_weight) {
			max_profit = (p > max_profit) ? p : max_profit;
		}
		else if (tmp_w == max_weight) {
			p += Profit[i];
			max_profit = (p > max_profit) ? p : max_profit;
			return;
		}
		else
			DFS(tmp_w, p + Profit[i]);
	}
}


int main() {
	freopen("sample.txt", "r", stdin);

	scanf("%d %d", &max_jams, &max_weight);
	
	for (int i = 0; i < max_jams; i++) 
		scanf("%d %d", &Weight[i], &Profit[i]);
	
	DFS(0, 0);
	
	printf("%d \n", max_profit);

	return 0;
}