import socket

ClientSocket = socket.socket()
host = '192.168.6.4'
port = 8888

print('Waiting for connection')
try:
    ClientSocket.connect((host, port))
except socket.error as e:
    print(str(e))

Response = ClientSocket.recv(1024)
print(Response)
print("\nONLINE CALCULATOR CONSIST OF LOG,SQUARE ROOT OR EXPONENTIAL FUNCTION ONLY\n\n")

while True:

    mfunc=input("Enter 1 for Calculate LOG / 2 for Calculate Square Root / 3 for Calculate  Exponential Function. Enter (exit) to terminate: ")
    if(mfunc=='1'):
        result=input("Enter number:")
    elif(mfunc=='2'):
        result=input("Enter number:")
    elif(mfunc=='3'):
        result=input("Enter number:")
    elif(mfunc=='exit'):
        break

    message=mfunc+" "+result
    ClientSocket.send(str.encode(message))
    Response = ClientSocket.recv(1024)
    print(Response.decode('utf-8'))

ClientSocket.close()
