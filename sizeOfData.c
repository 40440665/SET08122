#include <stdio.h>

int main()
{
	// Create Variables of different data types
	int integerVariable;
	char charVariable;
	long longVariable;
	float floatVariable;
	double doubleVariable;
	int a[100];
	
	size_t s = sizeof(a);
	printf("%zu bytes\n", s);
	
	size_t num = s/sizeof(int);
	printf("space for storing %zu elements\n", num);
	
	// Print each variables size in bytes using sizeof
	printf("Size of Integer Variable is %zu bytes\n", sizeof(integerVariable));
	printf("Size of Char Varibale is %zu bytes\n", sizeof(charVariable));
	printf("Size of Long Variable is %zu bytes\n", sizeof(longVariable));
	printf("Size of Float Variable is %zu bytes\n", sizeof(floatVariable));
	printf("Size of Double Variable is %zu bytes\n", sizeof(doubleVariable));
	
	return 0;
}