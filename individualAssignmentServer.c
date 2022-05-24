import socket
import random

quotes = [
    "Never do today what you can do tomorrow",
    "Nobody lies on the internet",
    "The cake is a lie"
]

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(("0.0.0.0", 17)) # Bind to port 17
server.listen(5)

while True:
    sock, addr = server.accept()
    quote = random.choice(quotes)
    sock.send(f"{quote}\n")
    sock.close()
