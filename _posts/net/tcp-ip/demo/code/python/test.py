from itertools import starmap

a = ["1","2","3","1","2","3","1","2","3","1","2","3"]
print(a[0::3])
print(a[1::3])
print(a[2::3])
l = list(zip(a[0::3],a[1::3],a[2::3]))
print(l)
l2 = list(zip(*l))
print(l2)

r2=list(map(lambda x,y,z:x+y+z,a[0::3],a[1::3],a[2::3]))
r3=list(starmap(lambda x,y,z:x+y+z,zip(a[0::3],a[1::3],a[2::3])))
r4=list(map(lambda x,y,z:x+y+z,a[0:],a[1:],a[2:]))
r5=list(starmap(lambda x,y,z:x+y+z,zip(a[0:],a[1:],a[2:])))
print(r2)
print(r3)
print(r4)
print(r5)