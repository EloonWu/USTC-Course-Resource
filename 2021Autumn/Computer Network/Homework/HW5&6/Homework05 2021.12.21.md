### Homework05 2021.12.21

#### 1.

**In CRC, consider a 5-bit generator, G=10011, and suppose that D has the value 1010101010. What is the value of R?**

$101010101000000 \div10011$的余式为$01000$，即$R=01000$

<img src="F:\Study_Sources\2021autumn\计算机网络\HW\HW5&6\images\QQ图片20211221222839.jpg" style="zoom:33%;" />

#### 2.

**Consider the following network.**

<img src="F:\Study_Sources\2021autumn\计算机网络\HW\HW5&6\images\Snipaste_2021-12-21_21-49-32.png" style="zoom:67%;" />

**a. How many LANs are interconnected? List the hosts, switches and router interfaces belonging to each LAN.**

**b. Suppose host A sends an IP datagram to host F, for the three path segments from A to R1, R1 to R2, and R2 to F, list all the source/destination IP addresses and MAC addresses in each path segment.**

**c. Suppose each pair of hosts have successfully pinged each other, list the ARP table for each host (ignore the TTL).**

**d. List the switch tables of the switches (ignore the TTL).**

a.3 LANs

​	LAN1：A, B, S1以及R1的左侧端口

​	LAN2：C, D, S2, R1的右侧端口以及R2的左侧端口

​	LAN3：E, F, S3以及R2的右侧端口

b.

|          | src.&dst. IP                 | src.&dst. MAC                            |
| -------- | ---------------------------- | ---------------------------------------- |
| A to R1  | 192.168.1.2<br />192.168.3.3 | 00-00-00-00-00-00<br />22-22-22-22-22-22 |
| R1 to R2 | 192.168.1.2<br />192.168.3.3 | 33-33-33-33-33-33<br />66-66-66-66-66-66 |
| R2 to F  | 192.168.1.2<br />192.168.3.3 | 77-77-77-77-77-77<br />99-99-99-99-99-99 |

c.

A:

| IP.addr     | MAC               |
| ----------- | ----------------- |
| 192.168.1.1 | 22-22-22-22-22-22 |
| 192.168.1.3 | 11-11-11-11-11-11 |

B:

| IP.addr     | MAC               |
| ----------- | ----------------- |
| 192.168.1.1 | 22-22-22-22-22-22 |
| 192.168.1.2 | 00-00-00-00-00-00 |

C:

| IP.addr     | MAC               |
| ----------- | ----------------- |
| 192.168.2.1 | 33-33-33-33-33-33 |
| 192.168.2.4 | 55-55-55-55-55-55 |
| 192.168.2.2 | 66-66-66-66-66-66 |

D:

| IP.addr     | MAC               |
| ----------- | ----------------- |
| 192.168.2.1 | 33-33-33-33-33-33 |
| 192.168.2.3 | 44-44-44-44-44-44 |
| 192.168.2.2 | 66-66-66-66-66-66 |

E:

| IP.addr     | MAC               |
| ----------- | ----------------- |
| 192.168.3.1 | 77-77-77-77-77-77 |
| 192.168.3.3 | 99-99-99-99-99-99 |

F:

| IP.addr     | MAC               |
| ----------- | ----------------- |
| 192.168.3.1 | 77-77-77-77-77-77 |
| 192.168.3.2 | 88-88-88-88-88-88 |

d.

S1:

| Address           | Interface |
| ----------------- | --------- |
| 00-00-00-00-00-00 | 1         |
| 11-11-11-11-11-11 | 2         |
| 22-22-22-22-22-22 | 3         |

S2:

| Address           | Interface |
| ----------------- | --------- |
| 33-33-33-33-33-33 | 1         |
| 44-44-44-44-44-44 | 2         |
| 55-55-55-55-55-55 | 3         |
| 66-66-66-66-66-66 | 4         |

S3:

| Address           | Interface |
| ----------------- | --------- |
| 77-77-77-77-77-77 | 1         |
| 88-88-88-88-88-88 | 2         |
| 99-99-99-99-99-99 | 3         |



#### 3.

**Consider the following network, and suppose each pair of hosts have successfully pinged each other, list the switch table for each of the three switches (ignore the TTL).**

<img src="F:\Study_Sources\2021autumn\计算机网络\HW\HW5&6\images\Snipaste_2021-12-21_21-51-37.png" style="zoom:80%;" />

S1:

| Address           | Interface |
| ----------------- | --------- |
| 00-00-00-00-00-00 | 1         |
| 11-11-11-11-11-11 | 2         |
| 22-22-22-22-22-22 | 3         |
| 33-33-33-33-33-33 | 3         |
| 44-44-44-44-44-44 | 3         |
| 55-55-55-55-55-55 | 3         |

S2:

| Address           | Interface |
| ----------------- | --------- |
| 00-00-00-00-00-00 | 1         |
| 11-11-11-11-11-11 | 1         |
| 22-22-22-22-22-22 | 2         |
| 33-33-33-33-33-33 | 3         |
| 44-44-44-44-44-44 | 4         |
| 55-55-55-55-55-55 | 4         |

S3:

| Address           | Interface |
| ----------------- | --------- |
| 00-00-00-00-00-00 | 1         |
| 11-11-11-11-11-11 | 1         |
| 22-22-22-22-22-22 | 1         |
| 33-33-33-33-33-33 | 1         |
| 44-44-44-44-44-44 | 2         |
| 55-55-55-55-55-55 | 3         |



#### 4.

**Let’s consider the operation of a learning switch in the context of a network in which 6 nodes labeled A through F are star connected into an Ethernet switch. Suppose that **

**(i) B sends a frame to E, **

**(ii) E replies with a frame to B, **

**(iii) A sends a frame to B, **

**(iv) B replies with a frame to A. **

**The switch table is initially empty. Show the state of the switch forwarding table before and after each of these events. For each of these events, identify the link(s) on which the transmitted frame will be forwarded.**

<img src="F:\Study_Sources\2021autumn\计算机网络\HW\HW5&6\images\Snipaste_2021-12-21_21-52-15.png"  />

| Events | Switch Forwarding Table | Forwarding Links |
| ------ | ----------------------- | ---------------- |
| i      | {B, 2}                  | 1, 3, 4, 5, 6    |
| ii     | {B, 2 ; E, 5}           | 2                |
| iii    | {B, 2 ; E, 5 ; A, 1}    | 2                |
| iv     | {B, 2 ; E, 5 ; A, 1}    | 1                |



#### 5.

**Suppose two mobile nodes communicate with mobile IP, as shown in the following graph, each has its permanent address and care-of-address, and the visited networks have dedicated mobile agents on the routers. On which paths the IP packets contains encapsulated headers, and give all the destination addresses of the IP headers (including the encapsulated headers) for the packets on each path.**

![](F:\Study_Sources\2021autumn\计算机网络\HW\HW5&6\images\Snipaste_2021-12-21_21-52-52.png)

Packets on path 2 and path 5 contains encapsulated headers

| Path | (inner) dst. addr. | outter dst. addr. |
| ---- | ------------------ | ----------------- |
| 1    | 128.119.40.18      | -                 |
| 2    | 128.119.40.18      | 79.129.13.2       |
| 3    | 128.119.40.18      | -                 |
| 4    | 10.10.10.1         | -                 |
| 5    | 10.10.10.1         | 20.20.20.2        |
| 6    | 10.10.10.1         | -                 |

