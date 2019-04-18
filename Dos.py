import socket
import struct
import time

TCP_IP = '127.0.0.1'
TCP_PORT = 2000
BUFFER_SIZE = 256
MESSAGE = "Timerlan:127.0.0.1:2017:"
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP, TCP_PORT))
i = 0;
while True:
    packed_int = struct.pack("I", socket.htonl(1))  # i = int, I = unsigned int
    try:
        s.send(packed_int)
        s.send(MESSAGE.encode())
    except:
        s.close()
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.connect((TCP_IP, TCP_PORT))
        i+=1
    print(i)
    time.sleep(0.000001)
    i += 1




