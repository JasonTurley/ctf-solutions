#!/usr/bin/python

def count_nums():
    total = 0
    with open('data.dat', 'r') as f:
        for line in f:
            n0 = 0
            n1 = 0

            for c in line:
                if c == '0':
                    n0 += 1

                elif c == '1':
                    n1 += 1

            if n0 % 3 == 0 or n1 % 2 == 0:
                total += 1

    return total

if __name__ == '__main__':
    print(count_nums())
