//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Memory.h"
#include "complex.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

void CreateArrayUC3(int DimentionSize[3],unsigned char*** &Array)
{
Array=new unsigned char**[DimentionSize[0]];
for(int i=0;i<DimentionSize[0];i++)
  {
  Array[i]=new unsigned char*[DimentionSize[1]];
  for(int j=0;j<DimentionSize[1];j++)
    {
    Array[i][j]=new unsigned char[DimentionSize[2]];
    ZeroMemory(Array[i][j],DimentionSize[2]);
    }
  }
}

void DeleteArrayUC3(int DimentionSize[3],unsigned char*** &Array)
{
for(int i=0;i<DimentionSize[0];i++)
  {
  for(int j=0;j<DimentionSize[1];j++)
    delete[] Array[i][j];
  delete[] Array[i];
  }
delete[] Array;
}

void CreateArrayInt3(int DimentionSize[3],int*** &Array)
{
Array=new int**[DimentionSize[0]];
for(int i=0;i<DimentionSize[0];i++)
  {
  Array[i]=new int*[DimentionSize[1]];
  for(int j=0;j<DimentionSize[1];j++)
    {
    Array[i][j]=new int[DimentionSize[2]];
    ZeroMemory(Array[i][j],DimentionSize[2]*4);
    }
  }
}

void DeleteArrayInt3(int DimentionSize[3],int*** &Array)
{
for(int i=0;i<DimentionSize[0];i++)
  {
  for(int j=0;j<DimentionSize[1];j++)
    delete[] Array[i][j];
  delete[] Array[i];
  }
delete[] Array;
}
// 2D arrays

void CreateArrayUC2(int DimentionSize0,int DimentionSize1,unsigned char** &Array)
{
Array=new unsigned char*[DimentionSize0];
for(int i=0;i<DimentionSize0;i++)
  {
  Array[i]=new unsigned char[DimentionSize1];
  ZeroMemory(Array[i],DimentionSize1);
  }
}

void DeleteArrayUC2(int DimentionSize0,unsigned char** &Array)
{
for(int i=0;i<DimentionSize0;i++)
  delete[] Array[i];
delete[] Array;
}
void CreateArrayShort2(int DimentionSize0,int DimentionSize1,short** &Array)
{
Array=new short*[DimentionSize0];
for(int i=0;i<DimentionSize0;i++)
  {
  Array[i]=new short[DimentionSize1];
  ZeroMemory(Array[i],DimentionSize1*2);
  }
}
void DeleteArrayShort2(int DimentionSize0,short** &Array)
{
for(int i=0;i<DimentionSize0;i++)
  delete[] Array[i];
delete[] Array;
}
void CreateArrayInt2(int DimentionSize0,int DimentionSize1,int** &Array)
{
Array=new int*[DimentionSize0];
for(int i=0;i<DimentionSize0;i++)
  {
  Array[i]=new int[DimentionSize1];
  ZeroMemory(Array[i],DimentionSize1*4);
  }
}
void DeleteArrayInt2(int DimentionSize0,int** &Array)
{
for(int i=0;i<DimentionSize0;i++)
  delete[] Array[i];
delete[] Array;
}
void CreateArrayFloat2(int DimentionSize0,int DimentionSize1,float** &Array)
{
Array=new float*[DimentionSize0];
for(int i=0;i<DimentionSize0;i++)
  {
  Array[i]=new float[DimentionSize1];
  ZeroMemory(Array[i],DimentionSize1*4);
  }
}
void DeleteArrayFloat2(int DimentionSize0,float** &Array)
{
for(int i=0;i<DimentionSize0;i++)
  delete[] Array[i];
delete[] Array;
}
void CreateArrayComplex2(int DimentionSize0,int DimentionSize1,complex<float>** &Array)
{
Array=new complex<float>*[DimentionSize0];
for(int i=0;i<DimentionSize0;i++)
  {
  Array[i]=new complex<float>[DimentionSize1];
  ZeroMemory(Array[i],DimentionSize1*8);
  }
}
void DeleteArrayComplex2(int DimentionSize0,complex<float>** &Array)
{
for(int i=0;i<DimentionSize0;i++)
  delete[] Array[i];
delete[] Array;
}
void CreateArrayComplexD2(int DimentionSize0,int DimentionSize1,complex<double>** &Array)
{
Array=new complex<double>*[DimentionSize0];
for(int i=0;i<DimentionSize0;i++)
  {
  Array[i]=new complex<double>[DimentionSize1];
  ZeroMemory(Array[i],DimentionSize1*8);
  }
}
void DeleteArrayComplexD2(int DimentionSize0,complex<double>** &Array)
{
for(int i=0;i<DimentionSize0;i++)
  delete[] Array[i];
delete[] Array;
}




