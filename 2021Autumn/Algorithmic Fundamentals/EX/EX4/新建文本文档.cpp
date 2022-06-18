#ifndef STUPID

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    vector<int> clothes(n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &clothes[i]);
    }

    sort(clothes.begin(), clothes.end(), less<int>());

    int left = 0, right = clothes[n - 1] - clothes[0];
    int target = n - m;
    // 借鉴学长的思路, 采用二分策略 (https://github.com/lyc0930/Online-Judge/tree/master/ItA/E4-EX)
    while (left <= right)
    {
        int mid = (left + right) / 2;
        int last_x = clothes[0];
        int count = 1;

        for (int i = 1; i < n && count < target; i++)
        {
            if (clothes[i] >= last_x + mid)
            {
                count++;
                last_x = clothes[i];
            }
        }

        if (count >= target)
            left = mid + 1;
        else
            right = mid - 1;
    }

    printf("%d\n", right);
}

#else
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <queue>
#include <unordered_set>

using namespace std;

class Cloth
{
public:
    int x;
    int next_idx;
    int prev_idx;
    Cloth() {}
    Cloth(int x) : x(x) {}
};

using ClothPair = pair<int, int>;

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    vector<Cloth> clothes(n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &clothes[i].x);
    }

    sort(clothes.begin(), clothes.end(), [](const Cloth &x, const Cloth &y)
         { return x.x < y.x; });

    auto cmp = [&](const ClothPair &x, const ClothPair &y)
    {
        return clothes[x.second].x - clothes[x.first].x > clothes[y.second].x - clothes[y.first].x;
    };
    priority_queue<ClothPair, vector<ClothPair>, decltype(cmp)> distances(cmp);

    for (int i = 0; i < n - 1; i++)
    {
        clothes[i].next_idx = i + 1;
        clothes[i].prev_idx = i - 1;
        distances.push(ClothPair(i, i + 1));
    }
    clothes[n - 1].next_idx = -1;
    clothes[n - 1].prev_idx = n - 2;

    for (int i = 0; i < m; i++)
    {
        auto nearest = distances.top();
        distances.pop();
        while (clothes[nearest.first].x == -1 || clothes[nearest.second].x == -1)
        {
            nearest = distances.top();
            distances.pop();
        }
        auto left = nearest.first;
        auto right = nearest.second;

        auto to_remove = left;
        if (clothes[left].prev_idx == -1)
        {
            to_remove = right;
        }
        else if (clothes[right].next_idx == -1)
            to_remove = left;
        else
        {
            // if left isn't begin and right isn't last
            auto leftleft = clothes[left].prev_idx;
            auto rightright = clothes[right].next_idx;
            int ifleft = min(clothes[right].x - clothes[leftleft].x, clothes[rightright].x - clothes[right].x);
            int ifright = min(clothes[rightright].x - clothes[left].x, clothes[right].x - clothes[leftleft].x);
            if (ifleft < ifright)
                to_remove = right;
            else
                to_remove = left;
        }

        distances.push(ClothPair(clothes[to_remove].prev_idx, clothes[to_remove].next_idx));

        clothes[clothes[to_remove].prev_idx].next_idx = clothes[to_remove].next_idx;
        clothes[clothes[to_remove].next_idx].prev_idx = clothes[to_remove].prev_idx;
        clothes[to_remove].x = -1;
    }

    auto nearest = distances.top();
    distances.pop();
    while (clothes[nearest.first].x == -1 || clothes[nearest.second].x == -1)
    {
        nearest = distances.top();
        distances.pop();
    }

    printf("%d\n", clothes[nearest.second].x - clothes[nearest.first].x);
}
#endif