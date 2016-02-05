from standard import A,Handle_A, ABuilder

# works
ah = ABuilder().GetHandleACopy()
ah.GetObject().DoSomething()

# 2nd line crashes since ABuilder is destroyed and cleans the handle
ah2 = ABuilder().GetHandleARef()
ah2.GetObject().DoSomething()

# crashes since handleCopy is destroyed after GetObject call
ABuilder().GetHandleACopy().GetObject().DoSomething()

# even this leads to a crashes as ABuilder is cleaned before copy construction
ah3 = Handle_A(ABuilder().GetHandleARef())
ah3.GetObject().DoSomething()

print "exit"
