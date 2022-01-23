
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stddef.h>
#include "mpi.h"

#include "rectangle.h"
#include "mpiCreate.h"
#include "sort.h"



#define FILE_NAME "rectangles.dat"
#define FINISH_FILE "result.dat"

#define  NUM_OF_RECTANGLES 16
#define NUM_OF_ATTRIBUTES 3



#define ROWS 4
#define COLUMNS 4

int main(int argc, char *argv[])
{

	int rank;
	Rectangle *recArray;
	int *sortedArea = (int *)malloc(sizeof(int)*16);
	int numOfProcs=16;
	RecType rectType;

	InitMPI(&argc, &argv, &rank, &numOfProcs, &rectType);
	Rectangle newRect;


	if(rank==0)
	{
	recArray = readRecFromFile(FILE_NAME, NUM_OF_RECTANGLES);
	printf("Read File....\n ");
	MPI_Scatter(recArray, 1, rectType.rectDataType, &newRect, 1, rectType.rectDataType, 0, MPI_COMM_WORLD);
	printf("Start Sorting...\n ");
	}
	else
	MPI_Scatter(NULL, 0, rectType.rectDataType,&newRect, 1, rectType.rectDataType, 0, MPI_COMM_WORLD);



    int newPlace=shearSort(&numOfProcs,&newRect,rectType,&rank);
	MPI_Gather(&newPlace, 1, MPI_INT, sortedArea, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Barrier(rectType.comm);


    if (rank==0)
    {
        WriteToFile(FINISH_FILE, sortedArea, numOfProcs);
    	printf("Sorting is over . \n Results were written to the file .");
    }



	MPI_Finalize();
	return 0;
}

