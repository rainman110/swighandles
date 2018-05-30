#ifndef A_H
#define A_H

#include "Standard_Transient.h"

#include <cstdio>
#include <memory>
#include <string>

#define Handle(CLS) Handle_##CLS

class Handle_A;

class A : public Standard_Transient
{
public:
    A()
        : value("NewA")
    {
    }

    A(const std::string& s);

    // TODO: into derived class
    void DoSomething() const;

    std::string Value() const;
    void setValue(const std::string& s)
    {
        value = s;
    }

private:
    std::string value;
};

class Handle_A : public Handle_Standard_Transient
{
public:
    Handle_A()
        : Handle_Standard_Transient()
    {
    }
    Handle_A(A* a)
        : Handle_Standard_Transient(a)
    {
    }

    Handle_A(Handle_Standard_Transient& other)
        : Handle_Standard_Transient(other)
    {
    }

    A* Access()
    {
        return (A*)Handle_Standard_Transient::Access();
    }

    A* operator->()
    {
        return Access();
    }

    operator Handle_Standard_Transient&()
    {
        return *this;
    }
};

/**
 * A class that mimics e.g. GeomAPI_PointsToBSpline
 */
class ABuilder
{
public:
    ABuilder()
        : ah(new A("From Builder"))
    {
    }
    ~ABuilder();

    Handle_A& GetHandleARef();

    Handle_A GetHandleACopy()
    {
        return ah;
    }

    A& GetARef()
    {
        return a;
    }

private:
    Handle_A ah;
    A a;
};

/**
 * Simple function that requires a handle of a
 */
void simpleFunctionHandle(Handle_A handle);
void simpleFunctionHandleRef(Handle_A& handle);

void simpleFunctionByRef(const A& a);

Handle_A getHandleA();

A getCopyA();

A* createA();

#endif // A_H
