#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void merge(int* arr, int start, int mid, int end)
{
	int len_l, len_r; //左右待合并区间的长度
	len_l = mid - start + 1;
	len_r = end - mid;
	int* l = (int*)malloc(len_l * sizeof(int));
	int* r = (int*)malloc(len_r * sizeof(int));
	memcpy(l, arr + start, sizeof(int) * len_l);
	memcpy(r, arr + mid + 1, sizeof(int) * len_r);

	int i = 0, j = 0, k = start;
	while (i < len_l && j < len_r)
	{
		arr[k++] = l[i] < r[j] ? l[i++] : r[j++];
	}

	while (i < len_l)
	{
		arr[k++] = l[i++];
	}
}

void merge_sort(int* arr, int start, int end)
{
	if (start < end)
	{
		int mid = (start + end) / 2;
		merge_sort(arr, start, mid);
		merge_sort(arr, mid + 1, end);
		merge(arr, start, mid, end);
	}
}

void task2(char* ch, int len, int T)
{
	char number = T + '0';
	int m, n = 0;
	char* buffer;
	buffer = (char*)malloc((len + 1) * sizeof(char));
	memset(buffer, 0, len + 1);
	int* arr;
	arr = (int*)malloc(1000000 * sizeof(int));
	int num = 0;

	for (m = 0; m < len; m++)
	{
		if (ch[m] != number)
		{
			buffer[n] = ch[m];
			n++;
		}
		else
		{
			if (strlen(buffer) != 0)
			{
				arr[num] = atoi(buffer);
				memset(buffer, 0, n + 1);
				n = 0;
				num++;
			}
		}
	}
	if (strlen(buffer) != 0)
	{
		arr[num] = atoi(buffer);
		memset(buffer, 0, n + 1);
		num++;
	}

	merge_sort(arr, 0, num - 1);
	for (m = 0; m < num; m++)
	{
		printf("%d ", arr[m]);
	}
}

int main()
{
	int N, T;
	char* ch;
	scanf("%d %d", &N, &T);
	ch = (char*)malloc(N * sizeof(char));
	scanf("%s", ch);

	task2(ch, N, T);

	return 0;
}