 # coding=<encoding coding=utf-8>
import socket
HOST = '192.168.0.112'    # The remote host
PORT = 8911             # The same port as used by the server
addr = (HOST,PORT)


PLCsock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
PLCsock.settimeout(1.2)            
PLCsock.connect(addr)
while True:
    data  = "hello this is python"
    # 数据收发和UDP基本一致
    PLCsock.send(data)  
    print("send data")

PLCsock.close()



