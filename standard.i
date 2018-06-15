%module standard

%include "std_string.i"
%include "occ_handle1.i"
%include "std_shared_ptr.i"

%{
#include "a.h"
%}


#if 1
%wrap_handle(Standard_Transient)
%wrap_handle(A)
#else
%shared_ptr(Standard_Transient)
%shared_ptr(A)
#endif

%include "Standard_Transient.hxx"
%make_alias(Standard_Transient)
%include "a.h"
%make_alias(A)
