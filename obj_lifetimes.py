from standard import A, ABuilder, getCopyA, simpleFunctionByRef, simpleFunctionHandle, simpleFunctionHandleRef, getHandleA, createA


# works
ah = ABuilder().GetHandleACopy()
ah.GetObject().DoSomething()

# It is irrelevant, whether ah2 is a handle or not
# is just works
ah2 = ABuilder().GetHandleARef()
ah2.GetObject().DoSomething()
ah2.GetHandle().DoSomething()
ah2.DoSomething()

# All those should not crash!
ABuilder().GetHandleACopy().GetObject().DoSomething()
ABuilder().GetHandleACopy().DoSomething()
ABuilder().GetHandleARef().DoSomething()

a = getCopyA()
del a

builder = ABuilder()
b = builder.GetHandleARef()
# The call to  RefCount() increases the refcount by one temporaly
# as the Handle_A is converted internally into Handle_Transient
print ("RefCount b (must be 3): %d" % b.RefCount())
del builder
print ("RefCount b (must be 2): %d" % b.RefCount())

builder = ABuilder()
b = builder.GetHandleACopy()
print ("RefCount b (must be 3): %d" % b.RefCount())
del builder
print ("RefCount b (must be 2): %d" % b.RefCount())

# We can put b into both functions, it just
# converts into the correct type
b.setValue("Welt1")
simpleFunctionByRef(b)
b.setValue("Welt2")
simpleFunctionHandle(b)
b.setValue("Welt2")
simpleFunctionHandleRef(b)

del b
del ah2
del ah

# test get handle by value
d = getHandleA()
d.DoSomething()

print (d.Value())
del d

# test get a by value
e = createA()
e.DoSomething()
print (e.Value())

del e
f = ABuilder().GetARef()
print (f.Value())
print (f.RefCount())

del f

print ("exit!!!")
# everything should be cleaned up to this point
