from socket import *

serverName = 'localhost'
serverPort = 12000
clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((serverName,serverPort))
sentence = input('Input lowercase sentence:')
clientSocket.send(str.encode(sentence))
modifiedSentence = clientSocket.recv(1024)
print ('From Server: ', bytes.decode(modifiedSentence))
clientSocket.close()
