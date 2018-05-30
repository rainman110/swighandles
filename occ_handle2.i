#if !defined(SHARED_PTR_DISOWN)
#define SHARED_PTR_DISOWN 0
#endif

%fragment("SWIG_null_deleter_python", "header", fragment="SWIG_null_deleter") {
%#define SWIG_NO_NULL_DELETER_SWIG_BUILTIN_INIT
}

%define WRAP_OCC_TRANSIENT_TYPE(CONST, TYPE)

// This two functions are just for backwards compatibilty
%extend TYPE {
%pythoncode {
    def GetHandle(self):
        return self

    def GetObject(self):
        return self
   }
}

%naturalvar TYPE;
%naturalvar Handle_ ## TYPE;

%feature("ref")   TYPE "$this->IncRefs();"
%feature("unref") TYPE "$this->DecRefs();"


%enddef


%define %wrap_handle(TYPE)
%nodefaultctor Handle_ ## TYPE;
%ignore Handle_ ## TYPE; 
%ignore Handle_ ## TYPE::operator=; 
%feature("smartptr", noblock=1) TYPE { Handle_ ## TYPE }
#define SWIGEMPTYHACK
WRAP_OCC_TRANSIENT_TYPE(SWIGEMPTYHACK, TYPE)
WRAP_OCC_TRANSIENT_TYPE(const, TYPE)
%enddef