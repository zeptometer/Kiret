#include <stdio.h>

#include "object.h"
#include "print.h"

void
printKrtCons (KrtObj obj)
{
  KrtCons *cell = obj.ptr;

  printf("(");
  while (1) {
    KrtObj car = cell->car;
    KrtObj cdr = cell->cdr;
    
    printKrtObj(car);

    if (cdr.type == KRT_EMPTY_LIST) {
      break;
    } else if (cdr.type == KRT_CONS) {
      printf(" ");
      cell = cdr.ptr;
    } else {
      printf(" . ");
      printKrtObj(cdr);
      break;
    }
  }
  printf(")");
}

void
printKrtObj (KrtObj obj)
{
  switch (obj.type) {
  case KRT_EMPTY_LIST:
    printf("()");
    break;
  case KRT_CONS:
    printKrtCons(obj);
    break;
  case KRT_SYMBOL:
    printf("%s", ((KrtSymbol*)obj.ptr)->name);
    break;
  case KRT_NUMBER:
    printf("%f", ((KrtNumber*)obj.ptr)->val);
    break;
  case KRT_BOOL:
    if (((KrtBool*)obj.ptr)->val)
      printf("#t");
    else
      printf("#f");
    break;
  }
}


