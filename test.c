#include <stdio.h>

#include "object.h"
#include "print.h"

int
main ()
{
  KrtObj nil  = makeKrtEmptyList();
  KrtObj poyo = makeKrtSymbol("poyo");
  KrtObj hoge = makeKrtSymbol("hoge");
  KrtObj cell = makeKrtCons(poyo, nil);
  KrtObj list = makeKrtCons(hoge, cell);
  KrtObj tsil = makeKrtCons(cell, hoge);

  printKrtObj(list);
  printf("\n");
  printKrtObj(tsil);
  printf("\n");
}
