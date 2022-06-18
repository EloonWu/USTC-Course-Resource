#include <algorithm>
#include <iostream>
#include <queue>
#include <climits>
#define N 100000
#define M 1000000

using namespace std;

struct Edge
{
	int to, w, next;
}edge[M];

struct queueNode
{
    int position; 
    int distance; 
    bool operator<(const queueNode& that) const
    {
        return this->distance > that.distance;
    }
};

int head[N];
int Distance[N];
bool ifvisited[N];
int cnt;

void init(int n,int s)
{
    for (int i = 0; i <= n; i++)
    {
        head[i] = 0;
        Distance[i] = INT_MAX;
    }
    cnt = 1;
    Distance[s] = 0;
}

void add_edge(int u, int v, int w)
{
    edge[cnt].to = v;
    edge[cnt].w = w;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

int main()
{
    int n, m, s, t, u, v, w;
    priority_queue<queueNode> Queue;

    cin >> n >> m >> s >> t;
    init(n, s);

    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        add_edge(u, v, w);
    }

    Queue.push({ s, 0 });
    while (!Queue.empty())
    {
        int top = Queue.top().position;
        Queue.pop();
        if (ifvisited[top])
            continue;
        else
            ifvisited[top] = true;
        for (int i = head[top]; i != 0; i = edge[i].next)
        {
            int end = edge[i].to;
            if (Distance[end] > Distance[top] + edge[i].w)
            {
                Distance[end] = Distance[top] + edge[i].w;
                if (!ifvisited[end])
                    Queue.push({ end,Distance[end] });
            }  
        }
    }
    if (Distance[t] != INT_MAX)
        cout << Distance[t];
    else
        cout << -1;
    return 0;
}