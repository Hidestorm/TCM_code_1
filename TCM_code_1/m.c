#include <float.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "t_16qam_types.h"
#include "rt_nonfinite.h"
#include "t_16qam.h"
#include "t_16qam_terminate.h"
#include "t_16qam_emxAPI.h"
#include "t_16qam_initialize.h"
#include "rtGetInf.h"
#include "rtGetNaN.h"
#include "t_16qam_emxutil.h"
#include <stdio.h>
int main()
{
	double dvo[3000];
//	int data[3000];
	emxArray_creal_T *y;
	emxInitArray_creal_T(&y, 2);
	/*myInitArray_creal_T(&y, 1002);*/

	double  N = 1000;
	FILE *p;
	errno_t  fp = fopen_s(&p, "data.txt", "r");
	if (!p)
	{
		printf("can't open file\n");
		return -1;
	}
	for (int i = 0; i < 3000; i++)
	{
		int d = 3;
		fscanf_s(p, "%d", &d);
		if (d == 0 || d == 1)
			dvo[i] = d;
		else
			i--;
	}
//	fscanf_s(p, "%d", &dvo);
	t_16qam(dvo, N, y);
	fp = fclose(p);
	FILE *r;
	errno_t rp = fopen_s(&r, "result.txt", "w");
	if (rp == 0)
	{
		printf("The file 'data2' was opened\n");
		for (int i = 0; i < 1002; i++)
		{
			fprintf(r, "%d",(int) y->data[i].re);
			putchar((int)y->data[i].re);
			fputc(' ', r);
		//	fputc(y->data[i].im, r);
			fprintf(r, "%d",(int) y->data[i].im);
			fputc('i', r);
			fputc('\n', r);
		}
	}
	else
	{
		printf("The file 'data2' was not opened\n");
	}

	emxDestroyArray_creal_T(y);
	system("pause");
}