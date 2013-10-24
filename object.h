#ifndef OBJECT_H
#define OBJECT_H

#include "object.h"

typedef enum {
  KRT_EMPTY_LIST,
  KRT_CONS,
  KRT_SYMBOL,
  KRT_NUMBER,
  KRT_BOOL,

  KRT_ENV,
  KRT_CLOSURE,
  KRT_MACRO,
  KRT_SYNTACTIC_CLOSURE,
  KRT_PRIM_FUNC,
  KRT_SYNTAX
} KrtType;

typedef enum {
  KRT_SYNTAX_QUOTE,
  KRT_SYNTAX_IF,
  KRT_SYNTAX_LAMBDA,
  KRT_SYNTAX_DEFINE,
  KRT_SYNTAX_BEGIN,
  KRT_SYNTAX_SET,
  KRT_SYNTAX_DEFINE_SYNTAX
} KrtSyntaxType;

typedef struct {
  KrtType type;
  union {
    void*  ptr;
    double num;
    int    bool;
    KrtSyntaxType syntax;
  } val;
} KrtObj;

/* env */
typedef struct KrtEnvData *KrtEnv;
KrtEnv	makeKrtEnv(KrtEnv parent);
KrtObj	getVar(KrtObj sym, KrtEnv env);
void	bindVar(KrtObj sym, KrtObj val, KrtEnv env);
void	setVar(KrtObj sym, KrtObj val, KrtEnv env);

/* constructor */
typedef KrtObj (*KrtPrimFunc) (KrtObj);

KrtObj	makeKrtEmptyList ();
KrtObj	makeKrtCons (KrtObj car, KrtObj cdr);
KrtObj	makeKrtSymbol (char* name);
KrtObj	makeKrtNumber (double val);
KrtObj	makeKrtBool (int val);
KrtObj	makeKrtClosure (KrtEnv env, KrtObj args, KrtObj code);
KrtObj	makeKrtPrimFunc (KrtPrimFunc func);
KrtObj  makeKrtMacro (KrtObj expander);
KrtObj	makeKrtSyntacticClosure (KrtEnv env, KrtObj code);
KrtObj	makeKrtSyntax (KrtSyntaxType tag);
KrtObj  envToObj (KrtEnv env);

/* accessor */
KrtType		getKrtType (KrtObj obj);
// cons
KrtObj		getCar (KrtObj obj);
KrtObj		getCdr (KrtObj obj);
// symbol
char*		getName (KrtObj obj);
// number
double		getNum (KrtObj obj);
// bool
int		getBool (KrtObj bool);
// env
KrtEnv          objToEnv (KrtObj obj);
// closure | syntactic closure
KrtEnv		getEnv (KrtObj obj);
KrtObj		getArgs (KrtObj obj);
KrtObj          getCode (KrtObj obj);
// primitive function
KrtPrimFunc	getPrimFunc (KrtObj obj);
// syntax
KrtSyntaxType   getSyntaxType (KrtObj obj);

#endif
