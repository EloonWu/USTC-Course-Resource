#!/usr/bin/python
# -*- coding: UTF-8 -*-
import socket
server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_socket.bind(('',53))
server_socket.setblocking(False)
#这里的blocking是什么含义，设置非阻塞和阻塞有什么区别呢？
print("------start-------")
while True:
    try:
        data, addr = server_socket.recvfrom(512)
        print("receive package from:")
        print(addr)
        print("DNS package:")
        print("type:",type(data))
        print("data:",data)

    except:
        continue