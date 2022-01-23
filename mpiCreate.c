#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <stddef.h>

#include "rectangle.h"

#define NUM_OF_ATTRIBUTES 3

void InitMPI(int *argc, char **argv[], int *rank, int *numOfProcs, RecType* dataT)
{
    MPI_Init(argc, argv);
    MPI_Comm_rank(MPI_COMM_WORLD, rank);
    MPI_Comm_size(MPI_COMM_WORLD, numOfProcs);

    createRectType(&dataT->rectDataType);

    dataT->comm = createCartComm(*rank,numOfProcs, dataT);
}

void createRectType(MPI_Datatype* rectType)
{
    int blockLen[NUM_OF_ATTRIBUTES] = {1, 1, 1};
    MPI_Aint disp[NUM_OF_ATTRIBUTES];
    MPI_Datatype types[NUM_OF_ATTRIBUTES] = {MPI_INT, MPI_DOUBLE, MPI_DOUBLE};

    disp[0] = offsetof(Rectangle, id);
    disp[1] = offsetof(Rectangle, hight);
    disp[2] = offsetof(Rectangle, width);

    MPI_Type_create_struct(NUM_OF_ATTRIBUTES, blockLen, disp, types,rectType);
    MPI_Type_commit(rectType);
}

MPI_Comm createCartComm(int rank, int* numOfProcs, RecType* dataT)
{
    MPI_Comm cartComm;
    int reorder=1;
    int size = sqrt(16);

    int dims[2]={size,size};
    int period[2]={0,0};


    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, period, reorder, &cartComm);
    MPI_Cart_coords(cartComm, rank, 2, &dataT->coord);

    return cartComm;
}
