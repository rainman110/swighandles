import standard

a = standard.A()
t = standard.Standard_Transient()

at = standard.getHandleATransient()

b = standard.Handle_A(a)

print (b)
b.Value()
print (standard.Handle_A.DownCast(a))
print (standard.Handle_A_DownCast(a))
print (standard.A.DownCast(a))

print (standard.A.DownCast(t))
print (standard.A.DownCast(at))

print (standard.A(a))

print (isinstance(a, standard.Handle_A))
print (isinstance(a, standard.Handle_Standard_Transient))

c = standard.C()
print (isinstance(c, standard.Handle_Standard_Transient))
standard.doWithC(c)
