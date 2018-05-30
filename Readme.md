README
======

This is a simple demo code to test, how the memory management can be performed
using OpenCASCADE like ```Handle_``` classes from python/swig.

The aim is, to have a non-leaking and non-crashing python wrapping of the C++
classes and making the existence of the Handle_ classes invisibile for python
users. Assume we have the wollowing C++ prototypes:

```c++
void DoSomething(const A& a);
void DoSomethingElse(Handle_A ah);
```

Then, the following python code is possible:

```python
a = A()
DoSomething(a);
DoSomethingElse(a);
```

At no point, the user is confronted with the Handle_ classes.

_Important note_
To be backwards compatible with existing pythonocc code, you can still call the
```.GetObject()``` and ```.GetHandle()``` methods. They simply do nothing and
just return ```self```. 


Dependencies:
-------------
 - Python + Libraries
 - Swig
 - CMake
