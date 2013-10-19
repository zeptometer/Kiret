#include "common.h"
#include "object.h"
#include "intern.h"
#include "env.h"

typedef struct {
  KrtObj car;
  KrtObj cdr;
} KrtCons;

typedef struct {
  double val;
} KrtNumber;

typedef struct {
  int val;
} KrtBool;


KrtObj
makeKrtEmptyList ()
{
  KrtObj obj;

  obj.type = KRT_EMPTY_LIST;
  obj.val.ptr  = NULL;

  return obj;
}

KrtObj
makeKrtCons (KrtObj car, KrtObj cdr)
{
  KrtCons* cell = (KrtCons*)GC_malloc(sizeof(KrtCons));
  KrtObj   obj;

  cell->car = car;
  cell->cdr = cdr;

  obj.type = KRT_CONS;
  obj.val.ptr = (void*)cell;

  return obj;
}

KrtObj
makeKrtSymbol (char* name)
{
  KrtObj obj;
  char* sym = internString(name);

  obj.type = KRT_SYMBOL;
  obj.val.ptr  = (void*)sym;
  
  return obj;
}

KrtObj
makeKrtNumber (double val)
{
  KrtObj obj;
 
  obj.type = KRT_NUMBER;
  obj.val.num  = val;

  return obj;
}

KrtObj
makeKrtBool (int val)
{
  KrtObj obj;

  obj.type = KRT_BOOL;
  obj.val.bool = val;

  return obj;
}


KrtType
getKrtType (KrtObj obj)
{
  return obj.type;
}

int
isEq (KrtObj a, KrtObj b)
{
  return a.val.ptr == b.val.ptr;
}

int
isEqv (KrtObj a, KrtObj b)
{
  if (getKrtType(a) != getKrtType(b)) {
    return 0;
  } else {
    switch (getKrtType(a)) {
    case KRT_EMPTY_LIST:
      return 1;
    case KRT_CONS:
      return isEq(a, b)
	|| (isEqv(getCar(a), getCar(b))
	    && isEqv(getCdr(a), getCdr(b)));
    case KRT_SYMBOL:
    case KRT_CLOSURE:
    case KRT_PRIM_FUNC:
      return isEq(a,b);
    case KRT_NUMBER:
      return getNum(a) == getNum(b);
    case KRT_BOOL:
      return getBool(a) == getBool(b);
    }
  }
}

KrtObj
getCar (KrtObj cons)
{
  return ((KrtCons*)cons.val.ptr)->car;
}

KrtObj
getCdr (KrtObj cons)
{
  return ((KrtCons*)cons.val.ptr)->cdr;
}

char*
getName (KrtObj sym)
{
  return (char*)sym.val.ptr;
}

double
getNum (KrtObj num)
{
  return (double)num.val.num;
}

int
getBool (KrtObj bool)
{
  return (int)bool.val.bool;
}
