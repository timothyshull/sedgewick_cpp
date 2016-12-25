s = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}

x = 20
y = 10
tmp = x * sum(s) == sum(x * y for y in s)
print('tmp: {0}'.format(tmp))
s_sum = sum(x * y for y in s)
print('s_sum: {0}'.format(s_sum))

s2 = (x * y for y in s)
for p in s2:
    print(p)


def f(a):
    return a * 3


m = 10
n = 29
sum_2 = sum(f(i) for i in range(m, n + 1))
print('sum_2 {0}'.format(sum_2))

s3 = 0
for i in range(m, n + 1):
    s3 += f(i)


def g(a):
    return a * 4

seq = range(m, n)
s4 = sum(f(i) for i in seq) + sum(g(i) for i in seq)
print('s4: {0}'.format(s4))

# use the math module
