#include <gc.h>
#include <string.h>

#include "object.h"

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
  char* symname = GC_malloc_atomic(sizeof(char)*(1+strlen(name)));

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