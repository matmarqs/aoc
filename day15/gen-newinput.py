import sys

def apply(f, x, n):
    for i in range(n):
        x = f(x)
    return x

def f(i):
    if (i < 9):
        return i+1
    else:
        return 1

def gen_newblock(block, n):
    len_i = len(block)
    len_j = len(block[0])
    newblock = []
    for i in range(len_i):
        line = []
        for j in range(len_j):
            line.append(apply(f, block[i][j], n))
        newblock.append(line)
    return newblock


def gen_table(block):
    table = []
    for i in range(5):
        line = []
        for j in range(5):
            line.append(gen_newblock(block, i+j))
        table.append(line)
    return table


def print_table(table):
    len_block_i = len(table[0][0])
    len_block_j = len(table[0][0][0])
    for a in range(5):
        for i in range(len_block_i):
            for b in range(5):
                for j in range(len_block_j):
                    print(table[a][b][i][j], end='')
            print()

L = []
block = []
for line in sys.stdin:
    nums = [int(i) for i in line.strip('\n')]
    block.append(nums)

table = gen_table(block)
#print(table)
print_table(table)
