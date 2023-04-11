import socket

my_socket = socket.socket()
port = 5055

ip = ""
my_socket.connect((ip,port))

while True:
    msg=(my_socket.recv(1024).decode())
    print(msg,end='')
