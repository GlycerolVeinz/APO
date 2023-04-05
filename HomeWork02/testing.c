#include <stdio.h>
#include <stdlib.h>
#define RGB_PER_PXL 3

int main(int argc, char const *argv[])
{
	int width = 3;
	#define COORD(y,x,z) (RGB_PER_PXL * (y * width + x) + z)
						
	printf("%d\n", COORD(1,2,2));
    return 0;
}
