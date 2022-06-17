## Homework04 2021.11.27

### 1.

 **Consider a datagram network using 32-bit host addresses. Suppose a router has four links, numbered 0 through 3, and packets are to be forwarded to the link interfaces as follows:**

|                **Destination Address Range**                 | **Link interface** |
| :----------------------------------------------------------: | :----------------: |
| **11100000 00000000 00000000 00000000<br />through<br />11100000 00111111 11111111 11111111** |       **0**        |
| **11100000 01000000 00000000 00000000<br />through<br />11100000 01000000 11111111 11111111** |       **1**        |
| **11100000 01000001 00000000 00000000<br />through <br />11100001 01111111 11111111 11111111** |       **2**        |
|                        **Otherwise**                         |       **3**        |

**a. Provide a forwarding table that has five CIDR entries, uses longest prefix matching, and forwards packets to the correct link interfaces.**

**b. Describe how your forwarding table determines the appropriate link interface for datagrams with destination addresses:**

**11001000 10010001 01010001 01010101**

**11100001 01000000 11000011 00111100**

**11100001 10000000 00010001 01110111**

a.

|       前缀        | 端口 |
| :---------------: | :--: |
|    11100000 00    |  0   |
| 11100000 01000000 |  1   |
|      1110000      |  2   |
|    11100001 1     |  3   |
|     Otherwise     |  3   |

b.题目所述的目标地址分别从接口3、接口2、接口3转发

### 2.

**Suppose a host send out an IP datagram of a size 3200 bytes (20 bytes header and 3180 bytes of IP payload), suppose that the MTU of the link is 804 bytes, how many fragments are sent out? And what are the values of the Length, flag bit, and Offset fields of each IP fragments?**

| 分片序号 |    分片长度    | 标志位MF | 偏移量 |
| :------: | :------------: | :------: | :----: |
|    1     | 804（=784+20） |    1     |   0    |
|    2     | 804（=784+20） |    1     |   98   |
|    3     | 804（=784+20） |    1     |  196   |
|    4     | 804（=784+20） |    1     |  294   |
|    5     |  64（=44+20）  |    0     |  392   |



### 3.

**Consider the following network. With the indicated link costs, use link-state routing algorithm to compute the shortest path from x to all network nodes. Show how the algorithm works by filling the table as on PPT page 97.**

<img src="F:\Study_Sources\2021autumn\计算机网络\HW\HW4\images\001.png" style="zoom: 50%;" />

由$Dijkstra$算法可得

| Step |      $N’$       | $p(y)$ | $p(z)$ |  $p(u)$  | $p(v)$ | $p(w)$ |  $p(t)$  |
| :--: | :-------------: | :----: | :----: | :------: | :----: | :----: | :------: |
| $0$  |       $x$       | $6,x$  | $8,x$  | $\infty$ | $3,x$  | $6,x$  | $\infty$ |
| $1$  |      $x,v$      | $6,x$  | $8,x$  |  $6,v$   |  $/$   | $6,x$  |  $7,v$   |
| $2$  |     $x,v,y$     |  $/$   | $8,x$  |  $6,v$   |  $/$   | $6,x$  |  $7,v$   |
| $3$  |    $x,v,y,u$    |  $/$   | $8,x$  |   $/$    |  $/$   | $6,x$  |  $7,v$   |
| $4$  |   $x,v,y,u,w$   |  $/$   | $8,x$  |   $/$    |  $/$   |  $/$   |  $7,v$   |
| $5$  |  $x,v,y,u,w,t$  |  $/$   | $8,x$  |   $/$    |  $/$   |  $/$   |   $/$    |
| $6$  | $x,v,y,u,w,t,z$ |  $/$   |  $/$   |   $/$    |  $/$   |  $/$   |   $/$    |

则

| destination |  link   |
| :---------: | :-----: |
|     $y$     | $(x,y)$ |
|     $z$     | $(x,z)$ |
|     $u$     | $(x,v)$ |
|     $v$     | $(x,v)$ |
|     $w$     | $(x,w)$ |
|     $t$     | $(x,v)$ |



### 4.

**Consider the three-node topology, compute the distance tables after the initialization step and after each iteration of a synchronous version of the distance-vector algorithm as in PPT page 109.** 

<img src="F:\Study_Sources\2021autumn\计算机网络\HW\HW4\images\002.png" style="zoom:50%;" />

<img src="F:\Study_Sources\2021autumn\计算机网络\HW\HW4\images\QQ图片20211206172708.jpg" style="zoom: 50%;" />
