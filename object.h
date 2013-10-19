#ifndef OBJECT_H
#define OBJECT_H

typedef enum {
  KRT_EMPTY_LIST,
  KRT_CONS,
  KRT_SYMBOL,
  KRT_NUMBER,
  KRT_BOOL,
  KRT_CLOSURE,
  KRT_PRIM_FUNC,
} KrtType;


typedef struct {
  KrtType type;
  union {
    void*  ptr;
    double num;
    int    bool;
  } val;
} KrtObj;


KrtObj makeKrtEmptyList ();
KrtObj makeKrtCons (KrtObj car, KrtObj cdr);
KrtObj makeKrtSymbol (char* name);
KrtObj makeKrtNumber (double val);
KrtObj makeKrtBool (int val);

KrtType getKrtType (KrtObj obj);
int     isAtom (KrtObj obj);
int     isEq (KrtObj a, KrtObj b);
int     isEqv (KrtObj a, KrtObj b);
KrtObj  getCar (KrtObj cons);
KrtObj  getCdr (KrtObj cons);
char*   getName (KrtObj sym);
double  getNum (KrtObj num);
int     getBool (KrtObj bool);

#endif
