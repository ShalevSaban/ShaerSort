#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#include "rectangle.h"
#include "mpiCreate.h"

#define MIN '<'
#define MAX '>'



Rectangle *readRecFromFile(char *fileName, int number)
{
    Rectangle *recArray;
    FILE *fp;

    if ((fp = fopen(fileName, "r")) == 0)
    {
        printf("cannot open file %s for reading\n", fileName);
        exit(0);
    }

    // Allocate array of points end Read data from the file
    recArray = (Rectangle *)malloc(number * sizeof(Rectangle));
    if (recArray == NULL)
    {
        printf("Problem to allocate memotry\n");
        exit(0);
    }
    for (int i = 0; i < number; i++)
        fscanf(fp, "%d %lf %lf ", &recArray[i].id, &recArray[i].hight, &recArray[i].width);


    fclose(fp);
    return recArray;
}



float calcArea(Rectangle *rectangle)
{
    return (rectangle->hight) * (rectangle->width);
}



void compare(Rectangle *rect, MPI_Datatype rectType, int otherPos, MPI_Status *status, char compare)
{
    Rectangle otherRect;

    MPI_Send(rect, 1, rectType, otherPos, 0, MPI_COMM_WORLD);
    MPI_Recv(&otherRect, 1, rectType, otherPos, 0, MPI_COMM_WORLD, status);

swap(rect,&otherRect,compare);
}


void swap(Rectangle *rect,Rectangle *otherRect,char method)
{
    float rect1=calcArea(rect);
    float rect2=calcArea(otherRect); //calc second rectangle are

    switch (method)
{
    case MAX:
        if(rect1<rect2)
        {
            copyRectData(rect, otherRect); //set rect 1 like 2
        }
        break;

    case MIN:
        if(rect1>rect2)
            copyRectData(rect, otherRect);
          break;
}
}

void copyRectData(Rectangle *rect, Rectangle *otherRect)
{
    rect->id = otherRect->id;
    rect->width = otherRect->width;
    rect->hight = otherRect->hight;
}


void WriteToFile(const char* fileName, int* results, int numOfRects)
{
	FILE* fp;

	int start = 0, finish = 0, direct = 0;

	if ((fp = fopen(fileName, "w")) == NULL)   // open file
		MPI_Abort(MPI_COMM_WORLD, 2);

//	int size =(int)sqrt(numOfRects);
    int size=4;
	for(int i=0;i<size;i++)
	{
	if(i%2==1)
		start=size-1,finish=0,direct=-1;
	else
		start=0 ,finish=size-1,direct=1;

	writePack(fp, results, i*size, start, finish, direct);

	}
}

	void writePack(FILE* fp, int* results, int k, int start, int finish, int direct)
	{
		for (int i=start*direct;i<=finish;i++)
			fprintf(fp, "%d ", *(results + abs(i)+k));
	}










