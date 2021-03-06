### Homework09 2021.12.15

#### 1

**我们怎样才能使用$Floyd-Warshall$算法的输出来检测权重为负值的环路？**  

在运行完$Floyd-Warshall$算法之后，得到结果矩阵，对结果矩阵再进行一轮迭代计算。如果结果不变，说明没有权重为负值的环路；否则，就说明图中含有权重为负值的环路。

因为如果图中有权重为负值的环路，在进行一次迭代计算之后，会有路径的$cost$减小，反映在矩阵上就是值发生改变。



#### 2

**假定在一个权重函数为 $W$ 的有向图图 $G $上运行$ Johnson $算法。证明：如果图 $G $包含一条权重为$0 $的环路 $c$，那么对于环路$ c$ 上的每条边$ (u,v)$，$ \hat{w} (u,v) = 0$**  

$\because$  有权重为$0$的环路$c$，且$\hat{w} (u,v)=w(u,v)+h(u)-h(v)$

设环路$c$上的点为$u_i,i=1,2,...,n$

$\therefore$  $\hat{w} (u_1,u_2)+\hat{w} (u_2,u_3)+...+\hat{w} (u_n,u_1)=0$

$\because$  $\hat{w} (u,v) \geq 0$

$\therefore$  $\hat{w} (u,v)=0$



#### 3

**(最大流的更新) 设 $G = (V,E)$ 是一个源结点为 $s$ 汇结点为 $t $的流网络，其容量全部为整数值。假定我们已经给定 $G $的一个最大流。**
**a. 如果将单条边$ (u,v) \in  E $的容量增加$ 1$ 个单位，请给出一个$ O(V + E)$ 时间的算法来对最大流进行更新。**
**b. 如果将单条边$ (u,v) \in E$ 的容量减少$ 1$ 个单位，请给出一个 $O(V + E) $时间的算法来对最大流进行更新。**  

a. 假设$(S,S')$是最小割，当$u \in S,v \in S'$或$u \in S',v\in S$时，最大流将会增加$1$。

对于已经给定的$G$的一个最大流，再进行一次$Ford\ Fulkerson$算法计算，利用$BFS$寻找增广路径，如果找到则最大流会被更新。由于容量都是整数值，且流量的增量是$1$，所以一次$Ford\ Fulkerson$算法计算就可以确定结果。时间复杂度就是$BFS$的复杂度$O(V + E)$

b. 首先利用$BFS$在$O(V + E)$的时间内找到一条从$s$到$t$并且包含$(u,v)$的路径，将该路径上所有边的流都减小$1$。再进行一次$Ford\ Fulkerson$算法计算，利用$BFS$寻找增广路径，如果找到则最大流会被更新。

