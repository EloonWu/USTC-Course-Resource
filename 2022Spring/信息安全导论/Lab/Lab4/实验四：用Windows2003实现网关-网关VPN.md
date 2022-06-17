## 实验四：用Windows2003实现网关-网关VPN

吴毅龙 PB19111749



### 1. 实验目的

​		用 IPsec 隧道方式配置网关-网关 VPN， 连接被 Internet 隔开的两个局域网(VMnet1 和 VMnet3)， 使之进行安全通信，实现信息的保密和完整。



### 2. 实验设计

​		下载并导入到虚拟机。 然后复制 5 台 Windows2003SP2 虚拟机，分别用作 ServerA、ServerB、 Router、 ClientA 和 ClientB。 用 VirtualBox Host-Only Ethernet Adapter 模拟两个局域网和一个广域网（用路由器模拟）。 每个局域网含若干台客户机和一台 Windows server2003 组成。 具体设计和规划如下图：

<img src="/Users/elonwu/Documents/Study_Sources/2022spring/信息安全导论/Lab/Lab4/images/Snipaste_2022-05-07_14-43-48.png" style="zoom: 67%;" />

​		虚拟网卡 VMnet1 和 VMnet3 分别模拟两个局域网， VMnet5、 VMnet6 和 Router 模拟因特网。 ServerA 和 ServerB 模拟互联网上的边界路由器 (远程服务器)，建立 IPSec 隧道以连接两个局域网， 用于保证通信安全。 VirtualBox 的网络配置如下图所示：

<img src="/Users/elonwu/Documents/Study_Sources/2022spring/信息安全导论/Lab/Lab4/images/Snipaste_2022-05-07_14-45-19.png" style="zoom:50%;" />

​		按照实验指导的配置表格配置各个虚拟机的网络设置。其中相同颜色框选出的IP地址应该相同。

<img src="/Users/elonwu/Documents/Study_Sources/2022spring/信息安全导论/Lab/Lab4/images/Snipaste_2022-05-07_18-08-53.png" style="zoom:67%;" />

​		将路由器、 ClientA 及 ClientB 的 IPv4 地址的第 4 个点分十进制数（如 192.168.86.202的第 4 个点分十进制数为 202） 改成你学号的最后 3 位数字%200（进行“模 200”运算），其他部分的 IP 地址也可能需要修改以避免 IP 地址重复。实际IP地址信息配置如下所示：

|  机器名  |     虚拟网络     | IP地址信息                                                   |
| :------: | :--------------: | ------------------------------------------------------------ |
| Client A |      VMnet1      | IP: 192.168.86.149<br>Subnet Mask: 255.255.255.0<br>**GateWay: 192.168.86.203** |
| Sever A  | VMnet1<br>VMnet5 | **IP: 192.168.86.203**<br>Subnet Mask: 255.255.255.0<br>GateWay: <br><br>IP: 55.55.55.203<br>Subnet Mask: 255.0.0.0<br>**GateWay: 55.55.55.149** |
|  Router  | VMnet5<br>VMnet6 | **IP: 55.55.55.149**<br/>Subnet Mask: 255.0.0.0<br/>GateWay: <br/><br/>**IP: 166.66.66.149**<br/>Subnet Mask: 255.255.0.0<br/>GateWay: |
| Server B | VMnet6<br>VMnet3 | IP: 166.66.66.213<br/>Subnet Mask: 255.255.0.0<br/>**GateWay: 166.66.66.149**<br/><br/>**IP: 10.0.0.213**<br/>Subnet Mask: 255.0.0.0<br/>GateWay: |
| Client B |      VMnet3      | IP: 10.0.0.149<br/>Subnet Mask: 255.0.0.0<br/>**GateWay: 10.0.0.213** |

​		配置结果如下所示：

* Client A

<img src="/Users/elonwu/Documents/Study_Sources/2022spring/信息安全导论/Lab/Lab4/images/clientA.jpg" alt="clientA" style="zoom:80%;" />

* Server A

<img src="/Users/elonwu/Documents/Study_Sources/2022spring/信息安全导论/Lab/Lab4/images/serverA.jpg" alt="serverA" style="zoom:80%;" />

* Router

<img src="/Users/elonwu/Documents/Study_Sources/2022spring/信息安全导论/Lab/Lab4/images/router1.jpg" alt="router1" style="zoom:80%;" />

* Server B

<img src="/Users/elonwu/Documents/Study_Sources/2022spring/信息安全导论/Lab/Lab4/images/serverB.jpg" alt="serverB" style="zoom:80%;" />

* Client B

<img src="/Users/elonwu/Documents/Study_Sources/2022spring/信息安全导论/Lab/Lab4/images/clientB.jpg" alt="clientB" style="zoom:80%;" />



### 3. 实验步骤

#### 3.1 创建Sever A的IPSec策略

* 管理工具中打开”本地安全策略”--右击”IP 安全策略,在本地计算机”—“创建 IP 安全策略”--命名为”AB”--取消选择”激活默认响应规则”--.编辑”AB”属性,添加新规则(不使用添加向导)

  <img src="/Users/elonwu/Documents/Study_Sources/2022spring/信息安全导论/Lab/Lab4/images/001.jpg" alt="001" style="zoom:80%;" />

  <img src="/Users/elonwu/Documents/Study_Sources/2022spring/信息安全导论/Lab/Lab4/images/002.jpg" alt="002" style="zoom:80%;" />

  <img src="/Users/elonwu/Documents/Study_Sources/2022spring/信息安全导论/Lab/Lab4/images/003.jpg" alt="003" style="zoom:80%;" />

* 添加"IP 筛选器列表",命名为"A to B"--添加属性(不使用添加向导),设置源地址为"特定 IP 子网:192.168.86.0",目的地址设置为"特定 IP 子网:10.0.0.0"--取消选择"镜像"--协议设定为默认值:"任意"。

  <img src="/Users/elonwu/Documents/Study_Sources/2022spring/信息安全导论/Lab/Lab4/images/004.jpg" alt="004" style="zoom:80%;" />

  <img src="/Users/elonwu/Documents/Study_Sources/2022spring/信息安全导论/Lab/Lab4/images/005.jpg" alt="005" style="zoom:80%;" />

  <img src="/Users/elonwu/Documents/Study_Sources/2022spring/信息安全导论/Lab/Lab4/images/006.jpg" alt="006" style="zoom:80%;" />

  <img src="/Users/elonwu/Documents/Study_Sources/2022spring/信息安全导论/Lab/Lab4/images/007.jpg" alt="007" style="zoom:80%;" />

* 筛选器操作(不使用添加向导):安全措施为"协商安全",新增安全措施为"完整性和加密"

  <img src="/Users/elonwu/Documents/Study_Sources/2022spring/信息安全导论/Lab/Lab4/images/008.jpg" alt="008" style="zoom:80%;" />

  <img src="/Users/elonwu/Documents/Study_Sources/2022spring/信息安全导论/Lab/Lab4/images/009.jpg" alt="009" style="zoom:80%;" />

  <img src="/Users/elonwu/Documents/Study_Sources/2022spring/信息安全导论/Lab/Lab4/images/010.jpg" alt="010" style="zoom:80%;" />

* 身份验证方法,使用预共享密钥: microsoft

  <img src="/Users/elonwu/Documents/Study_Sources/2022spring/信息安全导论/Lab/Lab4/images/011.jpg" alt="011" style="zoom:80%;" />

  <img src="/Users/elonwu/Documents/Study_Sources/2022spring/信息安全导论/Lab/Lab4/images/012.jpg" alt="012" style="zoom:80%;" />

* 隧道设置,指定隧道终点 IP 地址(Server B 的外网 IP 地址： 166.66.66.213)

  <img src="/Users/elonwu/Documents/Study_Sources/2022spring/信息安全导论/Lab/Lab4/images/013.jpg" alt="013" style="zoom:80%;" />

* 连接类型为"所有连接"

  <img src="/Users/elonwu/Documents/Study_Sources/2022spring/信息安全导论/Lab/Lab4/images/014.jpg" alt="014" style="zoom:80%;" />

* 重复(2)-(6),创建 IP 筛选器列表"B to A"。设置从 ServerB 到 ServerA 的 IP 策略。 将“源子网(IP)”和“目的子网(IP)”互换， 隧道终点设置为 55.55.55.203

  <img src="/Users/elonwu/Documents/Study_Sources/2022spring/信息安全导论/Lab/Lab4/images/015.jpg" alt="015" style="zoom:80%;" />

* 在本地安全设置中,右击策略"AB"—指派

  <img src="/Users/elonwu/Documents/Study_Sources/2022spring/信息安全导论/Lab/Lab4/images/016.jpg" alt="016" style="zoom:80%;" />

#### 3.2 创建 ServerB 的 IPSec 策略

​		按相同的方法步骤， 创建 ServerB 的 IP 安全策略并指派。

<img src="/Users/elonwu/Documents/Study_Sources/2022spring/信息安全导论/Lab/Lab4/images/017.jpg" alt="017" style="zoom:80%;" />

#### 3.3 配置远程访问/VPN 服务器

* 配置 Server A、 Router 和 Server B 为路由器。 在“开始”—“所有程序”—“管理工具”菜单中选择“路由和远程访问”， 如下图所示：

  <img src="/Users/elonwu/Documents/Study_Sources/2022spring/信息安全导论/Lab/Lab4/images/018.jpg" alt="018" style="zoom:80%;" />

* 打开“路由和远程访问”管理界面， 选择“配置并启用路由和远程访问”， 如下图所示：

  <img src="/Users/elonwu/Documents/Study_Sources/2022spring/信息安全导论/Lab/Lab4/images/019.jpg" alt="019" style="zoom:80%;" />

* 配置为“两个专用网络之间的安全连接”， 如下图所示：

  <img src="/Users/elonwu/Documents/Study_Sources/2022spring/信息安全导论/Lab/Lab4/images/Snipaste_2022-05-07_19-06-00.jpg" alt="020" style="zoom:80%;" />

* 不选择拨号 VPN，如下图所示

  <img src="/Users/elonwu/Documents/Study_Sources/2022spring/信息安全导论/Lab/Lab4/images/021.jpg" alt="021" style="zoom:80%;" />

* 配置完成后， ServerA 可以和 ServerB 互联互通。

#### 3.4 ping 测试(Client A)

​		在 Client A 的 cmd 中输入>ping 10.0.0.149，或者在 Client B 的 cmd 中输入>ping192.168.86.149。 如果两方的 IPsec 策略未配置正确， 不会 ping 通。 如果正确则说明两个局域网互联互通。

<img src="/Users/elonwu/Documents/Study_Sources/2022spring/信息安全导论/Lab/Lab4/images/999.jpg" style="zoom:80%;" />
