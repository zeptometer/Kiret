#include "object.h"

#ifndef EVAL_H
#define EVAL_H

KrtEnv rootEnv;

void initialize();

KrtObj eval(KrtObj code, KrtEnv env);

#endif
