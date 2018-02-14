
#Insert priv Key data
d = 59245909400328096229476030812807141613893493155744988131060136125721359659265
N = 73375270033624401281084918483265144282147683107270964016512019718595995392361

def pkcs1_unpad(text):
    if len(text) > 0 and text[0] == '\x02':
        # Find end of padding marked by nul
        pos = text.find('\x00')
        if pos > 0:
            return text[pos+1:]
    return None

def decrypt( fname,d,N ):
	val = ""
	f = open(fname, "rb")
	try:
	    byte = f.read(1)
	    while byte != "":
		# Do stuff with byte.
		val = val+byte
		byte = f.read(1)

	finally:
	    f.close()


	msg  = int(val.encode('hex'),16)


	res = pow(msg,d,N)
#	return pkcs1_unpad((hex(res).zfill(64)))
	return str(hex(res))[2:-1].split('00')[-1].decode('hex')


print decrypt("part1.enc",d,N),
print decrypt("part2.enc",d,N),
print decrypt("part3.enc",d,N),

