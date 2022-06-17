## **Packet Capture with** PingPlotter

吴毅龙  PB19111749

### 1

**Display the rules to filter the IP and ICMP packets between source host and destination host. Are there any other Application-layer protocols when you traceroute gaia.cs.umass.edu?**

* 过滤源主机和目标主机之间的IP和ICMP数据包的规则为

  `ip.dst == 128.119.245.12 or (ip.dst == 211.86.145.150 and icmp)`

  其中`128.119.245.12`为目的`IP`地址，`211.86.145.150`为源主机`IP`地址

  ![](F:\Study_Sources\2021autumn\计算机网络\Lab\Lab2\images\001-1.png)

* 跟踪路由`gaia.cs.umass.edu`时还用到的应用层协议有`DNS`

  ![](F:\Study_Sources\2021autumn\计算机网络\Lab\Lab2\images\001-2.png)



### 2

**How many hops between source and destination? Find the first ICMP Echo Request packet that has TTL=1, is this packet fragmented? If yes, how many fragments, and why is the packet fragmented?** 

![](F:\Study_Sources\2021autumn\计算机网络\Lab\Lab2\images\002-1.png)

* 由上图易知，源主机与目的主机时间有`31`跳

* `TTL=1`的包如下图所示

  ![](F:\Study_Sources\2021autumn\计算机网络\Lab\Lab2\images\002-2.png)

  这个包被分成了3个分片；一个链路层帧能承载的最大数据量叫做**最大传送单元（MTU）**，链路层的MTU限制了IP数据报的长度。所以在源主机上或是路由器上会将IP数据报中的数据分片成两个或更多个较小的IP数据报，用单独的链路层帧封装这些较小的IP数据报，然后向输出链路上发送这些帧。

### 3

**How the packets are fragmented and reassembled? For each fragment, how to know if it is the last fragment, and how many bytes are contained in each fragment? Print the packets and answer by highlighting the relevant fields.**

* 一个链路层帧能承载的最大数据量叫做**最大传送单元（MTU）**，链路层的MTU限制了IP数据报的长度。所以在源主机上或是路由器上会将IP数据报中的数据分片成两个或更多个较小的IP数据报，用单独的链路层帧封装这些较小的IP数据报，然后向输出链路上发送这些帧。分片的重新组装工作放到端系统中，而不是在网络路由中。

* 当路由器需要对一个数据报分片时，形成的每个分片具有初始数据报的原地址、目的地址与标识号。**最后一个分片的标志比特被设置为0，其他分片的标志比特为1**。另外使用**偏移字段**可以确定每一个分片在原数据报中的位置。

* 具体到实验结果如下图所示：

  第一个分片包含`1500byte`，其中`20byte`头部，`1480byte`数据

  ![](F:\Study_Sources\2021autumn\计算机网络\Lab\Lab2\images\003-1.png)

  第二个分片包含`1500byte`，其中`20byte`头部，`1480byte`数据

  ![](F:\Study_Sources\2021autumn\计算机网络\Lab\Lab2\images\003-2.png)

  第三个分片包含`40byte`，其中`20byte`头部，`20byte`数据

  ![](F:\Study_Sources\2021autumn\计算机网络\Lab\Lab2\images\003-3.png)

  从以上三个图中可以很容易看到，三个分片的`Identification: 0xfc37(64567)`，说明三个分片源自同一个包

  其中第一个和第二个包的`Flag: 0x20, More fragments`，表示后面还有更多分片；第三个分片的`Flag: 0x01`表示是最后一个分片。

  第一个分片`Fragment Offset: 0`，第二个分片`Fragment Offset: 1480`，第三个分片`Fragment Offset: 2960`，是分片在目的主机可以顺利组装



### 4

**What packet is returned from the router when TTL expires? What is contained in the payload of the packet?** 

* 当`TTL`到期时，这一跳路由器会向源主机发送一个`ICMP`包，告知源主机`TTL `已经过期。

![](F:\Study_Sources\2021autumn\计算机网络\Lab\Lab2\images\004-1.png)

* 包的有效载荷中由`IP`承载`ICMP`报文。如上图所示：`Type: 11(Time-to-live exceeded)`表示接收到的包`TTL`已经过期；`Code: 0(Time-to-live in transit)`表示在`transit`过程中过期；接下来两行表示检验和与检验和无误；后面还包含有过期包的信息（`IP`报文头以及`IP`承载的内容），内容如下图所示。

![](F:\Study_Sources\2021autumn\计算机网络\Lab\Lab2\images\004-2.png)



### 5

**Which link crosses the Pacific, give the router addresses at the two ends of the link. Explained your reason.** 

![](F:\Study_Sources\2021autumn\计算机网络\Lab\Lab2\images\005.png)

* `13-14`跳为跨越太平洋的链路，两端路由器的IP分别是`210.25.187.41`和`210.25.189.50`
* 原因：由上图可知，`13`跳以前，包括`14`跳以后的平均时延增幅都比较小，从`13`跳到`14`跳之间平均时延有明显增加。



### 6

**How long is the trans-Pacific link? (given that a bit transmits 2*10^8 m/s in fiber).** 

第`13`跳的平均响应时间为`31.6 ms`，第`14`跳的平均响应时间为`186.6 ms`

则估计太平洋链路的长度为$(186.6-31.6)/1000×2×10^8=31000km$

