#ifndef _MATHINTERF_H
#define _MATHINTERF_H
#include "HMem.h"
#include "HMath.h"
#ifdef __cplusplus
extern "C" {
#endif

/* EXPORT-> Dmat_mul: compute matrix multiplication for DMatrix m,n --> m*n
The result is saved as DMatrix res*/
void Dmat_mul(DMatrix m, DMatrix n, DMatrix res);

/* EXPORT-> Dmat_mul: compute matrix add for DMatrix m,n --> m+n
The result is saved as DMatrix res*/
void Dmat_add(DMatrix m, DMatrix n, DMatrix res);

/* EXPORT-> Dmat_mul: compute matrix sub for DMatrix m,n --> m-n
The result is saved as DMatrix res*/
void Dmat_sub(DMatrix m, DMatrix n, DMatrix res);

/* EXPORT-> Dmat_mul: compute matrix multiply by a double scalar DMatrix m,val --> val*m
The result is saved as DMatrix res*/
void Dmat_mul_val(DMatrix m, double val, DMatrix res);

/* EXPORT-> Dmat_T: transpose matirx m, the result is saved as DMatrix res*/
void Dmat_T(DMatrix m, DMatrix res);

/* EXPORT-> Dmat_dot_vec: Dmatrix m dot DVector n, the result is saved as DVector res*/
void Dmat_dot_vec(DMatrix m, DVector n, DVector res);

/* EXPORT-> Dvec_dot: DVector m dot n, the return result is double type. */
double Dvec_dot(DVector m, DVector n);


#ifdef __cplusplus
}
#endif
#endif  /* _MATHINTERF_H */
