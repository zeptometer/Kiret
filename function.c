#include "common.h"
#include "object.h"
#include "env.h"
#include "function.h"

typedef struct {
  KrtEnv env;
  KrtObj args;
  KrtObj code;
} KrtClosure;


KrtObj
makeKrtClosure (KrtEnv env, KrtObj args, KrtObj code)
{
  KrtObj obj;
  KrtClosure *ptr = GC_malloc(sizeof(KrtClosure));

  ptr->env  = env;
  ptr->args = args;
  ptr->code = code;

  obj.type = KRT_CLOSURE;
  obj.ptr  = (void*)ptr;

  return obj;
}

KrtObj
makeKrtPrimFunc (KrtPrimFunc func)
{
  KrtObj obj;

  obj.type = KRT_PRIM_FUNC;
  obj.ptr = (void*)func;

  return obj;
}


KrtEnv getEnv (KrtObj obj)
{
  return ((KrtClosure*)obj.ptr)->env;
}

KrtObj getArgs (KrtObj obj)
{
  return ((KrtClosure*)obj.ptr)->args;
}

KrtObj getCode (KrtObj obj)
{
  return ((KrtClosure*)obj.ptr)->code;
}



KrtObj applyKrtPrimFunc (KrtObj prim, KrtObj args)
{
  return ((KrtPrimFunc)prim.ptr)(args);
}
