import socket

addr = ("example.com", 17) # Change server address

conn = socket.create_connection(addr)
quote = conn.recv(4096) # Read up to 4096 bytes

print(quote.decode("utf-8"))
