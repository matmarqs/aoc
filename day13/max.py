import sys

A = []
for line in sys.stdin:
    A.append([ int(i) for i in line.strip('\n').split(',')])

xs = [ a[0] for a in A ]
ys = [ a[1] for a in A ]

print('max(x) = ', max(xs))
print('may(y) = ', max(ys))
