import socket

s = socket.socket()

PORT = 9898
print("\n Server is listing on port :", PORT, "\n")

s.bind(('', PORT))

s.listen(10)

file = open("recv.txt", "wb")
print("\n Copied file name will be recv.txt at server side\n")

while True:

    conn, addr = s.accept()

    msg = "\n\n|---------------------------------|\n Hi Client[IP address: "+ addr[0] + "], \n ֲֳ**Welcome to Server** \n -Server\n|---------------------------------|\n \n\n"    
    conn.send(msg.encode())

    RecvData = conn.recv(1024)
    while RecvData:
        file.write(RecvData)
        RecvData = conn.recv(1024)

    file.close()
    print("\n File has been copied successfully \n")

    conn.close()
    print("\n Server closed the connection \n")

    break
