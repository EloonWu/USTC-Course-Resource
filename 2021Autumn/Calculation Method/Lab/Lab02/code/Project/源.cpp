#include<stdio.h>
#include<math.h>
#define e 2.718281828
#define epslion 1e-8

double PrimitiveFunction(double x)
{
	return pow(2, -x) + pow(e, x) + 2 * cos(x) - 6;
}

double DerivativeFunction(double x)
{
	return -1 * pow(2, -x) * log(2) + pow(e, x) - 2 * sin(x);
}

void NewtonMethod(double x)
{
	int k = 0;
	while (fabs(PrimitiveFunction(x)) >= epslion)
	{
		printf("k=%d	x%d=%0.10f		f(x)=%0.10f\n", k, k, x, PrimitiveFunction(x));
		x = x - PrimitiveFunction(x) / DerivativeFunction(x);
		k++;
	}
	printf("k=%d	x%d=%0.10f		f(x)=%0.10f\n", k, k, x, PrimitiveFunction(x));
}

double Half(double x, double y)
{
	x = x * 10000000;
	y = y * 10000000;
	return (x + y) / 20000000;
}

void BisectionMethod(double low, double high)
{
	int k = 0;
	double root = (low + high) / 2;
	double left = PrimitiveFunction(low);
	double right = PrimitiveFunction(high);
	double middle = PrimitiveFunction(root);
	while (fabs(middle) >= epslion)
	{
		printf("k=%d	[%0.10f,%0.10f]		root=%0.10f		f(x)=%0.10f\n", k, low, high, root, middle);
		if ((middle <epslion && right > epslion)||(middle > epslion && right < epslion))
		{
			low = root;
			root = Half(low, high);
			left = PrimitiveFunction(low);
			middle = PrimitiveFunction(root);
			k++;
		}
		else
		{
			if ((middle <epslion && left > epslion) || (middle > epslion&& left < epslion))
			{
				high = root;
				root = Half(low, high);
				right = PrimitiveFunction(high);
				middle = PrimitiveFunction(root);
				k++;
			}
			else
			{
				printf("ERROR!\n");
				break;
			}
		}
	}
	printf("k=%d	[%0.10f,%0.10f]		root=%0.10f		f(x)=%0.10f\n", k, low, high, root, middle);
}

int main()
{
	double x1, x2;
	double low, high;
	scanf_s("%lf %lf", &x1, &x2);
	scanf_s("%lf %lf", &low, &high);

	printf("Newton Method for x1\n");
	NewtonMethod(x1);
	printf("\n");

	printf("Newton Method for x2\n");
	NewtonMethod(x2);
	printf("\n");


	printf("Bisection Method\n");
	BisectionMethod(low, high);
	return 0;
}