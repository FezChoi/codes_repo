int get_max(int a, int b) {
	return (a > b) ? a : b;
}

int solve(int n, int k) {
	int D[max_N + 1][max_K + 1]{ 0, }; // 크기가 너무 크면 전역변수로 뺄 것
	// 매번 할당하는 것보다 초기화 하는 것이 조금 더 빠름!

	for (int i = 1; i <= n; i++) {			// 보석
		for (int j = 1; j <= k; j++) {		// 배낭 용량
			if (wi[i] > j)					// 보석의 무게가 배낭의 용량보다 크면,
				D[i][j] = D[i - 1][j];	// 보석을 못 넣는 경우
			else
				D[i][j] = get_max(D[i - 1][j], D[i - 1][j - wi[i]] + p[i]);
				// 보석을 넣는 경우
				// 보석의 무게만큼 배낭의 용량을 확보하고, 가중치를 계산하여 비교
		}
	}

	return D[n][k];
}