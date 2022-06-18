## 算法第三次作业

PB19111747 王凯

### p1 

伪代码如下所示：

```C
CUT-ROD(p, n, c)
1:	let r[0..n] be a new array
2:	r[0] = 0
3:	for j = 1 to n do
4:		q = p[j] // 将q初始化为不切割的收益
5:    	for i = 1 to j - 1 do
6:			// 修改q的更新方案，加上成本c 
7:        	q = max(q, p[i] + r[j - i] + c)
8:		r[j] = q
9:	return r[n]      
```



### p2

证明：易知，计算$m[i,j]$时，需要访问：$m[i,k]$与$m[k+1,j]$，$k\in [i,j-1]$

​			假设$n$为矩阵的总个数，则：$m[i,j]$会被$m[i,p]\space (p\in[j+1,n])$以及$m[q,j](q\in[1,i-1])$共$n+i-j-1$元素访问

​			故：$\sum_{i=1}^n\sum_{j=i}^nR(i,j)=\sum_{i=1}^n\sum_{j=i}^n(n+i-j-1)=\sum_{i=1}^n(\frac{n^2}{2}-\frac{i^2}{2}+\frac{3}{2}i-\frac{n}{2}-1)$

​			根据平方和公式：$1²+2²+3²+...+n²=\frac{n(n+1)(2n+1)}{6}$

​			原式$=\frac{n^2}{2}\times n-\frac{1}{2}\frac{n(n+1)(2n+1)}{6}+\frac{3}{2}\frac{(n+1)n}{2}-\frac{n^2}{2}-n=\frac{n^3-n}{3}$



### p3

解：假设每一问题为$p[i,j]$，其中：$i\in[1,j]$，$j\in[1,n]$

​		则子问题图共有：$\sum_{j=1}^{n}(j)=\frac{n(n+1)}{2}$个结点。

​		对于每个节点$p[i,j]$而言，它与$p[i,k]$与$p[k+1,j]$结点有边相连，其中:$k\in[i,j-1]$

​		共与：$2(j-i)$个子结点有边关联，故推出：共有$\sum_{j=1}^{n}\sum_{1}^{j}2(j-i)=\frac{n(n+1)(n-1)}{3}$个边
