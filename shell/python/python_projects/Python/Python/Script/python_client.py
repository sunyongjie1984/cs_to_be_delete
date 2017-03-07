from socket import *

HOST = 'localhost'
PORT = 21567
BUFSIZ = 1024
ADDR = (HOST, PORT)

tcpClientSock = socket(AF_INET, SOCK_STREAM)

tcpClientSock.connect(ADDR)

while 1:
    data = raw_input('>')
    if not data:
        print 'null data'
        break
    tcpClientSock.send(data)
    data = tcpClientSock.recv(BUFSIZ)
    if not data:
        print 'recv null'
        break
    print data
tcpClientSock.close()
