var1  = 33
var2  = 4
num   = 64326
inc   = 116
iters = 0

# count total number of loop iterations
while var2 < num:
    iters += 1
    var2  += inc


flag = var1 + iters
flag = hex(flag)

print("The flag is {}".format(flag))
