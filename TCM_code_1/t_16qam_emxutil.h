/*
 * File: t_16qam_emxutil.h
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 13-Jul-2016 09:59:27
 */

#ifndef T_16QAM_EMXUTIL_H
#define T_16QAM_EMXUTIL_H

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
extern void emxEnsureCapacity(emxArray__common *emxArray, int oldNumel, int
  elementSize);
extern void emxFree_creal_T(emxArray_creal_T **pEmxArray);
extern void emxFree_real_T(emxArray_real_T **pEmxArray);
extern void emxInit_creal_T(emxArray_creal_T **pEmxArray, int numDimensions);
extern void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);

#endif

/*
 * File trailer for t_16qam_emxutil.h
 *
 * [EOF]
 */
