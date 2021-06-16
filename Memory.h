//---------------------------------------------------------------------------

#ifndef MemoryH
#define MemoryH
//---------------------------------------------------------------------------
#include "complex.h"
using namespace std;

#endif

void CreateArrayUC3(int DimentionSize[3],unsigned char*** &Array);
void DeleteArrayUC3(int DimentionSize[3],unsigned char*** &Array);
void CreateArrayInt3(int DimentionSize[3],int*** &Array);
void DeleteArrayInt3(int DimentionSize[3],int*** &Array);
void CreateArrayUC2(int DimentionSize0,int DimentionSize1,unsigned char** &Array);
void DeleteArrayUC2(int DimentionSize0,unsigned char** &Array);
void CreateArrayShort2(int DimentionSize0,int DimentionSize1,short** &Array);
void DeleteArrayShort2(int DimentionSize0,short** &Array);
void CreateArrayInt2(int DimentionSize0,int DimentionSize1,int** &Array);
void DeleteArrayInt2(int DimentionSize0,int** &Array);
void CreateArrayFloat2(int DimentionSize0,int DimentionSize1,float** &Array);
void DeleteArrayFloat2(int DimentionSize0,float** &Array);
void CreateArrayComplex2(int DimentionSize0,int DimentionSize1,complex<float>** &Array);
void DeleteArrayComplex2(int DimentionSize0,complex<float>** &Array);
void CreateArrayComplexD2(int DimentionSize0,int DimentionSize1,complex<double>** &Array);
void DeleteArrayComplexD2(int DimentionSize0,complex<double>** &Array);
