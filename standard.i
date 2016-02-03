%module standard

%{
#include <a.h>
%}

%ignore Handle_A::operator=(const Handle_A &h);

/* We add a handle to the shadow class of
 * A that is used to take care of the objects
 * lifetime and can be used for functions using
 * this handle
 */
%pythonappend A::A() %{
   # create handle that takes care of lifetime
   self.thisHandle = Handle_A(self)
   self.thisown = False
%}

/*
 * Some functions require a handle as input
 * This function provides it
 */
%extend A{
%pythoncode {
    def handle(self):
        return self.thisHandle
   }
}

%include "a.h"
