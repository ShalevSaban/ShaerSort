#ifndef RECTANGLE_H_
#define RECTANGLE_H_


//Id, Height, Width

typedef struct Rectangle
{
   int id;
   double hight;
   double width;
} Rectangle;



typedef struct RecType
{
   int coord[2];
   MPI_Datatype rectDataType;
   MPI_Comm comm;
} RecType;



Rectangle   *readRecFromFile(char *fileName, int number);
float       calcArea(Rectangle *rectangle);
void        compare(Rectangle *rect, MPI_Datatype rectType, int otherPos, MPI_Status *status,char compare);
void        swap(Rectangle *rect, Rectangle *otherRect, char method);
void        copyRectData(Rectangle *rect, Rectangle *otherRect);
void 		WriteToFile(const char* fileName, int* results, int numOfRects);
void 		writePack(FILE* fp, int* results, int k, int start, int finish, int direct);



#endif
