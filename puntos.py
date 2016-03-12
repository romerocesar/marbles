ll = []
for z in range(11):
    l = []
    for x in range(11):        
        p = "{%s, %s, %s}" % (x, 2, z)
        l.append(p)

    ll.append("{" + ", ".join(l) + "}")

print ",\n".join(ll)
