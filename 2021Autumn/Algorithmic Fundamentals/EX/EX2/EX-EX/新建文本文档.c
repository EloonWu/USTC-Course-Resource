#include <stdio.h>
#include <stdlib.h>

typedef struct DangerCoe 
{
    int obj1;
    int obj2;
    int coe;
} DangerCoe;

typedef struct Elem 
{
    int p;
    int against;
    int rank;
} Elem;

Elem* disjset;

void swap(DangerCoe* x, DangerCoe* y) 
{
    DangerCoe tmp = *y;
    *y = *x;
    *x = tmp;
}

void quick_sort(DangerCoe *array, int start, int end) 
{
    if (start >= end) return;
    int pivot = array[end].coe;
    int i = start - 1;
    for (int j = start; j < end; j++) 
    {
        if (array[j].coe >= pivot) 
        {
            i++;
            swap(array+i, array+j);
        }
    }
    i++;
    swap(array+i, array+end);
    
    quick_sort(array, start, i-1);
    quick_sort(array, i+1, end);
}



int find_root(int id) 
{
    if (disjset[id].p != id) 
        disjset[id].p = find_root(disjset[id].p);
    return disjset[id].p;
}


void union_set(int x, int y) 
{
    if (disjset[x].rank > disjset[y].rank) 
        disjset[y].p = x;
    else 
    {
        disjset[x].p = y;
        if (disjset[x].rank == disjset[y].rank) disjset[y].rank++;
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    DangerCoe* coes = (DangerCoe*)malloc(sizeof(DangerCoe) * m);
    for (int i = 0; i < m; i++) 
    {
        scanf("%d %d %d", &coes[i].obj1, &coes[i].obj2, &coes[i].coe);
    }
    // 先按危险系数排序
    quick_sort(coes, 0, m-1);

    disjset = (Elem*)malloc(sizeof(Elem)*(n+1));
    // 初始化
    for (int i = 0; i < n + 1; i++) 
    {
        disjset[i].against = -1;
        disjset[i].p = i;
    }
    for (int i = 0; i < m; i++) 
    {
        int obj1_root = find_root(coes[i].obj1);
        int obj2_root = find_root(coes[i].obj2);

        if (obj1_root == obj2_root) 
        {
            printf("%d\n", coes[i].coe);
            return 0;
        }

        if (disjset[coes[i].obj1].against != -1 && disjset[coes[i].obj2].against != -1) 
        {
            // 两个 obj 都曾出现过
            int obj1_root_against_root = find_root(disjset[obj1_root].against);
            int obj2_root_against_root = find_root(disjset[obj2_root].against);
            union_set(obj1_root_against_root, obj2_root);
            union_set(obj2_root_against_root, obj1_root);
        }
        else if (disjset[coes[i].obj1].against != -1 && disjset[coes[i].obj2].against == -1) 
        {
            // obj1 出现过, obj2 没出现过
            int obj1_root_against_root = find_root(disjset[obj1_root].against);
            union_set(obj1_root_against_root, coes[i].obj2);
        }
        else if (disjset[coes[i].obj1].against == -1 && disjset[coes[i].obj2].against != -1) 
        {
            // obj1 没出现过, obj2 出现过
            int obj2_root_against_root = find_root(disjset[obj2_root].against);
            union_set(obj2_root_against_root, coes[i].obj1);
        }
        disjset[coes[i].obj1].against = coes[i].obj2;
        disjset[coes[i].obj2].against = coes[i].obj1;

    }
    printf("0\n");
}