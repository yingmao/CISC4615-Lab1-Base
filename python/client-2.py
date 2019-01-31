import socket

client = socket.socket()

client.connect(('localhost',6969))  #connection

while True:
    msg = input(">>:").strip()
    if len(msg) == 0 :continue
    client.send(msg.encode())   # send data

    data = client.recv(1024)    # receive data

    print("Return:",data.decode())


client.close()
