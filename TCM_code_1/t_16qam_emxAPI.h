/*
 * File: t_16qam_emxAPI.h
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 13-Jul-2016 09:59:27
 */

#ifndef T_16QAM_EMXAPI_H
#define T_16QAM_EMXAPI_H

/* Include Files */
#include <float.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "t_16qam_types.h"

/* Function Declarations */
extern emxArray_creal_T *emxCreateND_creal_T(int numDimensions, int *size);
extern emxArray_creal_T *emxCreateWrapperND_creal_T(creal_T *data, int
  numDimensions, int *size);
extern emxArray_creal_T *emxCreateWrapper_creal_T(creal_T *data, int rows, int
  cols);
extern emxArray_creal_T *emxCreate_creal_T(int rows, int cols);
extern void emxDestroyArray_creal_T(emxArray_creal_T *emxArray);
extern void emxInitArray_creal_T(emxArray_creal_T **pEmxArray, int numDimensions);
void myInitArray_creal_T(emxArray_creal_T **pMyArray, int numb);

#endif

/*
 * File trailer for t_16qam_emxAPI.h
 *
 * [EOF]
 */
