#include <stdio.h>
#include <stdlib.h>
#include "MathInterf.h"

/** Double Matrix Multiplication
 * @author Mr.Black
 * @param m: Input DMatrix
 * @param n: Input DMatrix
 * @param res: m*n (matrix mult)
 */
void Dmat_mul(DMatrix m, DMatrix n, DMatrix res)
{
    /* dimension check */
    int nrows_m,ncols_m,nrows_n,ncols_n;
    int nrows_r,ncols_r;
    nrows_m = NumDRows(m);
    ncols_m = NumDCols(m);
    nrows_n = NumDRows(n);
    ncols_n = NumDCols(n);
    nrows_r = NumDRows(res);
    ncols_r = NumDCols(res);
    if(ncols_m!=nrows_n)
    {
        printf("Error in Dmat_mul: incompatible matrix dimension\n");
        return;
    }
    if(nrows_r!=nrows_m && ncols_r!=ncols_n)
    {
        printf("Error in Dmat_mul: incompatible result matrix dimension\n");
        return;
    }
    /* do the matrix mult */
    int i, j, k;
    double ret;
    for (i = 1; i <= nrows_m; i++)
    {
        for (j = 1; j <= ncols_n; j++)
        {
            ret = 0;
            for (k = 1; k <= ncols_m; k++)
            {
                ret += m[i][k] * n[k][j];
            }
            res[i][j] = ret;
        }
    }
    
}

/** Double Matrix Add
 * @author Mr.Black
 * @param m: Input DMatrix
 * @param n: Input DMatrix
 * @param res: m+n (matrix add)
 */
void Dmat_add(DMatrix m, DMatrix n, DMatrix res)
{
    /* dimension check */
    int nrows_m,ncols_m,nrows_n,ncols_n;
    int nrows_r,ncols_r;
    nrows_m = NumDRows(m);
    ncols_m = NumDCols(m);
    nrows_n = NumDRows(n);
    ncols_n = NumDCols(n);
    nrows_r = NumDRows(res);
    ncols_r = NumDCols(res);
    if(nrows_m!=nrows_n || nrows_m!=nrows_r
        || ncols_m!=ncols_n || ncols_m!=ncols_r)
    {
        printf("Error in Dmat_add: incompatible matrix dimension\n");
        return;
    }
    /* do the matrix add */
    int i, j;
    for (i = 1; i <= nrows_m; i++)
    {
        for (j = 1; j <= ncols_m; j++)
        {
            res[i][j] = m[i][j]+n[i][j];
        }
    }
}

/** Double Matrix Sub
 * @author Mr.Black
 * @param m: Input DMatrix
 * @param n: Input DMatrix
 * @param res: m-n (matrix sub)
 */
void Dmat_sub(DMatrix m, DMatrix n, DMatrix res)
{
    /* dimension check */
    int nrows_m,ncols_m,nrows_n,ncols_n;
    int nrows_r,ncols_r;
    nrows_m = NumDRows(m);
    ncols_m = NumDCols(m);
    nrows_n = NumDRows(n);
    ncols_n = NumDCols(n);
    nrows_r = NumDRows(res);
    ncols_r = NumDCols(res);
    if(nrows_m!=nrows_n || nrows_m!=nrows_r
        || ncols_m!=ncols_n || ncols_m!=ncols_r)
    {
        printf("Error in Dmat_sub: incompatible matrix dimension\n");
        return;
    }
    /* do the matrix sub */
    int i, j;
    for (i = 1; i <= nrows_m; i++)
    {
        for (j = 1; j <= ncols_m; j++)
        {
            res[i][j] = m[i][j]-n[i][j];
        }
    }
}

/** Double Matrix multiply by a double value
 * @author Mr.Black
 * @param m: Input DMatrix
 * @param val: A double scalar
 * @param res: val*m
 */
void Dmat_mul_val(DMatrix m, double val, DMatrix res)
{
   /* dimension check */
    int nrows_m,ncols_m,nrows_r,ncols_r;
    nrows_m = NumDRows(m);
    ncols_m = NumDCols(m);
    nrows_r = NumDRows(res);
    ncols_r = NumDCols(res);
    if(nrows_m!=nrows_r || ncols_m!=ncols_r)
    {
        printf("Error in Dmat_mul_val: incompatible matrix dimension\n");
        return;
    }
    /* do the matrix mul val */
    int i, j;
    for (i = 1; i <= nrows_m; i++)
    {
        for (j = 1; j <= ncols_m; j++)
        {
            res[i][j] = m[i][j]*val;
        }
    }
}

/** Double Matrix transpose
 * @author Mr.Black
 * @param m: Input DMatrix
 * @param res: m.T
 */
void Dmat_T(DMatrix m, DMatrix res)
{
    /* dimension check */
    int nrows_m,ncols_m,nrows_r,ncols_r;
    nrows_m = NumDRows(m);
    ncols_m = NumDCols(m);
    nrows_r = NumDRows(res);
    ncols_r = NumDCols(res);
    
    DMatrix m_copy = CreateDMatrix(&gstack,nrows_m,ncols_m);
    CopyDMatrix(m,m_copy);
    
    if(nrows_m!=ncols_r || ncols_m!=nrows_r)
    {
        printf("Error in Dmat_T: incompatible matrix dimension\n");
        return;
    }
    
    int i, j;
    for (i = 1; i <= nrows_m; i++)
    {
        for (j = 1; j <= ncols_m; j++)
        {
            res[j][i] = m_copy[i][j];
        }
    }
    FreeDMatrix(&gstack,m_copy);
}


/** Double Matrix dot Vector
 * @author Mr.Black
 * @param m: Input DMatrix
 * @param n: Input DVector
 * @param res: m*1 (DVector)
 */
void Dmat_dot_vec(DMatrix m, DVector n, DVector res)
{
	/* dimension check */
	int nrows_m,ncols_m;
	int lens_n, lens_res;
	nrows_m = NumDRows(m);
    ncols_m = NumDCols(m);
	lens_n = DVectorSize(n);
	lens_res = DVectorSize(res);
	
	if(ncols_m!=lens_n || nrows_m!=lens_res)
	{
		printf("Error in Dmat_dot_vec: incompatible matrix dimension\n");
		return;
	}
		
 	/* do the matrix dot */
    int i, k;
    double ret;
    for (i = 1; i <= nrows_m; i++)
    {
		ret = 0;
		for (k = 1; k <= ncols_m; k++)
		{
		    ret += m[i][k] * n[k];
		}
		res[i] = ret;   
    }

}

/** Double Vector dot Vector
 * @author Mr.Black
 * @param m: Input DVector
 * @param n: Input DVector
 * @param res: double
 */
double Dvec_dot(DVector m, DVector n)
{
	int lens_m,lens_n;
    /* dimension check */
	lens_m = DVectorSize(m);
    lens_n = DVectorSize(n);

	if(lens_m!=lens_n)
	{
		printf("Error in Dvec_dot: incompatible matrix dimension\n");
		return;
	}
    /* do the vector dot */
	int i; double res=0;
	for(i=1;i<=lens_m;++i)
	{
		res += m[i]*n[i];
	}
	return res;
}

