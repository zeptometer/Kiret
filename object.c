#include <gc.h>
#include <string.h>

#include "object.h"
#include "intern.h"

KrtObj
makeKrtEmptyList ()
{
  KrtObj obj;

  obj.type = KRT_EMPTY_LIST;
  obj.ptr  = NULL;

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
  obj.ptr = (void*)cell;

  return obj;
}

KrtObj
makeKrtSymbol (char* name)
{
  KrtSymbol *symbol = GC_malloc(sizeof(KrtSymbol));
  KrtObj obj;
  char* symname = internString(name);

  strcpy(symname, name);
  symbol->name = symname;

  obj.type = KRT_SYMBOL;
  obj.ptr  = (void*)symbol;
  
  return obj;
}

KrtObj
makeKrtNumber (double val)
{
  KrtObj obj;
  KrtNumber *ptr = GC_malloc_atomic(sizeof(KrtNumber));

  ptr->val = val;

  obj.type = KRT_NUMBER;
  obj.ptr  = ptr;

  return obj;
}

KrtObj
makeKrtBool (int val)
{
  KrtObj obj;
  KrtBool *ptr = GC_malloc_atomic(sizeof(KrtBool));

  ptr->val = val;

  obj.type = KRT_BOOL;
  obj.ptr  = ptr;

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
  return a.ptr == b.ptr;
}

int
isEqv (KrtObj a, KrtObj b)
{
  if (a.type != b.type) {
    return 0;
  } else {
    switch (a.type) {
    case KRT_EMPTY_LIST:
      return 1;
    case KRT_CONS:
      return a.ptr == b.ptr
	|| (isEqv(getCar(a), getCar(b))
	    && isEqv(getCdr(a), getCdr(b)));
    case KRT_SYMBOL:
      return a.ptr == b.ptr;
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
  return ((KrtCons*)cons.ptr)->car;
}

KrtObj
getCdr (KrtObj cons)
{
  return ((KrtCons*)cons.ptr)->cdr;
}

char*
getName (KrtObj sym)
{
  return ((KrtSymbol*)sym.ptr)->name;
}

double
getNum (KrtObj num)
{
  return ((KrtNumber*)num.ptr)->val;
}

int
getBool (KrtObj bool)
{
  return ((KrtBool*)bool.ptr)->val;
}
