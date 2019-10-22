#ifndef STANDARD_TRANSIENT_H
#define STANDARD_TRANSIENT_H

#include "standard_handle.hxx"

typedef int Standard_Integer; 

/**
 * @brief This is a reference counted base class
 * In OpenCASCADE many classes are derived from it
 */
class Standard_Transient
{
    template <typename T>
    friend class opencascade::handle;

public:
    Standard_Transient(const Standard_Transient&);
    Standard_Transient();
    virtual ~Standard_Transient();
    Standard_Transient& operator=(const Standard_Transient&);

    int RefCount();
    void IncrementRefCounter() {
        IncRefs();
    }

    static int GetNumAlive();

private:
    void IncRefs();
    void DecRefs();

private:
    volatile Standard_Integer count;

    bool* alive;

    static int n_alive;
};


#endif // STANDARD_TRANSIENT_H
