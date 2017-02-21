#!/usr/bin/env python
from socket import *
import sys

if __name__ == '__main__':
    if len(sys.argv) > 1:
        try:
            HOST=sys.argv[1]
            PORT = 8080
            BUFSIZ = 1024            # buffer size
            ADDR = (HOST, PORT)
            tcpCliSock = socket(AF_INET, SOCK_STREAM)   # Create a socket
            tcpCliSock.connect(ADDR)                    # Connect with the server
            while True:
                cmd = raw_input('input cmd : ')
                if (cmd == 'quit'):
                    break
                tcpCliSock.send(cmd)
            tcpCliSock.close()
        except:
            print "Usage: ",argv[0]," IP_add_of_server"
