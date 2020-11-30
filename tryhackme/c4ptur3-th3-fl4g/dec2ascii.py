# Translates decimal cdaracters to ascii

decimal = "85 110 112 97 99 107 32 116 104 105 115 32 66 67 68".split()

for d in decimal:
	print(chr(int(d, 10)), end="")

print()
