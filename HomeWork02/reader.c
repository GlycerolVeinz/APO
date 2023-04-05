// LIBRARIES
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// ERRORS
#define FALSE_START -1
#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif
#define ERR_FILE 100
#define ERR_PARAM 101
#define ERR_MALOC 102

// CONSTANTS
#define BIGGEST_PICTURE_RES 15
#define RGB_PER_PXL 3
#define RED 0
#define GREEN 1
#define BLUE 2
#define HISTOGRRAM_RED 0.2126
#define HISTOGRAM_GREEN 0.7152
#define HISTOGRAM_BLUE 0.0722

// FORMULAS
#define TO_INT(a) (a - 48)

// HEADERS
void err_ext(int err_code);
int size_reader(FILE *input_file, FILE *output_file);
void check_hue(FILE *input_file, FILE *output_file);
void check_file_type(FILE *input_file, FILE *output_file);
void *checked_calloc(size_t num, size_t size);
void increment_histogram(int histogram[5], double histogram_val);

// MAIN--------------------------------------------------------------
int main(int argc, char const *argv[])
{
	// prep work (checking inputs)
	if (argc <= 1)
		err_ext(FALSE_START);

	FILE *input_file = fopen(argv[1], "rb");
	if (!input_file)
		err_ext(ERR_FILE);
	FILE *output_file = fopen("out.ppm", "wb");
	if (!output_file)
		err_ext(ERR_FILE);
	FILE *histogram_file = fopen("out.txt", "w");
	if (!histogram_file)
		err_ext(ERR_FILE);

	// check PPM header
	check_file_type(input_file, output_file);
	int width = size_reader(input_file, output_file);
	int height = size_reader(input_file, output_file);
	check_hue(input_file, output_file);

	// allocate mem for pictures
	unsigned char *in_img = checked_calloc(width * height * RGB_PER_PXL, sizeof(unsigned char));
	unsigned char *out_img = checked_calloc(width * height * RGB_PER_PXL, sizeof(unsigned char));
	int histogram[5] = {0};

// load img
#define COORD(x, y, z) (RGB_PER_PXL * ((y)*width + (x)) + (z))

#define LEFT_TO(x, y, z) (RGB_PER_PXL * ((y)*width + ((x)-1)) + (z))
#define ABOVE(x, y, z) (RGB_PER_PXL * (((y)-1) * width + (x)) + (z))
#define BELLOW(x, y, z) (RGB_PER_PXL * (((y) + 1) * width + (x)) + (z))
#define RIGHT_TO(x, y, z) (RGB_PER_PXL * ((y)*width + ((x) + 1)) + (z))

	for (int row = 0; row < height; ++row)
	{
		for (int collum = 0; collum < width; ++collum)
		{
			double histogram_val = 0;

			for (int rgb = 0; rgb < RGB_PER_PXL; ++rgb)
			{
				in_img[COORD(collum, row, rgb)] = fgetc(input_file);

				// compute histogram value
				double histogram_mul = 0;
				switch (rgb)
				{
				case RED:
					histogram_mul = HISTOGRRAM_RED;
					break;
				case GREEN:
					histogram_mul = HISTOGRAM_GREEN;
					break;
				case BLUE:
					histogram_mul = HISTOGRAM_BLUE;
					break;
				}
				histogram_val += histogram_mul * in_img[COORD(collum, row, rgb)];

				// compute convolution (need to have at least 3 rows)
				if ((collum == 0) || (row == 0) || (collum == (width - 1)) || (row == (height - 1)))
				{
					out_img[COORD(collum, row, rgb)] = in_img[COORD(collum, row, rgb)];
				}

				if ((row >= 2) && ((collum != 0) || (collum != (width - 1)))) // start at the 3rd line
				{
					out_img[COORD(collum, row - 1, rgb)] =
						(5 * (in_img[COORD(collum, row - 1, rgb)]) -
						 in_img[LEFT_TO(collum, row - 1, rgb)] -
						 in_img[RIGHT_TO(collum, row - 1, rgb)] -
						 in_img[ABOVE(collum, row - 1, rgb)] -
						 in_img[BELLOW(collum, row - 1, rgb)]) %
						255;
				}
			}
			increment_histogram(histogram, histogram_val);
		}
	}
	fclose(input_file);

	// safe histogram to out.txt
	fprintf(histogram_file, "%d %d %d %d %d", histogram[0], histogram[1], histogram[2], histogram[3], histogram[4]);
	fclose(histogram_file);

	// safe img to out.ppm
	for (int row = 0; row < height; ++row)
	{
		for (int collum = 0; collum < width; ++collum)
		{
			for (int rgb = 0; rgb < RGB_PER_PXL; ++rgb)
			{
				fputc(out_img[COORD(collum, row, rgb)], output_file);
			}
		}
	}
	fclose(output_file);

	free(in_img);
	free(out_img);
	exit(EXIT_SUCCESS);
}
// EO_MAIN--------------------------------------------------------------

// LOCAL FUNCTIONS -----------------------------------------------------

// FUNCTION -----------------------------------------------------------
void err_ext(int err_code)
{
	char *err_msg = "";
	switch (err_code)
	{
	case FALSE_START:
		err_msg = "Error: no file selected";
		break;

	case ERR_FILE:
		err_msg = "Error: could not open a file";
		break;
	case ERR_PARAM:
		err_msg = "Error: wrong parametrs in header of a file.";
		break;
	case ERR_MALOC:
		err_msg = "Error: malloc failed.";
		break;
	default:
		err_msg = "Error: this error is yet to be named";
		break;
	}
	fprintf(stderr, "%s\n", err_msg);
	exit(err_code);
}

// FUNCTION -----------------------------------------------------------
void check_file_type(FILE *input_file, FILE *output_file)
{
	unsigned char c = 0;
	for (size_t i = 0; i < 3; ++i)
	{
		c = fgetc(input_file);
		if ((c != 'P') && (i == 0))
			err_ext(ERR_PARAM);
		if ((c != '6') && (i == 1))
			err_ext(ERR_PARAM);
		if ((c != '\n') && (i == 2))
			;
		fputc(c, output_file);
	}
}

// FUNCTION -----------------------------------------------------------
int size_reader(FILE *input_file, FILE *output_file)
{
	unsigned char size_line[BIGGEST_PICTURE_RES] = {0};
	int size = 0;
	int counter = 0;
	do
	{
		size_line[counter] = fgetc(input_file);
		if (size_line[counter] == EOF)
			err_ext(ERR_PARAM);
		fputc(size_line[counter], output_file);
	} while (size_line[counter++] != '\n');

	int tenth_pwr = 1;
	counter -= 2;
	do
	{
		size += (TO_INT(size_line[counter])) * tenth_pwr;
		tenth_pwr *= 10;
	} while (counter-- != 0);

	return size;
}

// FUNCTION -----------------------------------------------------------
void check_hue(FILE *input_file, FILE *output_file)
{
	char c = 0;
	for (size_t i = 0; i < 4; ++i)
	{
		c = fgetc(input_file);
		if ((TO_INT(c) != 2) && (i == 0))
			err_ext(ERR_PARAM);
		if ((TO_INT(c) != 5) && ((i == 1) || (i == 2)))
			err_ext(ERR_PARAM);
		if ((c != '\n') && (i == 3))
			;
		fputc(c, output_file);
	}
}

// FUNCTION -----------------------------------------------------------
void *checked_calloc(size_t num, size_t size)
{
	void *ret = calloc(num, size);
	if (!ret)
		err_ext(ERR_MALOC);
	return ret;
}

void increment_histogram(int histogram[5], double histogram_val)
{
	histogram_val = round(histogram_val);
	if ((0 <= histogram_val) && (histogram_val <= 50))
	{
		++(histogram[0]);
	}
	else if ((51 <= histogram_val) && (histogram_val <= 101))
	{
		++(histogram[1]);
	}
	else if ((102 <= histogram_val) && (histogram_val <= 152))
	{
		++(histogram[2]);
	}
	else if ((153 <= histogram_val) && (histogram_val <= 203))
	{
		++(histogram[3]);
	}
	else if ((204 <= histogram_val) && (histogram_val <= 255))
	{
		++(histogram[4]);
	}
}
