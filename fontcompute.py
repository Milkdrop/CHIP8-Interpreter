f = open("font.txt", "r").read().split("\n\n")
buff = ""

for letter in f:
	letter = letter.split("\n")
	for line in letter:
		nb = 0
		pwr = 128
		for char in line:
			if (char == '#'):
				nb += pwr
			pwr /= 2
		if (nb < 16):
			buff += "\\x0" + hex(nb)[2:]
		else:
			buff += "\\x" + hex(nb)[2:]

print (buff)