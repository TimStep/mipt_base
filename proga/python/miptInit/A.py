x, y, r = list(map(int, input().split()))

if x**2 + y**2 <= r**2:
    print('YES')
else:
    print('NO')
