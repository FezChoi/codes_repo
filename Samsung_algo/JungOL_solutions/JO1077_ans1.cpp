#include <stdio.h>
#include <stdlib.h>

int N, W;

struct Jewel {
	int weight;
	int price;
};

Jewel *jewel;

int main() {
	freopen("input.txt", "r", stdin);

	scanf("%d %d", &N, &W);

	jewel = (Jewel *)malloc(sizeof(Jewel) * (N + 1));

	for (int i = 1; i <= N; i++) {
		scanf("%d %d", &jewel[i].weight, &jewel[i].price);
	}

	int *c = (int *)malloc(sizeof(int) * (W + 1));
	for (int i = 0; i <= N; i++) c[i] = 0;

	for (int i = 1; i <= W; i++) {
		int maxCost = 0;
		for (int j = 1; j <= N; j++) {
			int weight = jewel[j].weight;
			int price = jewel[j].price;

			if (i - weight >= 0 && c[i - weight] + price > maxCost)
				maxCost = c[i - weight] + price;
		}
		c[i] = maxCost;
	}

	for (int i = 0; i <= W; i++)
		printf("%d \n", c[i]);

	free(c);
	free(jewel);

	return 0;
}