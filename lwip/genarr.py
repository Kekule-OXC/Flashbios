import sys

data = open(sys.argv[1]).read()

c_data = "".join(map(lambda a: "\\x%x" % ord(a), list(data)))

header = "HTTP/1.1 200 OK\\r\\nConnection: close\\r\\nServer: FlashBIOS/2.6\\r\\nContent-Type: %s\\r\\nContent-Length: %d\\r\\n\\r\\n" % (sys.argv[2], len(data))

open(sys.argv[1]+".h", "w").write('"'+header+c_data+'"\n')
