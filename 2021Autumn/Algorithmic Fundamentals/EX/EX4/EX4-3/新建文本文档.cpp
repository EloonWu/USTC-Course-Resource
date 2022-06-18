#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <assert.h>
#include <climits>

using namespace std;

typedef pair<int, int> AddrAndNext;

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);

    unordered_map<int, int> last_time_used_map;

    vector<AddrAndNext> addr_and_nexts(n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &addr_and_nexts[i].first);
        addr_and_nexts[i].second = INT_MAX;

        auto last_time = last_time_used_map.find(addr_and_nexts[i].first);
        if (last_time != last_time_used_map.end())
        {
            addr_and_nexts[last_time->second].second = i;
            last_time->second = i;
        }
        else
            last_time_used_map.insert(pair<int, int>(addr_and_nexts[i].first, i));
    }

    map<int, int> cached;

    int i = 0;
    int miss_count = 0;

    // first fill the cache
    for (i = 0; cached.size() < k && i < n; i++)
    {
        auto ann = cached.find(addr_and_nexts[i].first);
        if (ann == cached.end())
        {
            // cache missed
            cached.insert(addr_and_nexts[i]);
            miss_count++;
        }
        else
        {
            // cache hit
            ann->second = addr_and_nexts[i].second;
        }
    }

    // then go on
    for (; i < n; i++)
    {
        auto cur_ann = cached.find(addr_and_nexts[i].first);
        if (cur_ann == cached.end())
        {
            // cache miss
            miss_count++;
            assert(cached.size() == k);
            // find the addr cached that will be lastestly used
            AddrAndNext latest_ann = *cached.begin();
            for (auto &&ann : cached)
            {
                if (ann.second > latest_ann.second)
                {
                    latest_ann = ann;
                }
            }
            cached.erase(latest_ann.first);
            cached.insert(addr_and_nexts[i]);
        }
        else
        {
            // cache hit
            cur_ann->second = addr_and_nexts[i].second;
        }
    }

    printf("%d\n", miss_count);
}