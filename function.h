#include "object.h"
#include "env.h"

#ifndef FUNCTION_H
#define FUNCTION_H

typedef KrtObj (*KrtPrimFunc) (KrtObj);

KrtObj makeKrtClosure (KrtEnv env, KrtObj args, KrtObj code);
KrtObj makeKrtPrimFunc (KrtPrimFunc func);

KrtEnv getEnv (KrtObj obj);
KrtObj getArgs (KrtObj obj);
KrtObj getCode (KrtObj obj);

KrtObj applyKrtPrimFunc (KrtObj prim, KrtObj args);

#endif
