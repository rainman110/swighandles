#ifndef A_H
#define A_H

#include <cstdio>

class Handle_A;

class A {
  friend class Handle_A;

public:
  A();
  ~A();

  void DoSomething() const;

  int RefCount();

private:
  void IncRefs();
  void DecRefs();

private:
  int count;
  bool* alive;
};

/**
 * @brief Handle_A is a smart
 * pointer to class A as similarly done
 * in the OpenCASCADE framework
 *
 * Usage: Handle_A a = new A();
 */
class Handle_A {
public:
  Handle_A();
  Handle_A(A *a);
  Handle_A(const Handle_A &h);
  ~Handle_A();

  Handle_A &operator=(const Handle_A &h);

  bool IsNull() const;

  A *GetObject();

private:
  A *a;
};

/**
 * A class that mimics e.g. GeomAPI_PointsToBSpline
 */
class ABuilder {
public:
  ABuilder() {
    ah = new A();
  }
  ~ABuilder() {
    printf("ABuilder::~ABuilder()\n");
  }

  Handle_A& GetHandleARef() {
    return ah;
  }

  Handle_A GetHandleACopy() {
    return ah;
  }
private:
  Handle_A ah;
};

/**
 * Simple function that requires a handle of a
 */
void simpleFunction(Handle_A handle);

#endif // A_H
