#ifndef A_H
#define A_H

#include "Standard_Transient.hxx"
#include "standard_handle.hxx"

#include <cstdio>
#include <string>

using namespace opencascade;

class A : public Standard_Transient
{
public:
    A()
        : value("NewA")
    {
    }
    
    A(const A& other) : Standard_Transient(other) {
        value = other.value;
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

DEFINE_STANDARD_HANDLE(A, Standard_Transient)

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

    handle<A> GetHandleACopy()
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

class C : public A
{
public:
    C() : A(){}
    C(const std::string& s) : A(s) {}
    virtual ~C();
};



class D : public A
{
public:
    D(const std::string& s) : A(s) {}
    virtual ~D();
};



DEFINE_STANDARD_HANDLE(Standard_Transient, Standard_Transient)
DEFINE_STANDARD_HANDLE(C, A)

void doWithC(const C&);

/**
 * Simple function that requires a handle of a
 */
void simpleFunctionHandle(Handle_A handle);
void simpleFunctionHandleRef(const Handle(A)& handle);

inline void acceptTransient(Handle(Standard_Transient) h)
{
    printf("acceptTransient\n");
}

void simpleFunctionByRef(const A& a);

Handle(A) getHandleA();

handle<A> getNone();

Handle_Standard_Transient getHandleATransient();

handle<Standard_Transient> getHandleTransient();

Handle(C) getC();

A getCopyA();

A* createA();

void createAHandle(handle<A>& a);

#endif // A_H
