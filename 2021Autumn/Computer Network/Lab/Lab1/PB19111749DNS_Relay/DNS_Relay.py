import socket
import threading

class DNS_Relay_Server:      #一个relay server实例，通过缓存文件和外部地址来初始化
    def __init__(self,cache_file,name_server):
        #url_IP字典:通过域名查询ID
        self.url_ip = {}
        self.cache_file = cache_file
        self.load_file()
        self.name_server = name_server
        #trans字典：通过DNS响应的ID来获得原始的DNS数据包发送方
        self.trans = {}

    def load_file(self,):
        f = open(self.cache_file,'r',encoding='utf-8')
        for line in f:
            ip,name = line.split(' ')
            self.url_ip[name.strip('\n')] = ip
        f.close()

    def run(self):
        buffer_size = 512
        server_socket = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
        server_socket.bind(('',53))
        server_socket.setblocking(False)
        while True:
            try:
                data,addr = server_socket.recvfrom(buffer_size)
                threading.Thread(target=self.handle,args=(server_socket,data,addr)).start()
            except:
                continue 

    def handle(self,server_socket,data,addr):
        RecvDp = DNS_Packege(data)
        if RecvDp.QR == 0:#是请求报文:
            print('Query Message, require for :' + RecvDp.name)
            #未在配置文件中，将查询转发给DNS服务器
            if RecvDp.name not in self.url_ip:
                self.trans[RecvDp.ID] = addr
                server_socket.sendto(data, ('223.5.5.5', 53))
                print('Domain Name not in the Configuration file')
            #在配置文件中，构造响应报文
            else:
                ip = self.url_ip[RecvDp.name]
                data_to_send = RecvDp.generate_response(ip, ip == '0.0.0.0')
                server_socket.sendto(data_to_send, addr)
                print('Domain Name in the Configuration file :' + ip)
        elif RecvDp.QR == 1:#是响应报文，转发给请求ID
            addr = self.trans[RecvDp.ID]
            server_socket.sendto(data, addr)
            print('Receive Response')

class DNS_Packege:        #一个DNS Frame实例，用于解析和生成DNS帧
    def __init__(self,data):
        self.data = bytearray(data)
        Msg_arr = bytearray(data)
        #ID
        self.ID = (Msg_arr[0] << 8 ) + Msg_arr[1]
        # FLAGS
        self.QR = Msg_arr[2] >> 7
        self.Opcode = (Msg_arr[2] & 0b01111000) >> 3
        self.AA = (Msg_arr[2] & 0b00000100) >> 2
        self.TC = (Msg_arr[2] & 0b00000010) >> 1
        self.RD = Msg_arr[2] & 0b00000001
        self.RA = (Msg_arr[3] & 0b10000000) >> 7
        self.Z = (Msg_arr[3] & 0b01110000) >> 4
        self.RCODE = Msg_arr[3] & 0b00001111
        # 资源记录数量
        self.QDCOUNT = (Msg_arr[4] << 8) + Msg_arr[5]
        self.ANCOUNT = (Msg_arr[6] << 8) + Msg_arr[7]
        self.NSCOUNT = (Msg_arr[8] << 8) + Msg_arr[9]
        self.ARCOUNT = (Msg_arr[10] << 8) + Msg_arr[11]
        #query内容解析
        i = 12
        name = ''
        length = int(Msg_arr[12])
        while True:
            for j in range(i + 1, i + length + 1):
                name = name + chr(Msg_arr[j])
            i = i + length + 1
            length = int(Msg_arr[i])
            if length == 0:
                break
            else:
                name = name + '.'

        self.name = name
        self.name_length = len(name) + 2

    def generate_response(self,ip,Intercepted):
        self.QR = 1    #响应时QR为1
        self.AA = 0    #该字段在响应报文中有效。值为 0 时，表示不是权威服务器。
        self.RA = 1    #该字段只出现在响应报文中。当值为 1 时，表示服务器支持递归查询。
        self.Z = 0     #保留字段，在所有的请求和应答报文中，它的值必须为 0。
        self.ANCOUNT = 1
        self.NSCOUNT = 0
        self.ARCOUNT = 0
        if not Intercepted:
            self.RCODE = 0
            res = bytearray(32 + self.name_length)
            #以下为首部
            res[0] = self.ID >> 8
            res[1] = self.ID % 256
            res[2] = (self.QR << 7) + (self.Opcode << 3) + (self.AA << 2) + (self.TC << 1) + self.RD
            res[3] = (self.RA << 7) + (self.Z << 4) + self.RCODE
            res[4] = self.QDCOUNT >> 8
            res[5] = self.QDCOUNT % 256
            res[6] = self.ANCOUNT >> 8
            res[7] = self.ANCOUNT % 8
            res[8] = self.NSCOUNT >> 8
            res[9] = self.NSCOUNT % 8
            res[10] = self.ARCOUNT >> 8
            res[11] = self.ARCOUNT % 8
            #以上为首部
            #以下为问题部分，直接复制请求报文
            for i in range(12, 16 + self.name_length):
                res[i] = self.data[i]
            #以上为问题部分
            #以下为资源记录部分
            res[16 + self.name_length] = 0xc0
            res[17 + self.name_length] = 0x0c  #Name 消息压缩
            res[18 + self.name_length] = 0x00
            res[19 + self.name_length] = 0x01  #Type = A
            res[20 + self.name_length] = 0x00
            res[21 + self.name_length] = 0x01  #Class = IN
            for i in range(22 + self.name_length, 26 + self.name_length):  #TTL 零值的含意是 RR 仅能用于正在进行的业务，不能被缓存
                res[i] = 0
            res[26 + self.name_length] = 0
            res[27 + self.name_length] = 4  #RDLENGTH
            ip_part = ip.split('.')
            for i in range(0, 4):
                res[i + 28 + self.name_length] = int(ip_part[i])
            return bytes(res)
        else:
            print('Intercepted')
            self.RCODE = 5
            res = bytearray(32 + self.name_length)
            res[0] = self.ID >> 8
            res[1] = self.ID % 256
            res[2] = (self.QR << 7) + (self.Opcode << 3) + (self.AA << 2) + (self.TC << 1) + self.RD
            res[3] = (self.RA << 7) + (self.Z << 4) + self.RCODE
            res[4] = self.QDCOUNT >> 8
            res[5] = self.QDCOUNT % 256
            res[6] = self.ANCOUNT >> 8
            res[7] = self.ANCOUNT % 8
            res[8] = self.NSCOUNT >> 8
            res[9] = self.NSCOUNT % 8
            res[10] = self.ARCOUNT >> 8
            res[11] = self.ARCOUNT % 8
            for i in range(12, 16 + self.name_length):
                res[i] = self.data[i]
            res[16 + self.name_length] = 0xc0
            res[17 + self.name_length] = 0x0c
            res[18 + self.name_length] = 0
            res[19 + self.name_length] = 1
            res[20 + self.name_length] = 0
            res[21 + self.name_length] = 1
            for i in range(22 + self.name_length, 26 + self.name_length):
                res[i] = 0
            res[26 + self.name_length] = 0
            res[27 + self.name_length] = 4
            ip_part = ip.split('.')
            for i in range(0, 4):
                res[i + 28 + self.name_length] = int(ip_part[i])
            return bytes(res)


if __name__ == '__main__':
    cache_file = 'example.txt'
    name_server=('223.5.5.5',53)
    relay_server = DNS_Relay_Server(cache_file,name_server)   #构造一个DNS_Relay_Server实例
    relay_server.run()