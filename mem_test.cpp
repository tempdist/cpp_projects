#include <stdio.h>
#include <stdlib.h>

int main() 
{
	int *ptrc = (int *)calloc(10, sizeof(int));
	int *ptrm = (int *)malloc(10);
	for(int i = 0; i < 10; i++) {
		printf("%d calloc: %d malloc: %d\n", i, *ptrc++,*ptrm++);
	}
	return 0;
}