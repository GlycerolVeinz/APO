#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    FILE *o_file = fopen(argv[1],"r+b");
	if(!o_file) exit(-1);

	unsigned char width_line[15];	    
	int counter = -1;
	while (width_line[counter++] != '\n'){
		width_line[counter] = fgetc(o_file);
		if(width_line[counter] == EOF) exit(100);
        printf("%c", width_line[counter]);
	}
    width_line[counter] = fgetc(o_file);
    printf("%c", width_line[counter]);
    printf("\n");

    return 0;
}
