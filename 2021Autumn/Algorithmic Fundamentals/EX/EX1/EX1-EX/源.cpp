#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<stdio.h>
#include<stdlib.h>

void Swap(int* a, int* b)
{
    int temp;
    temp = *a; *a = *b; *b = temp;
}


void InsertSort(int arr[], int l, int r)
{
    for (int i = l + 1; i <= r; i++)
    {
        if (arr[i - 1] > arr[i])
        {
            int t = arr[i];
            int j = i;
            while (j > l&& arr[j - 1] > t)
            {
                arr[j] = arr[j - 1];
                j--;
            }
            arr[j] = t;
        }
    }
}

int Partion(int arr[], int p, int r, int pivot)
{
    for (int i = p; i <= r; i++)
    {
        if (arr[i] == pivot)
        {
            Swap(&arr[i], &arr[r]);
            break;
        }
    }
    int i = p - 1;
    for (int j = p; j < r; j++)
    {
        if (arr[j] <= arr[r])
        {
            i++;
            Swap(&arr[i], &arr[j]);
        }
    }
    Swap(&arr[i + 1], &arr[r]);
    return i + 1;
}

int task_ex(int arr[], int p, int r, int k)
{
    if (p == r)
        return arr[p];
    int len = r - p + 1;
    int midnum;
    if (len > 5)
    {
        if (len % 5 == 0)
            midnum = len / 5;
        else
            midnum = len / 5 + 1;
    }
    else
        midnum = 1;
    int* midarr;
    midarr = (int*)malloc(sizeof(int) * midnum);
    int count = p;
    for (int i = 0; i < midnum - 1; i++)
    {
        InsertSort(arr, count, count + 4);
        midarr[i] = arr[count + 2];
        count += 5;
    }
    InsertSort(arr, count, r);
    midarr[midnum - 1] = arr[count + (r - count) / 2];

    int pivot = task_ex(midarr, 0, midnum - 1, (midnum + 1) / 2);


    int pos = Partion(arr, p, r, pivot);
    int len1 = pos - p + 1;
    if (len1 == k)
        return pivot;
    else if (len1 > k)
        return task_ex(arr, p, pos - 1, k);
    else
        return task_ex(arr, pos + 1, r, k - len1);
}


int main()
{
	int T;
	int m, n;
	int N, K;
	int* arr;
	scanf("%d", &T);
	for (m = 0; m < T; m++)
	{
		scanf("%d %d", &N, &K);
		arr = (int*)malloc(N * sizeof(int));
		for (n = 0; n < N; n++)
		{
			scanf("%d", &arr[n]);
		}

        printf("%d\n", task_ex(arr, 0, N - 1, K));
		free(arr);
	}
	return 0;
}