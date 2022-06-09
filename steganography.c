/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				YOUR NAME HERE
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h" 
 
//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
	Color *answer;
	answer = malloc (sizeof(Color)+1);
	int blue = image->image[row][col].B;
	if(blue%2==0)
	{
		answer->R = answer->G = answer->B=0;
	}
	else
	{
		answer->R = answer->G = answer->B=255;
	}
	return answer;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	Image* answer;
	answer = malloc (sizeof(Image)+10);
	answer->cols=image->cols;
	answer->rows=image->rows;
	
	answer->image = malloc (sizeof(Color*)*answer->rows+10);
	for(int i =0;i<answer->rows;i++)
	{
		answer->image[i] = malloc (sizeof(Color)*answer->cols+10);
		for(int j =0;j<answer->cols;j++)
		{
			Color * currentPixel = evaluateOnePixel(image,i,j);
			answer->image[i][j]=*currentPixel;
			free (currentPixel);
		}
	}
	return answer;
	//YOUR CODE HERE
}

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
	Image *input;
	input = readData(argv[1]);
	Image *output;
	output = steganography(input);
	writeData(output);
	freeImage(input);
	freeImage(output);
	return 0;
}
