#include "object.h"

#ifndef ENV_H
#define ENV_H

typedef struct KrtEnvData *KrtEnv;

KrtEnv makeKrtEnv(KrtEnv parent);
KrtObj getVar(KrtObj sym, KrtEnv env);
void   bindVar(KrtObj sym, KrtObj val, KrtEnv env);
void   setVar(KrtObj sym, KrtObj val, KrtEnv env);

#endif
