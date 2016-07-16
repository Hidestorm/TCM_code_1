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
static void argInit_1000x3_real_T(double result[3000])
{
	int idx0;
	int idx1;
	FILE *p;
	errno_t  fp = fopen_s(&p, "data.txt", "r");
	if (!p)
	{
		printf("can't open file\n");
		return ;
	}
	/* Loop over the array to initialize each element. */
	for (idx0 = 0; idx0 < 1000; idx0++) {
		for (idx1 = 0; idx1 < 3; idx1++) {
			/* Set the value of the array element.
			Change this value to the value that the application requires. */
			int d = 3;
			fscanf_s(p, "%d", &d);
			result[idx0 + 1000 * idx1] = d;
		}
	}
}

int main()
{
	double dvo[3000];
	emxArray_creal_T *y;
	emxInitArray_creal_T(&y, 2);

	double  N = 1000;
	//FILE *p;
	//errno_t  fp = fopen_s(&p, "data.txt", "r");
	//if (!p)
	//{
	//	printf("can't open file\n");
	//	return -1;
	//}
	//for (int i = 0; i < 3000; i++)
	//{
	//	int d = 3;
	//	fscanf_s(p, "%d", &d);
	//	if (d == 0 || d == 1)
	//		dvo[i] = d;
	//	else
	//		i--;
	//}
	//fp = fclose(p);
	
	argInit_1000x3_real_T(dvo);
	t_16qam(dvo, N, y);
	
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
			//fputc('i', r);
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