# import socket
#import random

#quotes = [
 #   "Never do today what you can do tomorrow",
  #  "Nobody lies on the internet",
   # "The cake is a lie"
#]

#server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#server.bind(("0.0.0.0", 17)) # Bind to port 17
#server.listen(5)

#while True:
 #   sock, addr = server.accept()
  #  quote = random.choice(quotes)
   # sock.send(f"{quote}\n")
   # sock.close()

#!/usr/bin/python

import socket
import threading
import random

class server(object):
	""" This class implements all the QOTD protocol"""
	def __init__(self, host, port):
		self.host = host
		self.port = port
		self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		self.socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
		self.socket.bind((self.host, self.port))
		self.linearray = []
		reader = open('../qotd.txt', 'r')
		for line in reader.readlines():
			self.linearray.append(line)

	def listen(self):
		self.socket.listen(10)
		while True:
			client, address = self.socket.accept()
			threading.Thread(target = self.listenToClient,args = (client,address)).start()

	def listenToClient(self, client, address):
		sendmsg = self.server()
		objectbyte = sendmsg.encode()
		client.send(objectbyte)
		client.close()

	def server(self):
		quote = random.choice(self.linearray)
		quote = quote.split("|")
		response = quote[0] + "\n" + quote[1]
		return response
try:
	myserv = server("0.0.0.0", 17)
	myserv.listen()
except KeyboardInterrupt:
	print(" pressed. Exiting...")
except:
	print("An error has occurred. Exiting...")
finally:
	reader.close()
