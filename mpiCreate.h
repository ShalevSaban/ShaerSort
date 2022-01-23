#ifndef MPIC_H_
#define MPIC_H_


void InitMPI(int *argc, char **argv[], int *rank, int *numOfProcs, RecType* dataT);
void createRectType(MPI_Datatype* rectType);
MPI_Comm createCartComm(int rank, int* numOfProcs, RecType* dataT);

#endif
