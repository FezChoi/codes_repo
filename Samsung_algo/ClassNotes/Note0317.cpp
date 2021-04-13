//선택정렬

for (size_t i = 0; i < k; i++)
{
	int minidx = i;
	for (size_t j = i + 1; j < N; j++)
	{
		if (arr[minidx] > arr[j]) {
			minidx = j;
		}
	}

	int tmp = arr[i];
	arr[j] = arr[minidx];
	arr[minidx] = tmp;
}


//

for (int i = 0; str[i]; i++)
{
	//delimiter가 아닌 동안 실행
}