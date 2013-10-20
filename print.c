#include "common.h"
#include "object.h"
#include "print.h"
#include "function.h"

void
printKrtCons (KrtObj cons)
{
  KrtObj car = getCar(cons);
  KrtObj cdr = getCdr(cons);

  printf("(");
  while (1) {
    printKrtObj(car);

    if (getKrtType(cdr) == KRT_EMPTY_LIST) {
      break;
    } else if (getKrtType(cdr) == KRT_CONS) {
      printf(" ");

      car = getCar(cdr);
      cdr = getCdr(cdr);

      continue;
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
  switch (getKrtType(obj)) {
  case KRT_EMPTY_LIST:
    printf("()");
    break;
  case KRT_CONS:
    printKrtCons(obj);
    break;
  case KRT_SYMBOL:
    printf("%s", getName(obj));
    break;
  case KRT_NUMBER:
    printf("%f", getNum(obj));
    break;
  case KRT_BOOL:
    if (getBool(obj))
      printf("#t");
    else
      printf("#f");
    break;
  case KRT_CLOSURE:
    printf("#<closure ");
    printKrtObj(getArgs(obj));
    printf(" -> ");
    printKrtObj(getCode(obj));
    printf(">");
    break;
  case KRT_PRIM_FUNC:
    printf("#<primtive function>");
  }
}
