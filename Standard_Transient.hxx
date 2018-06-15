#ifndef STANDARD_TRANSIENT_H
#define STANDARD_TRANSIENT_H

typedef int Standard_Integer; 

/**
 * @brief This is a reference counted base class
 * In OpenCASCADE many classes are derived from it
 */
class Standard_Transient
{
    friend class Handle_Standard_Transient;

public:
    Standard_Transient(const Standard_Transient&);
    Standard_Transient();
    virtual ~Standard_Transient();
    Standard_Transient& operator=(const Standard_Transient&);

    int RefCount();

private:
    void IncRefs();
    void DecRefs();

private:
    volatile Standard_Integer count;

    bool* alive;
};

/**
 * @brief Handle_Standard_Transient is a smart
 * pointer to class Standard_Transient as similarly done
 * in the OpenCASCADE framework
 *
 * Usage: Handle_A a = new A();
 */
class Handle_Standard_Transient
{
public:
    Handle_Standard_Transient();
    Handle_Standard_Transient(Standard_Transient* a);
    Handle_Standard_Transient(const Handle_Standard_Transient& h);
    virtual ~Handle_Standard_Transient();

    Handle_Standard_Transient& operator=(const Handle_Standard_Transient& h);

    bool IsNull() const;

    Standard_Transient* Access();
    const Standard_Transient* Access() const;
    Standard_Transient* operator->();
    Standard_Transient& operator*();
    
    const Standard_Transient& operator*() const;
    
    static Handle_Standard_Transient DownCast(const Handle_Standard_Transient& t) {
        return const_cast<Handle_Standard_Transient&>(t);
    }

private:
    Standard_Transient* a;
};

template <class T>
class handle : public Handle_Standard_Transient
{
public:
    handle()
        : Handle_Standard_Transient()
    {
    }
    handle(T* t)
        : Handle_Standard_Transient(t)
    {
    }

    handle(Handle_Standard_Transient& other)
        : Handle_Standard_Transient(other)
    {
    }

    static handle<T> DownCast(const Handle_Standard_Transient& t)
    {
        return dynamic_cast<T*>(const_cast<Standard_Transient*>(t.Access()));
    }

    T* operator->()
    {
        return static_cast<T*>(Access());
    }

    operator Handle_Standard_Transient&()
    {
        return *this;
    }
};


#define Handle(CLS) Handle_##CLS

#define DEFINE_STANDARD_HANDLE(C1, C2) typedef handle<C1> Handle_ ## C1;
#define IMPLEMENT_STANDARD_HANDLE(C1,C2)


#endif // STANDARD_TRANSIENT_H
