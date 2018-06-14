#if !defined(SHARED_PTR_DISOWN)
#define SHARED_PTR_DISOWN 0
#endif


%{
#include <Standard_Transient.hxx>

// The following is an evil hack to edit the reference counter of Standard_Transient
template<typename Tag, typename Tag::type M>
struct Rob { 
  friend typename Tag::type get(Tag) {
    return M;
  }
};

// tag used to access A::count
struct Standard_Transient_f { 
  typedef volatile Standard_Integer Standard_Transient::*type;
  friend type get(Standard_Transient_f);
};

template struct Rob<Standard_Transient_f, &Standard_Transient::count>;

void IncRef(Standard_Transient& a) {
    a.*get(Standard_Transient_f()) += 1;
}

%}

%define WRAP_OCC_TRANSIENT_TYPE(CONST, TYPE)

// This two functions are just for backwards compatibilty
%extend TYPE {
%pythoncode {
    def GetHandle(self):
        return self

    def GetObject(self):
        return self

    def IsNull():
      return self is None
   }
}

%naturalvar TYPE;
%naturalvar Handle_ ## TYPE;

%feature("unref") TYPE 
    "(void)arg1; delete smartarg1;"


%typemap(out) CONST TYPE {
  Handle_ ## TYPE *smartresult = new Handle_ ## TYPE(new $1_ltype(($1_ltype &)$1));
  %set_output(SWIG_NewPointerObj(%as_voidptr(smartresult), $descriptor(Handle_ ## TYPE *), SWIG_POINTER_OWN));
}

%typemap(out) CONST TYPE * {
  Handle_ ## TYPE *smartresult = $1 ? new Handle_ ## TYPE($1) : 0;
  %set_output(SWIG_NewPointerObj(%as_voidptr(smartresult), $descriptor(Handle_ ## TYPE *), $owner | SWIG_POINTER_OWN));
}


// plain pointer
// Note: $disown not implemented by default as it will lead to a memory leak of the shared_ptr instance
%typemap(in) CONST TYPE * (void  *argp = 0, int res = 0, Handle_ ## TYPE tempshared, Handle_ ## TYPE *smartarg = 0) {
  int newmem = 0;
  res = SWIG_ConvertPtrAndOwn($input, &argp, $descriptor(Handle_ ## TYPE *), SHARED_PTR_DISOWN | %convertptr_flags, &newmem);
  if (!SWIG_IsOK(res)) {
    %argument_fail(res, "$type", $symname, $argnum); 
  }
  if (newmem & SWIG_CAST_NEW_MEMORY) {
    tempshared = *%reinterpret_cast(argp, Handle_ ## TYPE *);
    delete %reinterpret_cast(argp, Handle_ ## TYPE *);
    $1 = %const_cast(tempshared.operator->(), $1_ltype);
  } else {
    smartarg = %reinterpret_cast(argp, Handle_ ## TYPE *);
    $1 = %const_cast((smartarg ? smartarg->operator->() : 0), $1_ltype);
  }
}

// plain reference
%typemap(in) CONST TYPE & (void  *argp = 0, int res = 0, Handle_ ## TYPE tempshared) {
  int newmem = 0;
  res = SWIG_ConvertPtrAndOwn($input, &argp, $descriptor(Handle_ ## TYPE *), %convertptr_flags, &newmem);
  if (!SWIG_IsOK(res)) {
    %argument_fail(res, "$type", $symname, $argnum); 
  }
  if (!argp) { %argument_nullref("$type", $symname, $argnum); }
  if (newmem & SWIG_CAST_NEW_MEMORY) {
    tempshared = *%reinterpret_cast(argp, Handle_ ## TYPE *);
    delete %reinterpret_cast(argp, Handle_ ## TYPE *);
    $1 = %const_cast(tempshared.operator->(), $1_ltype);
  } else {
    $1 = %const_cast(%reinterpret_cast(argp, Handle_ ## TYPE *)->operator->(), $1_ltype);
  }
}

%typemap(out) Handle_ ## TYPE {
  Handle_ ## TYPE *smartresult = !$1.IsNull() ? new Handle_ ## TYPE($1) : 0;
  %set_output(SWIG_NewPointerObj(%as_voidptr(smartresult), $descriptor(Handle_ ## TYPE *), SWIG_POINTER_OWN));
}

// We return reference to handles as copy to handles as the lifetime
// is different in python than in c++ 
%typemap(out) Handle_ ## TYPE & {
  Handle_ ## TYPE *smartresult = !$1->IsNull() ? new Handle_ ## TYPE(*$1) : 0;
  %set_output(SWIG_NewPointerObj(%as_voidptr(smartresult), $descriptor(Handle_ ## TYPE *), SWIG_POINTER_OWN));
}

%typemap(out) CONST TYPE & {
  Handle_ ## TYPE *smartresult = new Handle_ ## TYPE($1);
  if (!$owner) {
      // he handle may not delete the object since it is owned by another class
      IncRef(*$1);
  }
  %set_output(SWIG_NewPointerObj(%as_voidptr(smartresult), $descriptor(Handle_ ## TYPE *), SWIG_POINTER_OWN));
}


%enddef

// This is the main macro used from usercode
// Do not call this on a handle class!
%define %wrap_handle(TYPE)
    %nodefaultctor Handle_ ## TYPE;
    // The handle class should be invisible/transparent in python 
    %ignore Handle_ ## TYPE;

    // deactivate warnings
    %ignore Handle_ ## TYPE::operator=; 
    %ignore TYPE::operator=;

    // Tell, that Handle_A is a smart pointer to A
    %feature("smartptr", noblock=1) TYPE { Handle_ ## TYPE }
    
    #define SWIGEMPTYHACK
    WRAP_OCC_TRANSIENT_TYPE(SWIGEMPTYHACK, TYPE)
    WRAP_OCC_TRANSIENT_TYPE(const, TYPE)

    // Allow to use e.g. Handle_Geom_Curve_DownCast(curve)
    %inline %{
        Handle_ ## TYPE Handle_ ## TYPE ## _DownCast(const Handle_Standard_Transient& t) {
            return Handle_ ## TYPE ## ::DownCast(t);
        }
    %}

    // Allow to use e.g. Handle_Geom_Curve.DownCast(curve)
    %pythoncode {
        class Handle_ ## TYPE():
            @staticmethod
            def DownCast(t):
                return Handle_ ## TYPE ## _DownCast(t)
    }

%enddef
