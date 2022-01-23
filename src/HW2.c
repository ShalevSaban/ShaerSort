/*
 ============================================================================
 Name        : HW2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello MPI World in C 
 ============================================================================
 */
#include <stdio.h>
#include <string.h>
#include "mpi.h"
#define FILE_NAME "rectangles.dat.txt"

int main(int argc, char* argv[]){
	int  my_rank; /* rank of process */
	int  p;       /* number of processes */
	int source;   /* rank of sender */
	int dest;     /* rank of receiver */
	int tag=0;    /* tag for messages */
	char message[100];        /* storage for message */
	MPI_Status status ;   /* return status for receive */
	FILE *fp;
	int *points;


	/* start up MPI */
	
	MPI_Init(&argc, &argv);
	
	/* find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 
	
	/* find out number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &p); 
	
	
	if (my_rank !=0){
		/* create message */
		dest = 0;
		/* use strlen+1 so that '\0' get transmitted */

	

		// Open file for reading points
		if ((fp = fopen(FILE_NAME, "r")) == 0)
		{
			printf("cannot open file %s for reading\n", FILE_NAME);
			exit(0);
		}

		// Number of points
		fscanf(fp, "%d", 10);

		// Allocate array of points end Read data from the file
		points = (int *)malloc(10 * sizeof(int));
		if (points == NULL)
		{
			printf("Problem to allocate memotry\n");
			exit(0);
		}
		for (int i = 0; i < 10; i++)
		{
			fscanf(fp, "%d", &points[i]);
			printf(points[i]);
		}

		fclose(fp);

		MPI_Send(message, strlen(message)+1, MPI_CHAR,
		   dest, tag, MPI_COMM_WORLD);



	}
	else{





		for (source = 1; source < p; source++) {
			MPI_Recv(message, 100, MPI_CHAR, source, tag,
			      MPI_COMM_WORLD, &status);
			printf("%s\n",message);
		}
	}
	/* shut down MPI */
	MPI_Finalize(); 
	
	
	return 0;
}
