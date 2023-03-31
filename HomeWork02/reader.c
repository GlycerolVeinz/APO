#include <stdio.h>
#include <stdlib.h>

#define FALSE_START -1

#ifndef EXIT_SUCCESS
	#define EXIT_SUCCESS 0
#endif
#define ERR_FILE 100
#define ERR_PARAM 101
void err_ext(int err_code);


// MAIN--------------------------------------------------------------
int main(int argc, char const *argv[])
{
	if (argc <= 1) err_ext(FALSE_START);

	FILE *o_file = fopen(argv[1],"r+");
	if(!o_file) err_ext(ERR_FILE);

	char pp, six;
	int width, height, max_hue;
	if (5 != fscanf(o_file, "%c %c %d %d %d", &pp, &six, &width, &height, &max_hue)) err_ext(ERR_PARAM);
	if ((pp != 'P') || (six != '6') || max_hue != 255) err_ext(ERR_PARAM); 

	


	fclose(o_file);
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
	default:
		err_msg = "Error: this error is yet to be named\n";
		break;
	}
	fprintf(stderr, "%s", err_msg);
	exit(err_code);
}