#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

struct Task
{
	int r;
	int p;
};

struct rcmp
{
	bool operator() (Task a, Task b)
	{
		return a.r > b.r;
	}
};

struct pcmp
{
	bool operator() (Task a, Task b)
	{
		return a.p > b.p;
	}
};

int main()
{
	int N;
	int cost = 0;
	int time;
	scanf("%d", &N);

	vector<Task> task(N);
	priority_queue<Task, vector<Task>, rcmp> arrive;
	priority_queue<Task, vector<Task>, pcmp>leftime;

	for (int i = 0; i < N; i++)
	{
		scanf("%d %d", &task[i].r, &task[i].p);
		arrive.push(task[i]);
	}

	time = arrive.top().r;

	while (1)
	{
		while (arrive.top().r <= time && !arrive.empty())
		{
			leftime.push(arrive.top());
			arrive.pop();
		}
		if (arrive.empty())
			break;
		if (leftime.empty())
		{
			time = arrive.top().r;
		}
		else
		{
			auto lastest = leftime.top();
			leftime.pop();
			int left = min(arrive.top().r - time, lastest.p);
			time += left;
			lastest.p -= left;
			if (lastest.p == 0)
				cost = cost + time - lastest.r;
			else
				leftime.push(lastest);
		}
	}

	while (!leftime.empty())
	{
		auto lastest = leftime.top();
		leftime.pop();
		time += lastest.p;
		cost = cost + time - lastest.r;
	}

	printf("%d", cost);
	return 0;
}