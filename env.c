#include "common.h"
#include "object.h"
#include "env.h"

typedef struct KrtVarData *KrtVar;
struct KrtVarData {
  KrtVar next;
  KrtObj symbol;
  KrtObj value;
};

struct KrtEnvData {
  KrtEnv parent;
  KrtVar head;
};


KrtEnv
makeKrtEnv (KrtEnv parent)
{
  KrtEnv env = GC_malloc(sizeof(struct KrtEnvData));

  env->parent = parent;
  env->head   = NULL;

  return env;
}

KrtObj
getVar (KrtObj sym, KrtEnv env)
{
  KrtEnv curframe = env;

  while (curframe != NULL) {
    KrtVar curvar = curframe->head;
    
    while (curvar != NULL) {
      if (isEq(sym, curvar->symbol))
	return curvar->value;
      
      curvar = curvar->next;
    }

    curframe = curframe->parent;
  }

  abort();
}

void
bindVar (KrtObj sym, KrtObj val, KrtEnv env)
{
  KrtVar var = GC_malloc(sizeof(struct KrtVarData));
  
  var->symbol = sym;
  var->value  = val;
  var->next   = env->head;

  env->head = var;
}

void
setVar (KrtObj sym, KrtObj val, KrtEnv env)
{
  KrtEnv curframe = env;

  while (curframe != NULL) {
    KrtVar curvar = curframe->head;
    
    while (curvar != NULL) {
      if (isEq(sym, curvar->symbol)) {
	curvar->value = val;
	return;
      }
      
      curvar = curvar->next;
    }

    curframe = curframe->parent;
  }

  abort();
}
