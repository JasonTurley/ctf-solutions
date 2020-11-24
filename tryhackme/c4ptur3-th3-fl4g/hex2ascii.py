# Translates the hex characters to ascii

hex = "68 65 78 61 64 65 63 69 6d 61 6c 20 6f 72 20 62 61 73 65 31 36 3f".split()

for h in hex:
	print(chr(int(h, 16)), end="")

print()
