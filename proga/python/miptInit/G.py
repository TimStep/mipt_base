st = input().split()

if st == []:
    print(st)
else:
    for w in range(len(st)):
        if len(st[w])<=3: st[w] = ''
    #st = [w for w in st if w != []]

#print(st)
print(' '.join(st))
