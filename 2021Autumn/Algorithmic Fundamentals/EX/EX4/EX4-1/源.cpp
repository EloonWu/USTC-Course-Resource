#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 10000

int N, R;

int cnt = 0;

void swap(int* x, int* y)
{
    int tmp = *y;
    *y = *x;
    *x = tmp;
}

void quick_sort(int* array, int start, int end)
{
    if (start >= end) return;
    int pivot = array[end];
    int i = start - 1;
    for (int j = start; j < end; j++)
    {
        if (array[j] <= pivot)
        {
            i++;
            swap(array + i, array + j);
        }
    }
    i++;
    swap(array + i, array + end);

    quick_sort(array, start, i - 1);
    quick_sort(array, i + 1, end);
}

int main()
{
    int m, n;
	int posi;
    int village[MAX];
	scanf("%d %d", &N, &R);
	for (m = 0; m < N; m++)
		scanf("%d", &village[m]);

    quick_sort(village, 0, N - 1);

    for (m = 0; m < N; m++)
    {
        if (village[m] == -1)
            continue;
        else
        {
            cnt++;
            n = m;
            while (village[n] <= village[m] + R && n < N)
                n++;
            int lrange = village[n - 1] - R;
            int rrange = village[n - 1] + R;
            for (n = m; n < N; n++)
            {
                if (village[n] >= lrange && village[n] <= rrange)
                    village[n] = -1;
                else
                    break;
            }

        }
    }
    printf("%d", cnt);
    return 0;
}
