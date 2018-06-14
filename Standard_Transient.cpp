#include "Standard_Transient.hxx"

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

Standard_Transient::Standard_Transient()
{
    write_log("Standard_Transient::Standard_Transient()\n");
    count = 0;
    RefCount();
    alive = new bool(true);
}

Standard_Transient::Standard_Transient(const Standard_Transient& other)
{
    write_log("Standard_Transient::Standard_Transient(const Standard_Transient&)\n");
    count = 0;
    alive = new bool(true);
}

Standard_Transient::~Standard_Transient()
{
    write_log("Standard_Transient::~Standard_Transient()\n");

    *alive = false;
    delete alive;
    alive = NULL;
}

int Standard_Transient::RefCount()
{
    write_log("  Standard_Transient::RefCount()=%d\n", count);
    return count;
}

void Standard_Transient::IncRefs()
{
    write_log("  Standard_Transient::IncRefs()\n");
    count++;
    RefCount();
}

void Standard_Transient::DecRefs()
{
    write_log("  Standard_Transient::DecRefs()\n");
    count--;
    RefCount();
}

Standard_Transient& Standard_Transient::operator=(const Standard_Transient& other)
{
    write_log("Standard_Transient::operator=(const Standard_Transient& other)\n");
    *this->alive = *other.alive;
    return *this;
}

Handle_Standard_Transient::Handle_Standard_Transient()
    : a(0)
{
    write_log("Handle_Standard_Transient::Handle_Standard_Transient()\n");
}

Handle_Standard_Transient::Handle_Standard_Transient(Standard_Transient* a)
{
    write_log("Handle_Standard_Transient::Handle_Standard_Transient(Handle_Standard_Transient* h)\n");
    this->a = a;
    if (a) {
        a->IncRefs();
    }
}

Handle_Standard_Transient::Handle_Standard_Transient(const Handle_Standard_Transient& h)
{
    write_log("Handle_Standard_Transient::Handle_Standard_Transient(const Handle_Standard_Transient &h)\n");
    a = h.a;
    if (a) {
        a->IncRefs();
    }
}

Handle_Standard_Transient& Handle_Standard_Transient::operator=(const Handle_Standard_Transient& h)
{
    write_log("Handle_Standard_Transient &Handle_Standard_Transient::operator=(const Handle_Standard_Transient &h)\n");
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
    write_log("Handle_Standard_Transient::~Handle_Standard_Transient()\n");
    if (a) {
        a->DecRefs();
        if (a->RefCount() == 0) {
            write_log("Delete Standard_Transient from Handle_Standard_Transient::~Handle_Standard_Transient()\n");
            delete a;
            a = NULL;
        }
    }
}

Standard_Transient* Handle_Standard_Transient::Access()
{
    return a;
}

const Standard_Transient* Handle_Standard_Transient::Access() const
{
    return a;
}

Standard_Transient* Handle_Standard_Transient::operator->()
{
    return Access();
}

Standard_Transient& Handle_Standard_Transient::operator*()
{
    return *Access();
}

const Standard_Transient& Handle_Standard_Transient::operator*() const
{
    return *a;
}
