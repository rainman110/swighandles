#include <iostream>

#include <Standard_Transient.hxx>
#include "a.h"

int main()
{

    handle<A> ah = new A("Hallo");
    handle<Standard_Transient> th(ah);

    handle<A> ch = new C("blubb");
    simpleFunctionByRef(*ch);

    Handle(A) aa = new A("Welt");

    Handle_A aaa = aa;

    Handle_A bbb = new A("Welt");

    handle<A> ccc = bbb;
    Handle(A) ddd = bbb;
    Handle(A) eeee = ch;
    Handle_A ffff = ch;

    return 0;
}
