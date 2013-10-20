#include "common.h"
#include "object.h"
#include "env.h"
#include "function.h"
#include "eval.h"

static KrtObj
KrtPrimCar (KrtObj obj)
{
  return getCar(getCar(obj));
}

static KrtObj
KrtPrimCdr (KrtObj obj)
{
  return getCdr(getCar(obj));
}

static KrtObj
KrtPrimCons (KrtObj obj)
{
  KrtObj car = getCar(obj);
  KrtObj cdr = getCar(getCdr(obj));
  return makeKrtCons(car, cdr);
}

static KrtObj
KrtPrimList (KrtObj obj)
{
  return obj;
}

static KrtObj
KrtPrimIsEmpty (KrtObj obj)
{
  if (getKrtType(getCar(obj)) == KRT_EMPTY_LIST)
    return makeKrtBool(1);
  else
    return makeKrtBool(0);
}

static KrtObj
KrtPrimPlus (KrtObj obj)
{
  double ans = 0;
  KrtObj num;
  KrtObj rest = obj;

  while (getKrtType(rest) != KRT_EMPTY_LIST) {
    num  = getCar(rest);
    rest = getCdr(rest);

    ans += getNum(num);
  }

  return makeKrtNumber(ans);
}

static KrtObj
KrtPrimSub (KrtObj obj)
{
  if (getKrtType(getCdr(obj)) == KRT_EMPTY_LIST) {
    return makeKrtNumber(-getNum(getCar(obj)));
  } else {
    double ans = getNum(getCar(obj));
    KrtObj num;
    KrtObj rest = getCdr(obj);

    while (getKrtType(rest) != KRT_EMPTY_LIST) {
      num  = getCar(rest);
      rest = getCdr(rest);

      ans -= getNum(num);
    }

    return makeKrtNumber(ans);
  }
}

static KrtObj
KrtPrimIsEq (KrtObj obj)
{
  return makeKrtBool(isEq(getCar(obj), getCar(getCdr(obj))));
}

static KrtObj
KrtPrimIsEqv (KrtObj obj)
{
  return makeKrtBool(isEqv(getCar(obj), getCar(getCdr(obj))));
}



void
defineKrtPrimFunc (char* name, KrtPrimFunc func)
{
  KrtObj sym  = makeKrtSymbol(name);
  KrtObj prim = makeKrtPrimFunc(func);

  bindVar(sym, prim, rootEnv);
}

void initialize_primitive()
{
  defineKrtPrimFunc("car", KrtPrimCar);
  defineKrtPrimFunc("cdr", KrtPrimCdr);
  defineKrtPrimFunc("cons", KrtPrimCons);
  defineKrtPrimFunc("list", KrtPrimList);
  defineKrtPrimFunc("empty?", KrtPrimIsEmpty);
  defineKrtPrimFunc("+", KrtPrimPlus);
  defineKrtPrimFunc("-", KrtPrimSub);
  defineKrtPrimFunc("eq?", KrtPrimIsEq);
  defineKrtPrimFunc("eqv?", KrtPrimIsEqv);
}
