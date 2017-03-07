from socket import *
from time import time, ctime

HOST = ''
PORT = 21567
BUFSIZ = 1024
ADDR = (HOST, PORT)

tcpSvrSock = socket(AF_INET, SOCK_STREAM)
tcpSvrSock.bind(ADDR)
tcpSvrSock.listen(5)

while 1:
    print 'waiting for connection .....'
    tcpClientSock, addr = tcpSvrSock.accept()
    print '......connected from:', addr

    while 1:
        data = tcpClientSock.recv(BUFSIZ)
        if not data:
            break
        tcpClientSock.send('[%s] %s' %(ctime(time()), data))
    tcpClientSock.close()
tcpSvrSock.close