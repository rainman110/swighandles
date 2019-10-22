%module standard

%include "std_string.i"
%include "occ_handle1.i"

%{
#include "a.h"
%}

namespace opencascade{
template <typename T>
class handle;
}
#define Handle(CLS) opencascade::handle<CLS>
#define DEFINE_STANDARD_HANDLE(A, ___) typedef opencascade::handle<A> Handle_ ## A;

%wrap_handle(Standard_Transient)
%wrap_handle(A)
%wrap_handle(C)
%add_missing_handle(D, A)
%wrap_handle(D)

%include "Standard_Transient.hxx"
%include "a.h"

%make_alias(A)
%make_alias(D)
