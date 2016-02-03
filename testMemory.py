from standard import A,Handle_A, simpleFunction

def myfun(mya):
    ha = mya.handle()
    count = mya.RefCount()
    print "Refcount after ha=handle():", count

    print "\nCreate new handle:"
    ha2 = Handle_A(mya)
    count = mya.RefCount()
    print "Refcount after creating new handle ha2:", count

    apointer = ha.GetObject()
    count = apointer.RefCount()
    print "Refcount after getting object from handle ha:", count
    apointer2 = ha2.GetObject()
    count = apointer2.RefCount()
    print "Refcount after getting object from handle ha2:", count


a = A()
print "Call myfun"
myfun(a)

# call a function that requires a handle
simpleFunction(a.handle())

# a should not be destructed, as it always holds a own handle to itself
print "After call myfun"
print "Exit program"

