#include "Standard_Transient.hxx"

#include <cstdio>
#include <cstdarg>


int Standard_Transient::n_alive = 0;

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
    write_log("Standard_Transient::Standard_Transient()\n");
    count = 0;
    RefCount();
    alive = new bool(true);
    n_alive++;
}

Standard_Transient::Standard_Transient(const Standard_Transient& other)
{
    write_log("Standard_Transient::Standard_Transient(const Standard_Transient&)\n");
    count = 0;
    alive = new bool(true);
    n_alive++;
}

Standard_Transient::~Standard_Transient()
{
    write_log("Standard_Transient::~Standard_Transient()\n");

    *alive = false;
    delete alive;
    alive = nullptr;
    n_alive--;
}

int Standard_Transient::RefCount()
{
    write_log("  Standard_Transient::RefCount()=%d\n", count);
    return count;
}

int Standard_Transient::GetNumAlive()
{
    return n_alive;
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



