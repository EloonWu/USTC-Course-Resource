## Homework03   2021.10.15

### 1  
**Compute 8-bit checksum for 01100010 and 10111001, and use an example to show that if the two numbers each has a 1-bit error, the checksum can not detect the errors.**

两数相加并进行回卷：$01100010+10111001=100011011$，回卷得到$00011100$，求反码得到$11100011$

如传输没有差错，则$01100010+10111001+11100011=11111111$

如果传输出错，$01100010$变成$01110010$，$10111001$变成$10101001$，。而$01110010+10101001+11100011=11111111$，为全1串无法检验出差错。



### 2

**Consider the following cwnd evolution at a TCP sender:**

<img src="F:\Study_Sources\2021autumn\计算机网络\HW\HW3\images\001.png" style="zoom: 50%;" />

**(a)  Is this TCP Tahoe or TCP Reno?**

**(b)  What is the sender’s initial ssthresh?**

**(c)  What happens at time 10? What is ssthresh and cwnd at time 11?** 

**(d)  What happens at time 22? What is ssthresh and cwnd at time 23?**

**(e)  What happens at time 36? What is ssthresh and cwnd at time 37?**

**(f)   When is the 50th segment is sent?**

**(g)  Which intervals the TCP connection is under slow start?**



(a)	$Reno$.  因为从图中可以看出有快速恢复状态

(b)	$32MSS$

(c)	超时指示的丢包事件；$ssthresh=18MSS$   $cwnd=1MSS$

(d)	当收到3个冗余ACK的丢包事件；$ssthresh=12MSS$   $cwnd=15MSS$

(e)	超时指示的丢包事件；$ssthresh=14MSS$   $cwnd=1MSS$

(f)	$time 6$

(g)	$time 1-time 6$	$time 11-time 16$	$time 37-time 41$



### 3

**Host A sets up a TCP connection with Host B, fill in the blanks the appropriate sequence and acknowledgement numbers.** 

![](F:\Study_Sources\2021autumn\计算机网络\HW\HW3\images\屏幕截图 2021-10-16 160857.png)

<img src="F:\Study_Sources\2021autumn\计算机网络\HW\HW3\images\屏幕截图 2021-10-16 160911.png" style="zoom:80%;" />





### 4

**Two TCP connections A and B strictly follow AIMD and they share a same bottleneck of 100 Mbps. Initially connection A has a throughput of 64 Mbps, connection B has a throughput of 32 Mbps, the two connections increase their throughputs at a same rate.** 

1) **Fill in following table.** 
2) **After how many loss events, the difference between the two connections’ throughputs is within 5 Mbps?** 

| **Round**          | **A**        | **B**        | different |
| ------------------ | ------------ | ------------ | --------- |
| **1st loss event** | **64→66→33** | **32→34→17** | 16        |
| **2nd loss event** | 33→58→29     | 17→42→21     | 8         |
| **3rd loss event** | 29→54→27     | 21→46→23     | 4         |
| **4th loss event** | 27→52→26     | 23→48→24     | 2         |

1. 如上表所示
2. 经历3轮loss event，两连接的吞吐量差距在 5 Mbps以内
