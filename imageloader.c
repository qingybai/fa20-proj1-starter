/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	Image *myinput;
	myinput = (Image *) malloc (sizeof (*myinput)+10);
	FILE *fp = fopen(filename,"r");
	char rubbish[20];
	fscanf(fp,"%s",rubbish);
	int cols,rows;
	fscanf(fp,"%d%d",&cols,&rows);
	myinput->cols=(unsigned) cols;
	myinput->rows=(unsigned) rows;
	fscanf(fp,"%s",rubbish);


	myinput->image = malloc (sizeof(Color*) * myinput->rows+10);
	for (int i = 0 ; i < (int) myinput->rows ; i++)
	{
		(myinput->image)[i] =  malloc (sizeof(Color) * myinput->cols +10);
		for (int j=0;j<myinput->cols;j++)
		{
			fscanf(fp,"%"SCNu8,&myinput->image[i][j].R);
			fscanf(fp,"%"SCNu8,&myinput->image[i][j].G);
			fscanf(fp,"%"SCNu8,&myinput->image[i][j].B);
		}
	}
	fclose(fp);
	return myinput;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	
	printf("P%d\n",3);
	printf("%d %d\n",(int) image->cols,(int) image->rows);
	printf("255\n");

	for (int i = 0;i<image->rows;i++)
	{
		for (int j = 0;j<image->cols;j++)
		{
			printf("%3u %3u %3u",image->image[i][j].R,image->image[i][j].G,image->image[i][j].B);
			if(j<image->cols-1) {printf("   ");}
		}
		printf("\n");
	}
	
	return;
}

//Frees an image


void freeImage(Image *image)
{
	for (int i=0;i<image->rows;i++)
	{
		free((image->image)[i]);
	}
	free(image->image);
	free(image);
	return;
}
/*
int main (void)

{
	char a[100]="testInputs/GliderGuns.ppm";

	Image* firstimg;
	firstimg = readData(a);
	writeData(firstimg);
	freeImage(firstimg);
	return 0;
}
*/