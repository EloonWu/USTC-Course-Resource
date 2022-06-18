#include <algorithm>
#include <iostream>
#define N 100000
#define M 1000000

using namespace std;

struct edge
{
	int u, v, w;
	bool operator<(const struct edge that) const
	{
		return this->w < that.w;
	}
}Edge[M + 1];

int Parent[N + 1];

int Find_Set(int x)
{
	if (x != Parent[x])
		Parent[x] = Find_Set(Parent[x]);
	return Parent[x];
}

int main()
{
	int n, m;
	int result = 0;
	int cnt = 0;
	scanf("%d %d", &n, &m);
	
	for (int i = 0; i < m; i++)
		scanf("%d %d %d", &Edge[i].u, &Edge[i].v, &Edge[i].w);

	sort(Edge, Edge + m);

	for (int i = 1; i <= n; i++)
		Parent[i] = i;

	for (int i = 0; i < m; i++)
	{
		int set_u = Find_Set(Edge[i].u);
		int set_v = Find_Set(Edge[i].v);
		if (set_u == set_v) 
			continue;

		result += Edge[i].w;
		Parent[set_v] = set_u; 
		cnt++;
		if (cnt == n - 1) 
			break;
	}
	printf("%d", result);
	return 0;
}