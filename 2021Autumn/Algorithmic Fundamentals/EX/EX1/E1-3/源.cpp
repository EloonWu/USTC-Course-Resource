#include<stdio.h>
#include<stdlib.h>

#define N 1000005
int a[N], b[N];
long long int cnt = 0;

void task3(int l, int r)
{
    if (r > l)
    {
        int mid = (r + l) / 2;
        int i = l;
        int p = l;
        int q = mid + 1;
        task3(l, mid);
        task3(mid + 1, r);
        while (p <= mid || q <= r) 
        {
            if (q > r || (p <= mid && a[p] <= a[q])) 
                b[i++] = a[p++];
            else 
            {
                b[i++] = a[q++];
                cnt += mid - p + 1;
            }
        }
        for (i = l; i <= r; i++) 
            a[i] = b[i];
    }
}

int main()
{
    int m;
    int num;
    scanf("%d", &num);
    for (m = 0; m < num; m++)
        scanf("%d", &a[m]);
    task3(0, m - 1);
    printf("%lld", cnt % 10000007);
    return 0;
}