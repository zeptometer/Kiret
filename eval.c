#include "common.h"
#include "object.h"
#include "primitive.h"
#include "eval.h"

void
initialize ()
{
  rootEnv = makeKrtEnv(NULL);
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

  case KRT_SYNTACTIC_CLOSURE:
    TAIL_CALL(getCode(code), getEnv(code));

  case KRT_CONS:
    {
      KrtObj func = eval(getCar(code), env);
      KrtObj args = getCdr(code);

    case KRT_CLOSURE:
      {
	KrtEnv frame = makeKrtEnv(getEnv(func));

	KrtObj sym;
	KrtObj arg;
	KrtObj restsym = getArgs(func);
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
      return getPrimFunc(func)(eval_each(args, env));

    case KRT_MACRO:
      {
	KrtEnv frame	     = makeKrtEnv(getEnv(func));
	KrtObj args_sym    = getArgs(func);

	KrtObj code_sym    = getCar(args_sym);
	KrtObj mac_env_sym = getCar(getCdr(args_sym));
	KrtObj use_env_sym = getCar(getCdr(getCdr(args_sym)));

	bindVar(code_sym, code, frame);
	bindVar(mac_env_sym, envToObj(getEnv(func)), frame);
	bindVar(use_env_sym, envToObj(env), frame);

	TAIL_CALL(eval(getCode(func), frame), env);
      }

      switch (getKrtType(func)) {
      case KRT_SYNTAX:
	switch (getSyntaxType(func)) {
	case KRT_SYNTAX_QUOTE:
	  return getCar(getCdr(code));

	case KRT_SYNTAX_IF:
	  {
	    KrtObj pred = eval(getCar(args), env);
	    if (getBool(pred)) {
	      TAIL_CALL(getCar(getCdr(args)), env);
	    } else {
	      KrtObj rest = getCdr(getCdr(args));
	      if (getKrtType(rest) == KRT_EMPTY_LIST) {
		return makeKrtEmptyList();
	      } else {
		TAIL_CALL(getCar(rest), env);
	      }
	    }
	  }

	case KRT_SYNTAX_BEGIN:
	  {
	    KrtObj body = getCdr(code);

	    while (getKrtType(getCdr(body)) != KRT_EMPTY_LIST) {
	      eval(getCar(body), env);
	      body = getCdr(body);
	    }

	    TAIL_CALL(getCar(body), env);
	  }

	case KRT_SYNTAX_LAMBDA:
	  {
	    KrtObj args = getCar(getCdr(code));
	    KrtObj body = getCdr(getCdr(code));

	    return makeKrtClosure(env, args, body);
	  }

	case KRT_SYNTAX_SET:
	  {
	    KrtObj var = getCar(getCdr(code));
	    KrtObj val = eval(getCar(getCdr(getCdr(code))), env);

	    setVar(var, val, env);

	    return val;
	  }

	case KRT_SYNTAX_DEFINE:
	  {
	    KrtObj var = getCar(getCdr(code));
	    KrtObj val = eval(getCar(getCdr(getCdr(code))), env);

	    bindVar(var, val, env);

	    return var;
	  }
	
	case KRT_SYNTAX_DEFINE_SYNTAX:
	  {
	    KrtObj var = getCar(args);
	    KrtObj expander = eval(getCar(getCdr(args)), env);

	    bindVar(var, makeKrtMacro(expander), env);
	    return var;
	  }
	}


      default:
	abort();
      }
    }
  default:
    abort();
  }
}
