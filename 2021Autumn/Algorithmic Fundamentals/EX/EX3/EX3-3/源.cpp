#include<stdio.h>
#include<stdlib.h>
#define NumMAX 200
#define WeightMAX 1000

int Weight;
int Num;
int Value = 0;
struct Obj
{
	int weight;
	int value;
	int num;
};

int max(int x, int y)
{
	if (x > y)
		return x;
	else
		return y;
}

int main()
{
	int i, j, k, m;
	int weight, value, num;
	Obj* list;
	int dp[NumMAX][WeightMAX];
	scanf("%d %d", &Num, &Weight);
	list = (Obj*)malloc(Num * sizeof(Obj));
	for (m = 0; m < Num; m++)
		scanf("%d %d %d", &list[m].weight, &list[m].value, &list[m].num);

	for (i = 0; i < NumMAX; i++)
	{
		for (j = 0; j < WeightMAX; j++)
			dp[i][j] = 0;
	}
	for (i = 1; i <= Num; i++)
	{
		weight = list[i - 1].weight;
		value = list[i - 1].value;
		num = list[i - 1].num;
		for (j = 1; j <= Weight; j++)
		{
			for (k = 0; k <= num; k++)
			{
				if (k * weight <= j)
					dp[i][j] = max(dp[i][j], dp[i - 1][j - k * weight] + k * value);
				else
					break;
			}
			Value = max(Value, dp[i][j]);
		}
	}
	printf("%d", Value);
	return 0;
}