#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int x;
    int y;
};

void Swap(Node* x, Node* y)
{
    Node tmp = *y;
    *y = *x;
    *x = tmp;
}

void Quick_sort(Node* list, int start, int end)
{
    if (start >= end) return;
    int pivot = list[end].x;
    int i = start - 1;
    for (int j = start; j < end; j++)
    {
        if (list[j].x >= pivot)
        {
            i++;
            Swap(list + i, list + j);
        }
    }
    i++;
    Swap(list + i, list + end);

    Quick_sort(list, start, i - 1);
    Quick_sort(list, i + 1, end);
}
int max(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}

int EX3_1(Node* list, int num)
{
    int* dp;
    int m, n;
    int re = 1;
    dp = (int*)malloc(num * sizeof(int));
    for (m = 0; m < num; m++)
        dp[m] = 1;
    for (m = 1; m < num; m++)
    {
        for (n = 0; n < m; n++)
        {
            if (list[n].y <= list[m].y)
                dp[m] = max(dp[m], dp[n] + 1);
        }
        re = max(re, dp[m]);
    }
    return re;
}

int main()
{
	int num;
	int k;
	Node* list;
	scanf("%d", &num);
	list = (Node*)malloc(num * sizeof(Node));
	for (k = 0; k < num; k++)
	{
		scanf("%d %d", &list[k].x, &list[k].y);
	}

    printf("%d", EX3_1(list, num));
    return 0;
}