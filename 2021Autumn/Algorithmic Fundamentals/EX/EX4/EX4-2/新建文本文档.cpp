#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

class Task
{
public:
    int r; // arriving time
    int p; // run time

    Task() {}
    Task(int r, int p) : r(r), p(p) {}
};

int main()
{
    int n;
    scanf("%d", &n);

    vector<Task> tasks(n);

    auto rcmp = [](const Task &x, const Task &y) -> bool
    { return x.r > y.r; };
    priority_queue<Task, vector<Task>, decltype(rcmp)> arrive_queue(rcmp);

    int r, p;
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &tasks[i].r, &tasks[i].p);
        arrive_queue.push(tasks[i]);
    }

    auto pcmp = [](const Task &x, const Task &y)
    { return x.p > y.p; };
    priority_queue<Task, vector<Task>, decltype(pcmp)> lefttime_queue(pcmp);

    int time = arrive_queue.top().r;
    int total_cost = 0;
    int i = 0;
    while (true)
    {
        // add all tasks arriving before time into lefttime_queue
        while (!arrive_queue.empty() && arrive_queue.top().r <= time)
        {
            lefttime_queue.push(arrive_queue.top());
            arrive_queue.pop();
        }

        // if arrive_queue is empty, then we only need to finish left tasks one by one.
        if (arrive_queue.empty())
            break;

        // run the task with minimun p, first findout if it will be interrupted
        if (!lefttime_queue.empty())
        {
            Task top = lefttime_queue.top();
            lefttime_queue.pop();

            int period = min(arrive_queue.top().r - time, top.p);
            time += period;
            top.p -= period;
            if (top.p == 0)
                total_cost += time - top.r;
            else
                lefttime_queue.push(top);
        }
        // if lefttime_queue is empty, then we might need to move forward the time
        if (lefttime_queue.empty())
            time = arrive_queue.top().r;
    }

    while (!lefttime_queue.empty())
    {
        Task top = lefttime_queue.top();
        lefttime_queue.pop();
        time += top.p;
        total_cost += time - top.r;
    }

    printf("%d\n", total_cost);
}