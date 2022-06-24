import socket
import sys

s = socket.socket()

port = 9898

s.connect(('192.168.6.4', port))

file = open("sample.txt", "rb")
SendData = file.read(1024)


while SendData:
    print("\n\n################## Below message is received from server ################## \n\n ", s.recv(1024).decode("utf-8"))

    s.send(SendData)
    SendData = file.read(1024)      


s.close()

