%module standard

%include "std_string.i"
%include "occ_handle1.i"
%include "std_shared_ptr.i"

%{
#include "a.h"
%}

%add_missing_handle(C, Standard_Transient)
%wrap_handle(Standard_Transient)
%wrap_handle(A)
%wrap_handle(C)

%include "Standard_Transient.hxx"
%include "a.h"

%make_alias(Standard_Transient)
%make_alias(A)
%make_alias(C)

