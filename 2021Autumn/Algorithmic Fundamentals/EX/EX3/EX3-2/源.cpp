#include<stdio.h>
#include<stdlib.h>

int t = 1;
int ans = 0;
void EX3_2(int k, int* list)
{
    int tmp = list[k - 1] + list[k];
    ans += tmp;
    for (int i = k; i < t - 1; i++)
        list[i] = list[i + 1];
    t--;
    int j;
    for (j = k - 1; j > 0 && list[j - 1] < tmp; j--)
        list[j] = list[j - 1];
    list[j] = tmp;
    while (j >= 2 && list[j] >= list[j - 2])
    {
        int d = t - j;
        EX3_2(j - 1, list);
        j = t - d;
    }
}


int main()
{
	int m, n;
    int num;
	int* list;
	scanf("%d", &num);
	list = (int*)malloc(num * sizeof(int));
	for (m = 0; m < num; m++)
		scanf("%d", &list[m]);

    for (int i = 1; i < num; i++)
    {
        list[t++] = list[i];
        while (t >= 3 && list[t - 3] <= list[t - 1])
            EX3_2(t - 2, list);
    }
    while (t > 1)
        EX3_2(t - 1, list);
    printf("%d\n", ans);
    return 0;
}