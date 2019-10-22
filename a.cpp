#include "a.h"

#include <cstdio>
#include <cstdarg>


A::A(const std::string& v)
    : Standard_Transient()
    , value(v)

{
    write_log("A::A(int v = %s)\n", v.c_str());
}

std::string A::Value() const
{
    return value;
}

void A::DoSomething() const
{
    printf("A::do_something()\n");
}

void simpleFunctionHandle(Handle_A handle)
{
    write_log("simpleFunctionHandle(handle<A> handle)\n");
    if (handle) {
        printf("Value = %s\n", handle->Value().c_str());
        handle->DoSomething();
    }
    else {
        write_log("handle is null\n");
    }
}

void simpleFunctionHandleRef(const Handle(A)& handle)
{
    write_log("simpleFunctionHandleRef(handle<A>& handle)\n");
    if (handle) {
        printf("Value = %s\n", handle->Value().c_str());
        handle->DoSomething();
    }
    else {
        write_log("handle is null\n");
    }
}

void simpleFunctionByRef(const A& a)
{
    write_log("simpleFUnctionByRef(constA&)\n");
    printf("Value = %s\n", a.Value().c_str());
}

Handle(A) getHandleA()
{
    Handle(A) ah(new A());
    return ah;
}

A getCopyA()
{
    return A("BLUBB");
}

A* createA()
{
    return new A("CreatedA");
}

ABuilder::~ABuilder()
{
    write_log("ABuilder::~ABuilder()\n");
}

Handle_A& ABuilder::GetHandleARef()
{
    write_log("ABuilder::GetHandleARef\n");
    return ah;
}

handle<A> getNone()
{
    return handle<A>();
}

Handle_Standard_Transient getHandleATransient()
{
    return new A("HandleTransientA");
}

handle<Standard_Transient> getHandleTransient()
{
    return handle<Standard_Transient>(new Standard_Transient());
}

void doWithC(const C &)
{
    printf("Do With C called\n");
}

void createAHandle(handle<A>& out)
{
    out = (new A("CreateHandleA"));
}

handle<C> getC()
{
    return new C("This is C");
}

C::~C(){}
D::~D(){}
