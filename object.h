#ifndef OBJECT_H
#define OBJECT_H

typedef enum {
  KRT_EMPTY_LIST,
  KRT_CONS,
  KRT_SYMBOL,
  KRT_NUMBER,
  KRT_BOOL
} KrtType;


typedef struct {
  KrtType type;
  void* ptr;
} KrtObj;


typedef struct {
  KrtObj car;
  KrtObj cdr;
} KrtCons;

typedef struct {
  char *name;
} KrtSymbol;

typedef struct {
  double val;
} KrtNumber;

typedef struct {
  int val;
} KrtBool;


KrtObj makeKrtEmptyList ();
KrtObj makeKrtCons (KrtObj car, KrtObj cdr);
KrtObj makeKrtSymbol (char* name);
KrtObj makeKrtNumber (double val);
KrtObj makeKrtBool (int val);

KrtType getKrtType (KrtObj obj);
int     isEq (KrtObj a, KrtObj b);
int     isEqv (KrtObj a, KrtObj b);
KrtObj  getCar (KrtObj cons);
KrtObj  getCdr (KrtObj cons);
char*   getName (KrtObj sym);
double  getNum (KrtObj num);
int     getBool (KrtObj bool);

#endif
