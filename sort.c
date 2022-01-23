#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#include "sort.h"
#include "rectangle.h"
#include "mpiCreate.h"


#define ROW_LOC 0
#define COL_LOC 1

#define MIN '<'
#define MAX '>'

int shearSort(int* numberOfProcs,Rectangle* rectangle,RecType recType,int* counter)
{
    int neighbors[4];

    MPI_Status status;
    MPI_Cart_shift(recType.comm, 1, 1,&neighbors[0], &neighbors[1]);
    MPI_Cart_shift(recType.comm, 0, 1, &neighbors[3], &neighbors[2]);
//    printf("rank %d [%d][%d]  (id = %d ) area :%lf  \n",*counter,recType.coord[0],recType.coord[1],rectangle->id ,(rectangle->hight)*(rectangle->width));

    printf("id %d  area %lf \n",rectangle->id,(rectangle->hight)*(rectangle->width));
    double iteration =4;           //log2(numberOfProcs)
    for (int i = 0; i < iteration;i++){
        if(i%2==0)
          sortRow(rectangle,neighbors[0],neighbors[1],recType,&status,numberOfProcs);///sort rows
        else
          sortCol(rectangle, neighbors[3], neighbors[2], recType, &status,numberOfProcs); //sort columns
    }
    sortRow(rectangle, neighbors[0], neighbors[1], recType, &status,numberOfProcs);
    //last iteration log(n)+1


    return rectangle->id;
}




void sortRow(Rectangle *rect, int left, int right, RecType recType, MPI_Status *status,int *numberOfProcs)
{

int rowSize=4;

for (int i=0 ;i<rowSize;i++)
{
    if (recType.coord[COL_LOC] % 2 != 0) // Check if the location odd
    {
       if(i%2==0) //if even iteration
         {
         if(recType.coord[ROW_LOC]%2==0)  //Check compare direction
             compare(rect, recType.rectDataType,left,status,MAX);   //Compare & swap if needed
         else
             compare(rect, recType.rectDataType, left, status, MIN);
         }
         else if (right != -1) //if there is a neighbor
         {
             if (recType.coord[ROW_LOC] % 2 == 0)
                 compare(rect, recType.rectDataType, right, status, MIN); //Compare & swap if needed

             else
                 compare(rect, recType.rectDataType, right, status, MAX);
        }
    }
    else //even location
    {
    if(i%2==0)
    {
        if(recType.coord[ROW_LOC]%2==0)
            compare(rect, recType.rectDataType, right, status, MIN);
        else
            compare(rect, recType.rectDataType, right, status, MAX);
    }
    else if (left != -1) //if there is a neighbor
    {
    if(recType.coord[ROW_LOC]%2==0)
        compare(rect, recType.rectDataType, left, status, MAX);
    else
        compare(rect, recType.rectDataType, left, status, MIN);
    }
    }
}
}

void sortCol(Rectangle *rect, int up, int down, RecType recType, MPI_Status *status, int *numberOfProcs)
{
    int colSize =4;

    for(int i=0;i<colSize;i++)
    {
        if(recType.coord[ROW_LOC]%2!=0)
        {
            if(i%2==0)
                compare(rect, recType.rectDataType, up, status, MAX);
            else if(down!=-1)
                compare(rect, recType.rectDataType, down, status, MIN);
        }
        else
        {
        if(i%2==0)
            compare(rect, recType.rectDataType, down, status, MIN);
        else if(up!=-1)
            compare(rect, recType.rectDataType, up, status, MAX);
        }
    }
}
