/*
 * File: t_16qam.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 13-Jul-2016 09:59:27
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "t_16qam.h"
#include "t_16qam_emxutil.h"

/* Function Declarations */
static int div_s32_floor(int numerator, int denominator);
static double rt_remd_snf(double u0, double u1);
static double rt_roundd_snf(double u);

/* Function Definitions */

/*
 * Arguments    : int numerator
 *                int denominator
 * Return Type  : int
 */
static int div_s32_floor(int numerator, int denominator)
{
  int quotient;
  unsigned int absNumerator;
  unsigned int absDenominator;
  boolean_T quotientNeedsNegation;
  unsigned int tempAbsQuotient;
  if (denominator == 0) {
    if (numerator >= 0) {
      quotient = MAX_int32_T;
    } else {
      quotient = MIN_int32_T;
    }
  } else {
    if (numerator < 0) {
      absNumerator = ~(unsigned int)numerator + 1U;
    } else {
      absNumerator = (unsigned int)numerator;
    }

    if (denominator < 0) {
      absDenominator = ~(unsigned int)denominator + 1U;
    } else {
      absDenominator = (unsigned int)denominator;
    }

    quotientNeedsNegation = ((numerator < 0) != (denominator < 0));
    tempAbsQuotient = absNumerator / absDenominator;
    if (quotientNeedsNegation) {
      absNumerator %= absDenominator;
      if (absNumerator > 0U) {
        tempAbsQuotient++;
      }
    }

    if (quotientNeedsNegation) {
      quotient = -(int)tempAbsQuotient;
    } else {
      quotient = (int)tempAbsQuotient;
    }
  }

  return quotient;
}

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_remd_snf(double u0, double u1)
{
  double y;
  double b_u1;
  double tr;
  if (!((!rtIsNaN(u0)) && (!rtIsInf(u0)) && ((!rtIsNaN(u1)) && (!rtIsInf(u1)))))
  {
    y = rtNaN;
  } else {
    if (u1 < 0.0) {
      b_u1 = ceil(u1);
    } else {
      b_u1 = floor(u1);
    }

    if ((u1 != 0.0) && (u1 != b_u1)) {
      tr = u0 / u1;
      if (fabs(tr - rt_roundd_snf(tr)) <= DBL_EPSILON * fabs(tr)) {
        y = 0.0;
      } else {
        y = fmod(u0, u1);
      }
    } else {
      y = fmod(u0, u1);
    }
  }

  return y;
}

/*
 * Arguments    : double u
 * Return Type  : double
 */
static double rt_roundd_snf(double u)
{
  double y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/*
 * 16QAM��TCM�������
 * Arguments    : const double data[3000]
 *                double N
 *                emxArray_creal_T *y
 * Return Type  : void
 */
void t_16qam(const double data[3000], double N, emxArray_creal_T *y)
{
  double z[1000];
  int i0;
  double u[1004];
  emxArray_real_T *u1;
  int i;
  double uu[3006];
  int k;
  int i1;
  int xs;
  double cnvencd[2004];
  int cs;
  int s16_im;
  double b_y[2004];
  static double s[4008];
  double u_data[1005];
  static const signed char a[6] = { 1, 0, 0, 1, 1, 0 };

  int loop_ub;
  double b_uu[4008];
  double kk[4008];
  cint8_T s16[16];
  double d0;
  static const signed char b[4] = { 8, 4, 2, 1 };

  /* ������� */
  memcpy(&z[0], &data[2000], 1000U * sizeof(double));

  /*  cnv_encd(G,k0,input),k0��ÿһʱ�����������������bit���� */
  /*  G�Ǿ����������е����ɾ�������n0��L*k0��n0�����bit���� */
  /*  ����n0��L�����ɾ���G������L��Լ�����ȡ�L֮���Խ�Լ������ */
  /*  ����Ϊ��������ÿһʱ����������в����뵱ǰ���������йأ� */
  /*  ���һ����������״̬�йأ����״̬���ɱ�������ǰ(L-1)k0�� */
  /*  �����������,ͨ��������ʾΪ(n0,k0,m)��m=(L-1)*k0�Ǳ��� */
  /*  ���еı������������Ҳ���Ƿ�ΪL-1�Σ�ÿ��k0�� */
  /*  ��Щ�˽�m=L*k0����ΪԼ�����ȣ��е��˶���Ϊm=(L-1)*k0 */
  /*  �鿴�Ƿ���Ҫ��0������input������k0��������  */
  /*  ������ɾ���G��ά���Ƿ��k0һ��  */
  /*  �õ�Լ������L�����������n0 */
  /*  ����Ϣǰ���0��ʹ��������0����0����Ϊ(L-1)*k0�� */
  for (i0 = 0; i0 < 2; i0++) {
    u[i0] = 0.0;
  }

  memcpy(&u[2], &z[0], 1000U * sizeof(double));
  for (i0 = 0; i0 < 2; i0++) {
    u[i0 + 1002] = 0.0;
  }

  emxInit_real_T(&u1, 2);

  /*  �õ�uu����,���ĸ����Ǳ����������������ڸ�ʱ�����ڵ�����  */
  i0 = u1->size[0] * u1->size[1];
  u1->size[0] = 1;
  u1->size[1] = 3;
  emxEnsureCapacity((emxArray__common *)u1, i0, (int)sizeof(double));
  for (i0 = 0; i0 < 3; i0++) {
    u1->data[i0] = u[2 - i0];
  }

  /* ����0����������а�ÿ��L*k0�����飬�����ǰ�һ�������� */
  /* ��1��L*k0����Ϊ��һ�飬��2��L*k0+1Ϊ�ڶ��飬���������� */
  /* �������鰴�������С�  */
  for (i = 0; i < 1001; i++) {
    if (2 + i > 4 + i) {
      i0 = 1;
      k = 1;
      i1 = 0;
    } else {
      i0 = i + 4;
      k = -1;
      i1 = i + 2;
    }

    xs = u1->size[1];
    cs = div_s32_floor(i1 - i0, k);
    s16_im = u1->size[0] * u1->size[1];
    u1->size[1] = (xs + cs) + 1;
    emxEnsureCapacity((emxArray__common *)u1, s16_im, (int)sizeof(double));
    loop_ub = div_s32_floor(i1 - i0, k);
    for (i1 = 0; i1 <= loop_ub; i1++) {
      u_data[i1] = u[(i0 + k * i1) - 1];
    }

    for (i0 = 0; i0 <= cs; i0++) {
      u1->data[xs + i0] = u_data[i0];
    }
  }

  for (k = 0; k < 3006; k++) {
    uu[k] = u1->data[k];
  }

  /*  �õ��������������ɾ���G*uu�õ� */
  for (i0 = 0; i0 < 2; i0++) {
    for (k = 0; k < 1002; k++) {
      b_y[i0 + (k << 1)] = 0.0;
      for (i1 = 0; i1 < 3; i1++) {
        b_y[i0 + (k << 1)] += (double)a[i0 + (i1 << 1)] * uu[i1 + 3 * k];
      }
    }
  }

  for (k = 0; k < 2004; k++) {
    cnvencd[k] = rt_remd_snf(b_y[k], 2.0);
  }

  /*  ӳ�� */
  memset(&s[0], 0, 4008U * sizeof(double));
  for (k = 0; k < 1000; k++) {
    s[((1 + k) << 2) - 4] = data[k];
  }

  s[(int)(4.0 * N + 1.0) - 1] = 0.0;
  s[(int)(4.0 * (N + 1.0) + 1.0) - 1] = 0.0;
  for (k = 0; k < 1000; k++) {
    s[((1 + k) << 2) - 3] = data[1000 + k];
  }

  s[(int)(4.0 * N + 2.0) - 1] = 0.0;
  s[(int)(4.0 * (N + 1.0) + 2.0) - 1] = 0.0;
  for (k = 0; k < 1002; k++) {
    s[((1 + k) << 2) - 2] = cnvencd[((1 + k) << 1) - 2];
    s[((1 + k) << 2) - 1] = cnvencd[((1 + k) << 1) - 1];
  }

  memcpy(&b_uu[0], &s[0], 4008U * sizeof(double));
  for (i0 = 0; i0 < 4; i0++) {
    for (k = 0; k < 1002; k++) {
      kk[k + 1002 * i0] = b_uu[i0 + (k << 2)];
    }
  }

  s16[0].re = -3;
  s16[0].im = 3;
  s16[4].re = 1;
  s16[4].im = -1;
  s16[8].re = -3;
  s16[8].im = -1;
  s16[12].re = 1;
  s16[12].im = 3;
  s16[1].re = -1;
  s16[1].im = 1;
  s16[5].re = 3;
  s16[5].im = -3;
  s16[9].re = -1;
  s16[9].im = -3;
  s16[13].re = 3;
  s16[13].im = 1;
  s16[2].re = -1;
  s16[2].im = -1;
  s16[6].re = 3;
  s16[6].im = 3;
  s16[10].re = -1;
  s16[10].im = 3;
  s16[14].re = 3;
  s16[14].im = -1;
  s16[3].re = -3;
  s16[3].im = -3;
  s16[7].re = 1;
  s16[7].im = 1;
  s16[11].re = -3;
  s16[11].im = 1;
  s16[15].re = 1;
  s16[15].im = -3;
  i0 = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = (int)(N + 2.0);
  emxEnsureCapacity((emxArray__common *)y, i0, (int)sizeof(creal_T));
  loop_ub = (int)(N + 2.0);
  for (i0 = 0; i0 < loop_ub; i0++) {
    y->data[i0].re = 0.0;
    y->data[i0].im = 0.0;
  }

  i0 = u1->size[0] * u1->size[1];
  u1->size[0] = 1;
  u1->size[1] = (int)(N + 2.0);
  emxEnsureCapacity((emxArray__common *)u1, i0, (int)sizeof(double));
  loop_ub = (int)(N + 2.0);
  for (i0 = 0; i0 < loop_ub; i0++) {
    u1->data[i0] = 0.0;
  }

  for (k = 0; k < 1002; k++) {
    /*  ����������ת��Ϊʮ������ */
    d0 = 0.0;
    for (i0 = 0; i0 < 4; i0++) {
      d0 += kk[k + 1002 * i0] * (double)b[i0];
    }

    u1->data[k] = d0;
    loop_ub = s16[(int)(u1->data[k] + 1.0) - 1].re;
    s16_im = s16[(int)(u1->data[k] + 1.0) - 1].im;
    y->data[k].re = loop_ub;
    y->data[k].im = s16_im;
  }

  emxFree_real_T(&u1);
}

/*
 * File trailer for t_16qam.c
 *
 * [EOF]
 */
