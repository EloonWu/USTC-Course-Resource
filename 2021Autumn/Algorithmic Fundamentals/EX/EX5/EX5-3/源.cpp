#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

const long long inf = INT_MAX;
int n, m, s, t, u, v;
long long w, ans, dis[520010];
int tot = 1, now[520010], head[520010];

struct node {
	int to, net;
	long long val;
} e[520010];

inline void add(int u, int v, long long w) {
	e[++tot].to = v;
	e[tot].val = w;
	e[tot].net = head[u];
	head[u] = tot;

	e[++tot].to = u;
	e[tot].val = 0;
	e[tot].net = head[v];
	head[v] = tot;
}

inline int bfs() 
{ 
	for (int i = 1; i <= n; i++) 
		dis[i] = inf;
	queue<int> q;
	q.push(s);
	dis[s] = 0;
	now[s] = head[s];
	while (!q.empty()) 
	{
		int x = q.front();
		q.pop();
		for (int i = head[x]; i; i = e[i].net) 
		{
			int v = e[i].to;
			if (e[i].val > 0 && dis[v] == inf) 
			{
				q.push(v);
				now[v] = head[v];
				dis[v] = dis[x] + 1;
				if (v == t) 
					return 1;
			}
		}
	}
	return 0;
}

int dfs(int x, long long sum) 
{
	if (x == t) return sum;
	long long k, res = 0; 
	for (int i = now[x]; i && sum; i = e[i].net) 
	{
		now[x] = i; 
		int v = e[i].to;
		if (e[i].val > 0 && (dis[v] == dis[x] + 1)) 
		{
			k = dfs(v, min(sum, e[i].val));
			if (k == 0) 
				dis[v] = inf;  
			e[i].val -= k;
			e[i ^ 1].val += k;
			res += k;   
			sum -= k;  
		}
	}
	return res;
}

int main() {
	scanf("%d%d%d%d", &n, &m, &s, &t);
	for (int i = 1; i <= m; i++) 
	{
		scanf("%d%d%lld", &u, &v, &w);
		add(u, v, w);
	}
	while (bfs()) {
		ans += dfs(s, inf);   
	}
	printf("%lld", ans);
	return 0;
};
