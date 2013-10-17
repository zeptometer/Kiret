#include <stdio.h>

#include "object.h"
#include "print.h"

int
isKrtList (KrtObj obj)
{
  KrtObj rest = obj;

  while(1) {
    if (rest.type == KRT_EMPTY_LIST)
      return 1;

    if (rest.type != KRT_CONS)
      return 0;

    rest = ((KrtCons*)rest.ptr)->cdr;
  }
}

void
printKrtList (KrtObj obj)
{
  KrtCons *cell = obj.ptr;

  printf("(");
  while(1) {
    KrtObj car = cell->car;
    KrtObj cdr = cell->cdr;
    
    printKrtObj(car);

    if (cdr.type == KRT_EMPTY_LIST)
      break;
    
    printf(" ");

    cell = cdr.ptr;
  }
  printf(")");
}

void
printKrtCons (KrtObj obj)
{
  KrtCons *cell = obj.ptr;
  
  printf("(");
  printKrtObj(cell->car);
  printf(" . ");
  printKrtObj(cell->cdr);
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
    if (isKrtList(obj)) {
      printKrtList(obj);
    } else {
      printKrtCons(obj);
    }
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


