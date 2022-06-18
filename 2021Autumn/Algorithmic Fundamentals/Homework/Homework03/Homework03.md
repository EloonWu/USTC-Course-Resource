## Homework02 2021.11.2

### 1.

**我们对钢条切割问题进行一点修改，除了切割下的钢条段具有不同价格 $p_i$ 外，每次切割还要付出固定的成本 c。这样，切割方案的收益就等于钢条段的价格之和减去切割的成本。设计一个动态规划算法解决修改后的钢条切割问题。**  

```C
CUT-ROD(p. n)
let r[0...n]be a new array
r[0] = 0
for j = 1 to n
	q = -∞
	for i = 1 to j - 1
		q = max(q, p[i] + r[j-i] - c)
	q = max(q, p[j])
	r[j] = q
return r[n]
```



### 2.

**令 $R(i, j)$ 表示在一次调用 MATRIX-CHAIN-ORDER 过程中，计算其他表项时访问表项 $m[i, j] $的次数。证明：**  $\sum_{i=1}^{n} \sum_{j=i}^{n} R(i,j)=\frac{n^3-n}{3}$

设矩阵的总数为n，在计算$m[i,j]$时，需要访问$m[i,k]$与$m[k+1,j]$，$k\in [i,j-1]$

所以，$m[i,j]$会被$m[i,p]\space p\in[j+1,n]$以及$m[q,j]q\in[1,i-1]$访问，共$n+i-j-1$个元素

$\sum_{i=1}^n\sum_{j=i}^nR(i,j)=\sum_{i=1}^n\sum_{j=i}^n(n+i-j-1)=\sum_{i=1}^n(\frac{n^2}{2}-\frac{n}{2}-\frac{i^2}{2}+\frac{3}{2}i-1)\\=\frac{n^3}{2}-\frac{n^2}{2}-\frac{1}{2}\frac{n(n+1)(2n+1)}{6}+\frac{3}{2}\frac{(n+1)n}{2}-n=\frac{n^3-n}{3}$



### 3.

**对输入链长度为 n 的矩阵链乘法问题，描述其子问题图：它包含多少个顶点？包含多少条边？这些边分别连接哪些顶点。**  

对于子问题中节点$m[i,j]$，$i\in[1,j]$，$j\in[1,n]$

子问题图共有：$\sum_{j=1}^{n} \sum_{i=1}^{j}1=\frac{n(n+1)}{2}$个结点。

对于节点$m[i,j]$，它与$m [i,k]$与$m [k+1,j]$结点有边相连 $k\in[i,j-1]$

故其子问题图共有$\sum_{j=1}^{n}\sum_{1}^{j}2(j-i)=\frac{n(n+1)(n-1)}{3}$条边
