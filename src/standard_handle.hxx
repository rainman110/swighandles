#ifndef STANDARD_HANDLE_HXX
#define STANDARD_HANDLE_HXX

#include <type_traits>

//#define DEBUG

void write_log(const char* format, ...);

/**
 * @brief Handle_Standard_Transient is a smart
 * pointer to class Standard_Transient as similarly done
 * in the OpenCASCADE framework
 *
 * Usage: Handle_A a = new A();
 */


namespace opencascade
{

template <class T>
class handle
{
public:
    handle()
        : a(0)
    {
        write_log("Handle_Standard_Transient::Handle_Standard_Transient()\n");
    }

    handle(T* a)
    {
        write_log("Handle_Standard_Transient::Handle_Standard_Transient(Handle_Standard_Transient* h)\n");
        this->a = a;
        if (a) {
            a->IncRefs();
        }
    }

    handle(const handle& h)
    {
        write_log("Handle_Standard_Transient::Handle_Standard_Transient(const Handle_Standard_Transient &h)\n");
        a = h.a;
        if (a) {
            a->IncRefs();
        }
    }


    template <class T2, typename = typename std::enable_if <std::is_base_of <T, T2>::value>::type>
    handle(const handle<T2>& h)
    {
        write_log("Handle_Standard_Transient::Handle_Standard_Transient(const Handle_Standard_Transient &h)\n");
        a = h.a;
        if (a) {
            a->IncRefs();
        }
    }

    template <class T2>
    static typename std::enable_if<std::is_base_of<T2, T>::value, handle>::type
    DownCast(const handle<T2>& t)
    {
        return dynamic_cast<T*>(const_cast<T2*>(t.Access()));
    }

    T* operator->()
    {
        return Access();
    }

    const T* operator->() const
    {
        return Access();
    }

    const T& operator*() const
    {
        return *a;
    }

    T& operator*()
    {
        return *a;
    }


    bool IsNull() const
    {
        return a == nullptr;
    }

    operator bool() const {
        return !IsNull();
    }

    handle& operator=(const handle& h)
    {
        write_log("Handle_Standard_Transient &Handle_Standard_Transient::operator=(const Handle_Standard_Transient &h)\n");
        a = h.a;
        if (a) {
            a->IncRefs();
        }
        return *this;
    }

    template <typename T2>
    handle& operator=(const handle<T2>& h)
    {
        write_log("Handle_Standard_Transient &Handle_Standard_Transient::operator=(const Handle_Standard_Transient &h)\n");
        a = h.a;
        if (a) {
            a->IncRefs();
        }
        return *this;
    }


    ~handle()
    {
        write_log("Handle_Standard_Transient::~Handle_Standard_Transient()\n");
        if (a) {
            a->DecRefs();
            if (a->RefCount() == 0) {
                write_log("Delete Standard_Transient from Handle_Standard_Transient::~Handle_Standard_Transient()\n");
                delete a;
                a = nullptr;
            }
        }
    }

    template <class T2> friend class handle;

protected:
    T* Access() {
        return a;
    }
    const T* Access() const {
        return a;
    }


    T* a;

};

} // namespace opencascade
#define Handle(CLS) opencascade::handle<CLS>


// This switches between win and linux behaviour
#if 1

#define DEFINE_STANDARD_HANDLE(C1, __) class C1; class Handle_ ## C1 : public Handle(C1) \
{ \
public: \
  Handle_ ## C1() {} \
  Handle_ ## C1(const handle<C1>& other) : Handle(C1)(other) {} \
  template <class T2, typename = typename std::enable_if <std::is_base_of <C1,T2>::value>::type> \
  inline Handle_ ## C1(const handle<T2>& theOther) : Handle(C1)(theOther) {} \
  template <class T2, typename = typename std::enable_if <std::is_base_of <C1,T2>::value>::type> \
  inline Handle_ ## C1(T2* theOther) : Handle(C1)(theOther) {} \
  template<typename T> inline Handle_ ## C1& operator=(T theOther) { Handle(C1)::operator=(theOther); return *this; } \
};

#else
#define DEFINE_STANDARD_HANDLE(C1, __) using Handle_ ## C1 = handle<C1>;
#endif

#define IMPLEMENT_STANDARD_HANDLE(__, ___)




#endif // STANDARD_HANDLE_HXX
