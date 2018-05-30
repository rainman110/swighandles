#include "a.h"

#include <cstdio>
#include <cstdarg>

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

Standard_Transient::Standard_Transient()
{
    write_log("A::A()\n");
    count = 0;
    RefCount();
    alive = new bool(true);
}

Standard_Transient::Standard_Transient(const Standard_Transient& other)
{
    write_log("A::A(const A&)\n");
    count = 0;
    alive = new bool(true);
}

A::A(const std::string& v)
    : Standard_Transient()
    , value(v)

{
    write_log("A::A(int v = %s)\n", v.c_str());
}

Standard_Transient::~Standard_Transient()
{
    write_log("A::~A()\n");

    *alive = false;
    delete alive;
    alive = NULL;
}

void A::DoSomething() const
{
    printf("A::do_something()\n");
}

int Standard_Transient::RefCount()
{
    write_log("  A::RefCount()=%d\n", count);
    return count;
}

void Standard_Transient::IncRefs()
{
    write_log("  A::IncRefs()\n");
    count++;
    RefCount();
}

void Standard_Transient::DecRefs()
{
    write_log("  A::DecRefs()\n");
    count--;
    RefCount();
}

std::string A::Value() const
{
    return value;
}

Standard_Transient& Standard_Transient::operator=(const Standard_Transient& other)
{
    write_log("A::operator=(const A& other)\n");
    *this->alive = *other.alive;
    return *this;
}

Handle_Standard_Transient::Handle_Standard_Transient()
    : a(0)
{
    write_log("Handle_A::Handle_A()\n");
}

Handle_Standard_Transient::Handle_Standard_Transient(Standard_Transient* a)
{
    write_log("Handle_A::Handle_A(Handle_A* h)\n");
    this->a = a;
    if (a) {
        a->IncRefs();
    }
}

Handle_Standard_Transient::Handle_Standard_Transient(const Handle_Standard_Transient& h)
{
    write_log("Handle_A::Handle_A(const Handle_A &h)\n");
    a = h.a;
    if (a) {
        a->IncRefs();
    }
}

Handle_Standard_Transient& Handle_Standard_Transient::operator=(const Handle_Standard_Transient& h)
{
    write_log("Handle_A &Handle_A::operator=(const Handle_A &h)\n");
    a = h.a;
    if (a) {
        a->IncRefs();
    }
    return *this;
}

bool Handle_Standard_Transient::IsNull() const
{
    return a == NULL;
}

Handle_Standard_Transient::~Handle_Standard_Transient()
{
    write_log("Handle_A::~Handle_A()\n");
    if (a) {
        a->DecRefs();
        if (a->RefCount() == 0) {
            write_log("Delete A from Handle_A::~Handle_A()\n");
            delete a;
            a = NULL;
        }
    }
}

Standard_Transient* Handle_Standard_Transient::Access()
{
    return a;
}

Standard_Transient* Handle_Standard_Transient::operator->()
{
    return Access();
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
