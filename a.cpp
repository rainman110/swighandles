#include "a.h"

#include <cstdio>

A::A() {
  printf("A::A()\n");
  count = 0;
}

A::~A() { printf("A::~A()\n"); }

void A::DoSomething() const {
    printf("A::do_something(): My refcount is %d\n", count);
}

int A::RefCount() {
  printf("  A::RefCount()=%d\n", count);
  return count;
}

void A::IncRefs() {
  printf("  A::IncRefs()\n");
  count++;
}

void A::DecRefs() {
  printf("  A::DecRefs()\n");
  count--;
}

Handle_A::Handle_A()
{
  a = NULL;
}

Handle_A::Handle_A(A *a) {
  this->a = a;
  if (a) {
    a->IncRefs();
  }
}

Handle_A::Handle_A(const Handle_A &h) {
  printf("Handle_A::Handle_A(const Handle_A &h)\n");
  a = h.a;
  if (a) {
    a->IncRefs();
  }
}

Handle_A &Handle_A::operator=(const Handle_A &h) {
  printf("Handle_A &Handle_A::operator=(const Handle_A &h)\n");
  a = h.a;
  if (a) {
    a->IncRefs();
  }
  return *this;
}

bool Handle_A::IsNull() const
{
  return a == NULL;
}

Handle_A::~Handle_A() {
  printf("Handle_A::~Handle_A()\n");
  if (a) {
    a->DecRefs();
    if (a->RefCount() == 0) {
      printf("Delete A from Handle_A::~Handle_A()\n");
      delete a;
    }
  }
}

A *Handle_A::GetObject() { return a; }


void simpleFunction(Handle_A handle) {
  printf("simpleFunction(Handle_A handle)\n");
  if(!handle.IsNull()) {
    handle.GetObject()->DoSomething();
  }
  else {
    printf("handle is null\n");
  }
}
