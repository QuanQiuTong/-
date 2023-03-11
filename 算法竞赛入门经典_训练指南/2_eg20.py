from numpy import *
f = zeros((22, 22),unsignedinteger[_64Bit])
f[1, 0] = 1
for i in range(2, 22):
    for j in range(0, i):
        f[i, j] = f[i-1, j]
        if j > 0:
            f[i,j] += f[i - 1,j - 1] * (i - 1)
while 1:
    n, k = input().split()
    n = int(n)
    k = int(k)
    if n == 0 and k == 0:
        break
    print(f[n,k])
