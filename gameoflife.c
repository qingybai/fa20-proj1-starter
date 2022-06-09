/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"
//#include "imageloader.c"
unsigned get_bit(unsigned x,
        			unsigned n) 
{
                     unsigned p,q;
                     q=1<<n;
                     p=x&q;
                     return p>>n;
    // YOUR CODE HERE
    // Returning -1 is a placeholder (it makes
    // no sense, because get_bit only returns 
    // 0 or 1)
}
// Set the nth bit of the value of x to v.
// Assume 0 <= n <= 31, and v is 0 or 1
// n=2,v=0,x=1111
void set_bit(unsigned * x,
             unsigned n,
             unsigned v) {
                 unsigned u=1;
                 u= u << n;
                 u= ~ u;
                 *x= *x & u;
                 v= v << n;
                 *x= *x | v;
                 return;
    // YOUR CODE HERE
}

//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	int left,right,up,down;
	left = (col==0)?           image->cols-1:col-1;
	right = (col==image->cols-1)?        0:col+1;
	up = (row==0)?             image->rows-1:row-1;
	down = (row==image->rows-1)?         0:row+1;
	Color *answer;
	answer = malloc (sizeof(Color)+1);
	//let's start with red
	unsigned newred=0;
	for (unsigned place =0;place<8;place++)
	{
		unsigned alive = get_bit(image->image[row][col].R,place)*9;
		unsigned sur = get_bit(image->image[up][left].R,place) +
						get_bit(image->image[row][left].R,place) +
						get_bit(image->image[down][left].R,place) +
						get_bit(image->image[up][col].R,place) +
						get_bit(image->image[down][col].R,place) +
						get_bit(image->image[up][right].R,place) +
						get_bit(image->image[row][right].R,place) +
						get_bit(image->image[down][right].R,place);
		unsigned rulebit = get_bit(rule,sur+alive);
		set_bit(&newred,place,rulebit);
	}
	answer->R=newred;
	//then do green
	unsigned newgreen=0;
	for (unsigned place =0;place<8;place++)
	{
		unsigned alive = get_bit(image->image[row][col].G,place)*9;
		unsigned sur = get_bit(image->image[up][left].G,place) +
						get_bit(image->image[row][left].G,place) +
						get_bit(image->image[down][left].G,place) +
						get_bit(image->image[up][col].G,place) +
						get_bit(image->image[down][col].G,place) +
						get_bit(image->image[up][right].G,place) +
						get_bit(image->image[row][right].G,place) +
						get_bit(image->image[down][right].G,place);
		unsigned rulebit = get_bit(rule,sur+alive);
		set_bit(&newgreen,place,rulebit);
	}
	answer->G=newgreen;
//  finally, blue
	unsigned newblue=0;
	for (unsigned place =0;place<8;place++)
	{
		unsigned alive = get_bit(image->image[row][col].B,place)*9;
		unsigned sur = get_bit(image->image[up][left].B,place) +
						get_bit(image->image[row][left].B,place) +
						get_bit(image->image[down][left].B,place) +
						get_bit(image->image[up][col].B,place) +
						get_bit(image->image[down][col].B,place) +
						get_bit(image->image[up][right].B,place) +
						get_bit(image->image[row][right].B,place) +
						get_bit(image->image[down][right].B,place);
		unsigned rulebit = get_bit(rule,sur+alive);
		set_bit(&newblue,place,rulebit);
	}
	answer->B=newblue;

	return answer;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
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
			Color * currentPixel = evaluateOneCell(image,i,j,rule);
			answer->image[i][j]=*currentPixel;
			free (currentPixel);
		}
	}
	return answer;
	
	//YOUR CODE HERE
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
/*
int main(void)
{	
	Image test;
	test.cols=3;
	test.rows=3;
	char argv[20][20];
	strcpy(argv[2],"0x1808");
	
	test.image = malloc (sizeof(Color*)*10);
	for (int i =0;i<3;i++)
	{
		test.image[i] = malloc (sizeof(Color)*10);
		for (int j =0;j<3;j++)
		{test.image[i][j].R=255;
		test.image[i][j].G=255;
		test.image[i][j].B=255;}
	}
	
	
	unsigned rule=0;
	int read =0;
	sscanf(argv[2],"%x",&read);
	rule = (unsigned) read;

	life (&test,rule);



	return 0;
}

*/
int main(int argc, char **argv)
{
	unsigned rule=0;
	int read =0;
	sscanf(argv[2],"%x",&read);
	rule = (unsigned) read;

	Image *input;
	input = readData(argv[1]);

	Image *output;
	output = life(input,rule);
	writeData(output);

	freeImage(input);
	freeImage(output);
	return 0;
}
