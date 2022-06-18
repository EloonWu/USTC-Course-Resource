#include<stdio.h>
#include<stdlib.h>
#define MAX 200

int min(int x, int y, int z)
{
	if (x <= y && x <= z)
		return x;
	else
	{
		if (y <= x && y <= z)
			return y;
		else
		{
			if (z <= x && z <= y)
				return z;
		}
	}
}

int main()
{
	int m, n;
	int i, j;
	int map[MAX][MAX];
	int dp[MAX][MAX];
	int re = 0;
	scanf("%d %d", &m, &n);
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
			scanf("%d", &map[i][j]);
	}
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (i == 0 || j == 0)
				dp[i][j] = !map[i][j];
			else
			{
				if (map[i][j] == 1)
					dp[i][j] = 0;
				else
					dp[i][j] = min(dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]) + 1;
			}
			re += dp[i][j];
		}
	}
	printf("%d", re);
	return 0;
}