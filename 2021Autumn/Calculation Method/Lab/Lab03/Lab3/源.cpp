#include<stdio.h>
#include<math.h>

double low = 0;
double high = 8;

double function(double x)
{
	return x / (1 + pow(x, 2));
}

double CompoundTrapezoid(double n)
{
	double result = 0;
	double length = high - low;
	double h = length / n;
	int k;
	for (k = 0; k < n; k++)
	{
		result += function(low + k * h) + function(low + (k + 1) * h);
	}
	result = result * h / 2;
	return result;
}

double CompoundSimpson(double n)
{
	double result = 0;
	double length = high - low;
	double h = length / n;
	double m = n / 2;

	for (int k = 0; k < m; k++)
	{
		result += function(low + (2 * k) * h) + 4 * function(low + (2 * k + 1) * h) + function(low + (2 * k + 2) * h);
	}
	result = result * h / 3;
	return result;
}

int main()
{
	double trueval = 0.5 * log(65);
	double curr;
	double result;
	double error;

	printf("CompoundTrapezoid\n");
	curr = CompoundTrapezoid(1);
	error = fabs(trueval - curr);
	printf("k=0 result=%.12E error=%.12E\n", curr, error);
	for (int k = 1; k <= 10; k++)
	{
		result = curr;
		curr = CompoundTrapezoid(pow(2,k));
		double error1 = fabs(trueval - result);
		double error2 = fabs(trueval - curr);
		double d = -1 * (log(error2) - log(error1)) / log(2);

		printf("k=%d result=%.12E error=%.12E d=%.4E\n", k, curr, error2, d);
	}

	printf("CompoundSimpson\n");
	curr = CompoundSimpson(1);
	printf("k=0 result=%.12E error=%.12E\n", curr, error);
	for (int k = 1; k <= 10; k++)
	{
		result = curr;
		curr = CompoundSimpson(pow(2, k));
		double error1 = fabs(trueval - result);
		double error2 = fabs(trueval - curr);
		double d = -1 * (log(error2) - log(error1)) / log(2);

		printf("k=%d result=%.12E error=%.12E d=%.4E\n", k, curr, error2, d);
	}
	return 0;
}