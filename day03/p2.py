import sys

lines = []

for line in sys.stdin:
    lines.append(line.split("\n")[0])

N = len(lines)
size = len(lines[0])
atual = lines[:]

num = N
j = 0
while (num > 1 and j < size):
    n0 = n1 = 0
    for i in range(num):
        if atual[i][j] == '1':
            n1++
        else:
            n0++
    char = '1' if (n1 >= n0) else '0'
    k = 0
    for i in range(num):
        if atual[i][j] == char:
            atual[k++] = atual[i]
    num = k

