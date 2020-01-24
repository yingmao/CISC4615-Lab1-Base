import socket

server = socket.socket()             #initialize a socket object

server.bind(('localhost',6969))      #bind the ip

server.listen(5)                #listen, queue length 5


print("Waiting for clients----")

while True:
    conn,addr = server.accept()      #accept connection
    print(conn,addr)
    print("The data is coming")
    while True:
        data = conn.recv(1024)       #connect
        print("Received data from client：", data)
        if not data:
            print("client has lost")
            break
        conn.send(data.upper())     # return data

        if (data == 'bye') :
            break

server.close()                       #clode socket
