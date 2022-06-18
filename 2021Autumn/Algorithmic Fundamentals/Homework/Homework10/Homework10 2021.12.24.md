### Homework10 2021.12.24

#### 1.

**试说明如何扩展$ Rabin-Karp$ 算法用于处理以下问题: 在一个 $n×n$ 的二维字符数组中搜索一个给定的$ m×m $的模式。 (该模式可以在水平方向和垂直方向移动，但是不可以旋转。 )**  

对于一个$m×m$的矩阵，其哈希值按照如下方法计算：先计算$m$列每一列的哈希值，再将这$m$个计算结果计算一个哈希值作为矩阵的哈希值。



#### 2.

**对字母表 $\sum=\{a,b\}$，画出与模式 $ababbabbababbababbabb $对应的字符串匹配自动机的状态转换图**  

![](F:\Study_Sources\2021autumn\算法导论\HW\Homework10\QQ图片20211224170053.jpg)

其中状态$21$为接收状态



#### 3.

**描述解决这一问题的算法，并对算法效果与复杂度进行分析**  

> 你需要求出模式串$P$在原串$S$中出现的次数, 模式串和原串中的字母均为小写, 数据有多组, 每组输出一个答案

* 算法描述：本题是对于$KMP$算法的考察，使用$KMP$算法用$pattren$字符串在$match$字符串中从第$i$个字符开始进行匹配，若成功匹配，$KMP$匹配函数返回此次成功匹配，$pattern$串在$match$串中的位置（$pattern$串首字符在$match$串中的位置）；若匹配失败，则返回$-1$.$func$函数从头到尾使用$KMP$匹配函数遍历$match$串，若成功进行一次匹配，则一下次遍历从上一次成功的位置的下一个字符开始；否则$KMP$函数将会一直遍历，直到$pattern$串结束。

* 算法实现：

```C++
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MATCH 100001
#define PATTERN 1001

void GetNext(int next[], char string[])
{
	int j = 0, k = -1;
	int length = strlen(string);
	next[0] = -1;
	while (j < length - 1)
	{
		if (k == -1 || string[j] == string[k])
			next[++j] = ++k;
		else
			k = next[k];
	}
}

int KMP(int i, char match[], char pattern[])
{
	int j = 0;
	int Plength = strlen(pattern);
	int Mlength = strlen(match);
	int* next = (int*)malloc(Plength * sizeof(int));
	GetNext(next, pattern);

	while (i < Mlength && j < Plength)
	{
		if (j == -1 || match[i] == pattern[j])
		{
			i++;
			j++;
		}
		else
			j = next[j];
	}
	if (j >= Plength)
		return i - Plength;
	else
		return -1;
}

int func(char match[], char pattern[])
{
	int i = 0, j;
	int cnt = 0;
	int Mlength = strlen(match);
	while (i < Mlength)
	{
		j = KMP(i, match, pattern);
		if (j == -1)
			return cnt;
		else
		{
			i = j + 1;
			cnt++;
		}
	}
	return cnt;
}

int main()
{
	int T;
	char match[MATCH];
	char pattern[PATTERN];
	scanf("%d",&T);
	while (T > 0)
	{
		memset(match, '\0', MATCH);
		memset(pattern, '\0', PATTERN);
		scanf("%s", pattern);
		scanf("%s", match);
		
		printf("%d\n", func(match, pattern));
		T--;
	}
	return 0;
}
```

* 算法分析：
  * 算法效果：经OJ平台测试，算法正确
  * 算法复杂度：对于第$t$次，长度为$m_t$的$match$串和长度为$n_t$的$pattern$串，求取$next$数组的时间复杂度是$O(n_t)$，对$match$串进行一次遍历的时间复杂度是$O(m_t)$，故最终的时间复杂度是$\displaystyle O\left(\sum_{t = 1}^T{(m_t + n_t)}\right)$



#### 4.

**对于在无向图中寻找最长简单回路这一问题，给出其形式化的定义并给出其相关的判定问题。另外，给出与该判定问题对应的语言。**  

在无向图中寻找最长简单回路问题的形式化定义是对于无向图$G=(V,E)$，给出图$G$中最长的简单回路

与其相关的判定问题是给定正整数$k$与无向图$G$，$G$中是否存在长度至少为$k$的简单回路，如果存在则输出1；否则输出0

对应的语言是$\{<G,k>:G=(V,E)是一个无向图，k \geq 0是一个整数，即G中存在长度至少为k的简单回路\}$

