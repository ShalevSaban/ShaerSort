#ifndef SORT_H_
#define SORT_H_

#include "rectangle.h"

int shearSort(int *numberOfProcs, Rectangle* rectangle, RecType recType,int* counter);
void sortRow(Rectangle *rect, int left, int right, RecType recType, MPI_Status *status, int *numberOfProcs);
void sortCol(Rectangle *rect, int up, int down, RecType recType, MPI_Status *status, int *numberOfProcs);

#endif
