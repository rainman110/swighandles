%module standard

%include "std_string.i"
%include "occ_handle1.i"

%{
#include "a.h"
%}

%wrap_handle(Standard_Transient)
%wrap_handle(A)

%include "Standard_Transient.hxx"
%include "a.h"
