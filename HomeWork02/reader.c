#include <stdio.h>
#include <stdlib.h>

#define FALSE_START -1

#ifndef EXIT_SUCCESS
	#define EXIT_SUCCESS 0
#endif
#define ERR_FILE 100

void err_ext(int err_code);


// MAIN--------------------------------------------------------------
int main(int argc, char const *argv[])
{
	if (argc <= 1) err_ext(FALSE_START);

	FILE *o_file = fopen(argv[1],"bw");
	if(!o_file) ERR_FILE;

	
	
	return EXIT_SUCCESS;
}
// EO_MAIN--------------------------------------------------------------


void err_ext(int err_code){
	char *err_msg = "";
	switch (err_code)
	{
	case FALSE_START:
		err_msg = "Error: no file selected\n";
		break;

	case ERR_FILE:
		err_msg = "Error: could not open a file\n";
		break;
	}

	fprintf(stderr, "%s", err_msg);
	exit(err_code);
}