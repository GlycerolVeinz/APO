// LIBRARIES
#include <stdio.h>
#include <stdlib.h>

// ERRORS
#define FALSE_START -1
#ifndef EXIT_SUCCESS
	#define EXIT_SUCCESS 0
#endif
#define ERR_FILE 100
#define ERR_PARAM 101

// CONSTANTS
#define BIGGEST_PICTURE_RES 15
#define TO_INT(a) (a - 48)

// HEADERS
void err_ext(int err_code);
int size_reader(FILE *o_file);
void check_hue(FILE *o_file);
void check_file_type(FILE *o_file);

// MAIN--------------------------------------------------------------
int main(int argc, char const *argv[])
{
	if (argc <= 1) err_ext(FALSE_START);

	FILE *o_file = fopen(argv[1],"r+b");
	if(!o_file) err_ext(ERR_FILE);

	//check PPM header
	check_file_type(o_file);
	int width = size_reader(o_file);
	int height = size_reader(o_file);
	check_hue(o_file);

	//load img
	//compute convolution
	// compute histogram

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
	case ERR_PARAM:
		err_msg = "Error: wrong parametrs in header of a file.\n";
		break;
	default:
		err_msg = "Error: this error is yet to be named\n";
		break;
	}
	fprintf(stderr, "%s", err_msg);
	exit(err_code);
}

void check_file_type(FILE *o_file){
	char c = NULL;
	for (size_t i = 0; i < 3; ++i)
	{
		c = fgetc(o_file);
		if ((c != 'P') && (i == 0))err_ext(ERR_PARAM);
		if ((c != '6') && (i == 1))err_ext(ERR_PARAM);
		if ((c != '\n') && (i == 2));
	}

}

int size_reader(FILE *o_file){
	unsigned char size_line[BIGGEST_PICTURE_RES] = {0};
	int size = 0;
	int counter = -1;
	while (size_line[counter++] != '\n'){
		size_line[counter] = fgetc(o_file);
		if(size_line[counter] == EOF) err_ext(ERR_PARAM);
	}
	
	int tenth_pwr = 1;
	counter -= 2;
	do
	{
		size += (TO_INT(size_line[counter])) * tenth_pwr;
		tenth_pwr *= 10;
	} while (counter-- != 0);

	return size;
}

void check_hue(FILE *o_file){
	char c = NULL;
	for (size_t i = 0; i < 4; ++i)
	{
		c = fgetc(o_file);
		if ((TO_INT(c) != 2) && (i == 0))err_ext(ERR_PARAM);
		if ((TO_INT(c) != 5) && ((i == 1) || (i == 2)))err_ext(ERR_PARAM);
		if ((c != '\n') && (i ==3));
	}
}	

