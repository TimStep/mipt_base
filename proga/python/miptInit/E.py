st = input()

low = 0
upp = 0

'''
st.replace(" ", "")
print(st)
'''
for l in st:
    if ord(l) >= ord("A") and ord(l) <= ord("Z"): upp+=1
    if ord(l) >= ord("a") and ord(l) <= ord("z"): low+=1

print(upp, low)
