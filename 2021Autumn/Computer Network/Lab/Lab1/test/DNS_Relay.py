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

    def handle(self,server_socket:socket.socket,data,addr):
        RecvDp = DNS_Packege(data)
        if RecvDp.QR == 0:      # 查询报文
            print('查询报文：'+RecvDp.name)
            if RecvDp.name in self.url_ip:
                ip = self.url_ip[RecvDp.name]
                send_data = RecvDp.generate_response(ip, ip=='0.0.0.0')
                server_socket.sendto(send_data, addr)
                print('在缓存中，回复报文：'+ip)
            else:
                self.trans[RecvDp.ID] = addr
                server_socket.sendto(data, ('202.38.64.56', 53))
                print('不在缓存中，转发：'+RecvDp.name)
        elif RecvDp.QR == 1:      # 响应报文
            addr = self.trans[RecvDp.ID]
            server_socket.sendto(data, addr)
            print('收到响应，回复查询ID：'+str(RecvDp.ID))

class DNS_Packege:        #一个DNS Frame实例，用于解析和生成DNS帧
    def __init__(self,data):
        self.data = bytearray(data)
        Msg_arr = bytearray(data)
        #ID
        self.ID = (Msg_arr[0] << 8) + Msg_arr[1]
        # FLAGS
        self.QR = Msg_arr[2] >> 7
        self.Opcode = (Msg_arr[2] & 0b01111000) >> 3
        self.AA = (Msg_arr[2] & 0b00000100) >> 2
        self.TC = (Msg_arr[2] & 0b00000010) >> 1
        self.RD = (Msg_arr[2] & 0b00000001)
        # 资源记录数量
        self.QDCOUNT = (Msg_arr[4] << 8) + Msg_arr[5]
        self.ANCOUNT = (Msg_arr[6] << 8) + Msg_arr[7]
        self.NSCOUNT = (Msg_arr[8] << 8) + Msg_arr[9]
        self.ARCOUNT = (Msg_arr[10] << 8) + Msg_arr[11]
        #query内容解析
        i = 12
        name = ''
        while True:
            length = int(Msg_arr[i])
            if length == 0:
                break
            else:
                if i != 12:
                    name += '.'
                for j in range(i + 1, i + length + 1):
                    name += chr(Msg_arr[j])
                i += length + 1
        self.name = name
        self.name_length = len(name) + 2

    def generate_response(self,ip:str,Intercepted):
        self.QR = 1
        self.AA = 0
        self.RA = 1
        self.Z = 0
        self.ANCOUNT = 1
        self.NSCOUNT = 0
        self.ARCOUNT = 0
        if not Intercepted:
            self.RCODE = 0
        else:
            self.RCODE = 5
            print('发生截断查询')
        res = bytearray(32 + self.name_length)
        res[0] = self.ID >> 8
        res[1] = self.ID % 256
        res[2] = (self.QR << 7) + (self.Opcode << 3) + (self.AA << 2) + (self.TC << 1) + self.RD
        res[3] = (self.RA << 7) + (self.Z <<  4) + self.RCODE
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
            res[i+28+self.name_length] = int(ip_part[i])

        return bytes(res)
   

if __name__ == '__main__':
    cache_file = 'example.txt'
    name_server=('223.5.5.5',53)
    relay_server = DNS_Relay_Server(cache_file,name_server)   #构造一个DNS_Relay_Server实例
    relay_server.run()