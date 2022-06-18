#include <iostream>
#include <algorithm>
#include <stdlib.h>

using namespace std;

int N, M;

bool compare(int a, int b)
{
	return a < b; 
}

int main()
{
	int left = 0;
	int right;
	int mid;
	int result;
	scanf("%d %d", &N, &M);
	int* Position = (int*)malloc(sizeof(int) * N);
	for (int m = 0; m < N; m++)
		scanf("%d", &Position[m]);
	sort(Position, Position + N, compare);

	right = Position[N - 1] - Position[0];

	while (left <= right)
	{
		mid = (left + right) / 2;
		int total = 1;
		int last = 0;
		int curr;

		for (int m = 1; m < N && total < N - M; m++)
		{
			curr = m;
			int interval = Position[curr] - Position[last];
			if (interval >= mid)
			{
				last = curr;
				total++;
			}
		}

		if (total >= N - M)
			left = mid + 1;
		else
			right = mid - 1;
	}

	printf("%d", right);
	return 0;
}