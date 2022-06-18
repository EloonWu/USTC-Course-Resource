#include<stdio.h>
#include<stdlib.h>

int task1(int arr[], int num)
{
	int m, n;
	int probable = arr[0];
	int sum = 1;
	for (m = 1; m < num; m++)
	{
		if (sum == 0)
			probable = arr[m];
		if (arr[m] == probable)
			sum++;
		else
			sum--;
	}

	sum = 0;
	for (m = 0; m < num; m++)
	{
		if (arr[m] == probable)
			sum++;
	}

	if (2 * sum >= num + 1)
		return probable;
	else
		return -1;
}

int main()
{
	int T, N;
	int* arr;
	int i, j;
	int result;
	scanf("%d", &T);

	for (i = 0; i < T; i++)
	{
		scanf("%d", &N);
		arr = (int*)malloc(N * sizeof(int));
		for (j = 0; j < N; j++)
			scanf("%d", &arr[j]);

		result = task1(arr, N);
		printf("%d\n", result);
	}
	return 0;
}