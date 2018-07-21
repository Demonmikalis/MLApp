#ifndef _EXPRESSION_H
#define _EXPRESSION_H
#ifdef __cplusplus
extern "C" {
#endif

#define FALSE 0
#define TRUE 1

#include "CLib/Stack.h"


double EvaluateExpression(char exp[]);

#ifdef __cplusplus
}
#endif
#endif  /* _EXPRESSION_H */
