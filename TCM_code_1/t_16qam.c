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
 * 16QAM的TCM编码程序
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

  /* 编码比特 */
  memcpy(&z[0], &data[2000], 1000U * sizeof(double));

  /*  cnv_encd(G,k0,input),k0是每一时钟周期输入编码器的bit数， */
  /*  G是决定输入序列的生成矩阵，它有n0行L*k0列n0是输出bit数， */
  /*  参数n0和L由生成矩阵G导出，L是约束长度。L之所以叫约束长度 */
  /*  是因为编码器在每一时刻里输出序列不但与当前输入序列有关， */
  /*  而且还与编码器的状态有关，这个状态是由编码器的前(L-1)k0。 */
  /*  个输入决定的,通常卷积码表示为(n0,k0,m)，m=(L-1)*k0是编码 */
  /*  器中的编码存贮个数，也就是分为L-1段，每段k0个 */
  /*  有些人将m=L*k0定义为约束长度，有的人定义为m=(L-1)*k0 */
  /*  查看是否需要补0，输入input必须是k0的整数部  */
  /*  检查生成矩阵G的维数是否和k0一致  */
  /*  得到约束长度L和输出比特数n0 */
  /*  在信息前后加0，使存贮器归0，加0个数为(L-1)*k0个 */
  for (i0 = 0; i0 < 2; i0++) {
    u[i0] = 0.0;
  }

  memcpy(&u[2], &z[0], 1000U * sizeof(double));
  for (i0 = 0; i0 < 2; i0++) {
    u[i0 + 1002] = 0.0;
  }

  emxInit_real_T(&u1, 2);

  /*  得到uu矩阵,它的各列是编码器各个存贮器在各时钟周期的内容  */
  i0 = u1->size[0] * u1->size[1];
  u1->size[0] = 1;
  u1->size[1] = 3;
  emxEnsureCapacity((emxArray__common *)u1, i0, (int)sizeof(double));
  for (i0 = 0; i0 < 3; i0++) {
    u1->data[i0] = u[2 - i0];
  }

  /* 将加0后的输入序列按每组L*k0个分组，分组是按一比特增加 */
  /* 从1到L*k0比特为第一组，从2到L*k0+1为第二组，。。。。， */
  /* 并将分组按倒序排列。  */
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

  /*  得到输出，输出由生成矩阵G*uu得到 */
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

  /*  映射 */
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
    /*  将二进制数转化为十进制数 */
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
