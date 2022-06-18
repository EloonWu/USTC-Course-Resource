#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

#define N 5000
#define M 100000

struct edge
{
	int from;
	int to;
	int next;
};

edge Edge[M], Edge_shrink[M];
int head[N], head_shrink[N];
int component[N];
int Size[N];
int DFN[N];
int LOW[N];
int cnt, top;
int Stack[N];
bool visited[N];


void Tarjan(int u)
{
	DFN[u] = LOW[u] = ++cnt;
	Stack[++top] = u;
	visited[u] = true;
	for (int i = head[u]; i != 0; i = Edge[i].next)
	{
		if (DFN[Edge[i].to] == 0)
		{
			Tarjan(Edge[i].to);
			LOW[u] = min(LOW[u], LOW[Edge[i].to]);
		}
		else
		{
			if (visited[Edge[i].to])
				LOW[u] = min(LOW[u], DFN[Edge[i].to]);
		}
	}
	if (LOW[u] == DFN[u])
	{
		for (; Stack[top] != 0; top--)
		{
			visited[Stack[top]] = false;
			component[Stack[top]] = u;
			Size[u]++;
			if (Stack[top] == u)
				break;
		}
	}
}
int degree[N], length[N];

void Sort(int n)
{
	queue<int>Queue;
	for (int i = 1; i <= n; i++)
	{
		if (component[i] == i && degree[i] == 0)
		{
			Queue.push(i);
			length[i] = Size[i];
		}
	}
	while (!Queue.empty())
	{
		int head = Queue.front();
		Queue.pop();
		for (int i = head_shrink[head]; i != 0; i = Edge_shrink[i].next)
		{
			length[Edge_shrink[i].to] = max(length[Edge_shrink[i].to], length[head] + Size[Edge_shrink[i].to]);
			degree[Edge_shrink[i].to]--;
			if (degree[Edge_shrink[i].to] == 0)
				Queue.push(Edge_shrink[i].to);
		}
	}
}

void addedge(int i, int u, int v)
{
	cin >> u >> v;
	Edge[i].from = u;
	Edge[i].to = v;
	Edge[i].next = head[u];
	head[u] = i;
}

int main()
{
	int n, m, u, v;
	int k;
	int result = 0;
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
		addedge(i, u, v);
	for (int i = 1; i <= n; i++)
	{
		if (DFN[i] == 0)
			Tarjan(i);
	}
	for (int i = 1; i <= m; i++)
	{
		if (component[Edge[i].from] != component[Edge[i].to])
		{
			k++;
			Edge_shrink[k].from = component[Edge[i].from];
			Edge_shrink[k].to = component[Edge[i].to];
			Edge_shrink[k].next = head_shrink[component[Edge[i].from]];
			head_shrink[component[Edge[i].from]] = k;
			degree[component[Edge[i].to]]++;
		}
	}
	Sort(n);
	for (int i = 1; i <= n; i++)
	{
		if (component[i] == i)
			result = max(result, length[i]);
	}
	cout << result;
	return 0;
}



