#include "common.h"
#include "object.h"
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
  int result = getCar(obj).val.ptr == getCar(getCdr(obj)).val.ptr;
  return makeKrtBool(result);
}

static int
isEqv (KrtObj a, KrtObj b)
{
  if (getKrtType(a) != getKrtType(b)) {
    return 0;
  } else {
    switch (getKrtType(a)) {
    case KRT_EMPTY_LIST:
      return 1;
    case KRT_CONS:
      return (a.val.ptr == b.val.ptr)
        || (isEqv(getCar(a), getCar(b))
         && isEqv(getCdr(a), getCdr(b)));
    case KRT_SYMBOL:
    case KRT_CLOSURE:
    case KRT_PRIM_FUNC:
      return a.val.ptr == b.val.ptr;
    case KRT_NUMBER:
      return getNum(a) == getNum(b);
    case KRT_BOOL:
      return getBool(a) == getBool(b);
    default:
      abort();
    }
  }
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

void
defineKrtSyntax (char* name, KrtSyntaxType tag)
{
  KrtObj sym    = makeKrtSymbol(name);
  KrtObj syntax = makeKrtSyntax(tag);

  bindVar(sym, syntax, rootEnv);
}

void initialize_primitive()
{
  defineKrtSyntax("quote",  KRT_SYNTAX_QUOTE);
  defineKrtSyntax("if",     KRT_SYNTAX_IF);
  defineKrtSyntax("lambda", KRT_SYNTAX_LAMBDA);
  defineKrtSyntax("begin",  KRT_SYNTAX_BEGIN);
  defineKrtSyntax("set!",   KRT_SYNTAX_SET);
  defineKrtSyntax("define", KRT_SYNTAX_DEFINE);
  defineKrtSyntax("define-syntax", KRT_SYNTAX_DEFINE_SYNTAX);

  defineKrtPrimFunc("car",    KrtPrimCar);
  defineKrtPrimFunc("cdr",    KrtPrimCdr);
  defineKrtPrimFunc("cons",   KrtPrimCons);
  defineKrtPrimFunc("list",   KrtPrimList);
  defineKrtPrimFunc("empty?", KrtPrimIsEmpty);
  defineKrtPrimFunc("+",      KrtPrimPlus);
  defineKrtPrimFunc("-",      KrtPrimSub);
  defineKrtPrimFunc("eq?",    KrtPrimIsEq);
  defineKrtPrimFunc("eqv?",   KrtPrimIsEqv);
}
