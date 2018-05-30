#include "a.h"

#include <cstdio>
#include <cstdarg>

namespace
{
//#define DEBUG
void write_log(const char* format, ...)
{
#ifdef DEBUG
    va_list args;
    va_start(args, format);

    vprintf(format, args);

    va_end(args);
#endif
}
}

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
    write_log("simpleFunctionHandle(Handle_A handle)\n");
    if (!handle.IsNull()) {
        printf("Value = %s\n", handle->Value().c_str());
        handle->DoSomething();
    }
    else {
        write_log("handle is null\n");
    }
}

void simpleFunctionHandleRef(Handle_A& handle)
{
    write_log("simpleFunctionHandleRef(Handle_A& handle)\n");
    if (!handle.IsNull()) {
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

Handle_A getHandleA()
{
    Handle_A ah = new A();
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
