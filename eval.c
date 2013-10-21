#include "common.h"
#include "object.h"
#include "env.h"
#include "function.h"
#include "primitive.h"
#include "eval.h"

static KrtObj QUOTE;
static KrtObj IF;
static KrtObj LAMBDA;
static KrtObj DEFINE;
static KrtObj BEGIN;
static KrtObj SET_BANG;

void initialize () {
  rootEnv  = makeKrtEnv(NULL);

  QUOTE    = makeKrtSymbol("quote");
  IF       = makeKrtSymbol("if");
  LAMBDA   = makeKrtSymbol("lambda");
  DEFINE   = makeKrtSymbol("define");
  BEGIN    = makeKrtSymbol("begin");
  SET_BANG = makeKrtSymbol("set!");

  initialize_primitive();
}

static KrtObj
eval_each (KrtObj list, KrtEnv env)
{
  if (getKrtType(list) == KRT_EMPTY_LIST) {
    return makeKrtEmptyList();
  } else {
    return makeKrtCons(eval(getCar(list), env),
		       eval_each(getCdr(list), env));
  }
}

KrtObj applyKrtPrimFunc (KrtObj prim, KrtObj args, KrtEnv env)
{
  return ((KrtPrimFunc)prim.val.ptr)(eval_each(args, env));
}

#define TAIL_CALL(c, e) do {			\
    code = c;					\
    env = e;					\
    goto LOOP;					\
  } while (0)					\


KrtObj
eval (KrtObj code, KrtEnv env)
{
 LOOP:
  switch (getKrtType(code)) {
  case KRT_SYMBOL:
    return getVar(code, env);

  case KRT_NUMBER:
  case KRT_BOOL:
    return code;

  case KRT_CONS:
    {
      KrtObj head = getCar(code);

      if (isEq(head, QUOTE)) {

	return getCar(getCdr(code));

      } else if (isEq(head, IF)) {

	KrtObj pred = eval(getCar(getCdr(code)), env);

	if (getBool(pred)) {
	  TAIL_CALL(getCar(getCdr(getCdr(code))), env);
	} else {
	  KrtObj rest = getCdr(getCdr(getCdr(code)));
	  if (getKrtType(rest) == KRT_EMPTY_LIST) {
	    return makeKrtEmptyList();
	  } else {
	    TAIL_CALL(getCar(rest), env);
	  }
	}

      } else if (isEq(head, BEGIN)) {

	KrtObj body = getCdr(code);

	while (getKrtType(getCdr(body)) != KRT_EMPTY_LIST) {
	  eval(getCar(body), env);
	  body = getCdr(body);
	}

	TAIL_CALL(getCar(body), env);

      } else if (isEq(head, LAMBDA)) {

	KrtObj args = getCar(getCdr(code));
	KrtObj body = getCdr(getCdr(code));

	return makeKrtClosure(env, args, body);

      } else if (isEq(head, SET_BANG)) {

	KrtObj var = getCar(getCdr(code));
	KrtObj val = eval(getCar(getCdr(getCdr(code))), env);

	setVar(var, val, env);

	return val;

      } else if (isEq(head, DEFINE)) {

	KrtObj var = getCar(getCdr(code));
	KrtObj val = eval(getCar(getCdr(getCdr(code))), env);

	bindVar(var, val, env);

	return var;

      } else {

	KrtObj func = eval(getCar(code), env);
	KrtObj args = getCdr(code);

	switch (getKrtType(func)) {
	case KRT_CLOSURE:
	  {
	    KrtEnv frame = makeKrtEnv(getEnv(func));

	    KrtObj sym;
	    KrtObj restsym = getArgs(func);
	    KrtObj arg;
	    KrtObj restarg = args;

	    while (getKrtType(restsym) != KRT_EMPTY_LIST) {
	      if (getKrtType(restsym) == KRT_SYMBOL) {
		bindVar(restsym, eval_each(restarg, env), frame);
		break;
	      }

	      arg     = getCar(restarg);
	      restarg = getCdr(restarg);
	      sym     = getCar(restsym);
	      restsym = getCdr(restsym);

	      bindVar(sym, eval(arg, env), frame);
	    }

	    TAIL_CALL(getCode(func), frame);
	  }
	case KRT_PRIM_FUNC:
	  return applyKrtPrimFunc (func, args, env);
	default:
	  abort();
	}
      }
    }
  default:
    abort();
  }
}
