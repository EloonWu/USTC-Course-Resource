#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

int main()
{
	int N, K;
	int i;
	int cnt = 0;
	scanf("%d %d", &N, &K);
	unordered_map<int, int>NextUse;
	vector<pair<int, int>>BufferUnit(N);
	map<int, int>Buffer;
	
	for (i = 0; i < N; i++)
	{
		scanf("%d", &BufferUnit[i].first);
		BufferUnit[i].second = N + 1;
		auto iter = NextUse.find(BufferUnit[i].first);
		if (iter == NextUse.end())
			NextUse.insert(pair<int, int>(BufferUnit[i].first, i));
		else
		{
			BufferUnit[iter->second].second = i;
			iter->second = i;
		}
	}

	for (i = 0; i < N && Buffer.size() < K; i++)
	{
		auto iter = Buffer.find(BufferUnit[i].first);
		if (iter == Buffer.end())
		{
			cnt++;
			Buffer.insert(BufferUnit[i]);
		}
		else
			iter->second = BufferUnit[i].second;
	}
	for (; i < N; i++)
	{
		auto iter = Buffer.find(BufferUnit[i].first);
		if (iter == Buffer.end())
		{
			cnt++;
			pair<int, int> next = *Buffer.begin();
			for (auto&& unit : Buffer)
			{
				if (unit.second > next.second)
					next = unit;
			}
			Buffer.erase(next.first);
			Buffer.insert(BufferUnit[i]);
		}
		else
			iter->second = BufferUnit[i].second;
	}
	printf("%d", cnt);
	return 0;
}