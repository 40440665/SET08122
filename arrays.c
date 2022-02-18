#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) 
{	
	// Initialize first year grades array
	int firstYearGrades[6] = {50, 60, 45, 73, 49, 83};
	
	// Calculate the length of first year grades array
	int length = sizeof(firstYearGrades)/sizeof(firstYearGrades[0]);
	
	// Initialize array for all grades
	int allGrades[9] = {0, 0, 0, 0, 0, 0, 44, 86, 77};
	
	for(int i = 0;  i < length; i++)
	{	
		allGrades[i] = firstYearGrades[i];
	}
	
	// Reset length to the length of the new array
	length = sizeof(allGrades)/sizeof(allGrades[0]);
		
	// For loop to print each element in an array
	for (int i = 0; i < length; i++)
	{
		printf("%d ", allGrades[i]);
	}
	
	return 0;
}