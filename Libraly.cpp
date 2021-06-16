//---------------------------------------------------------------------------


#pragma hdrstop

#include "Unit9.h"
#include <vcl.h>
#pragma hdrstop
#include <fstream>
#include <complex.h>
#include "ForMenyu1.h"
#include "Forma.h"
#include "Imagebase.h"
#include "bmpfile.h"
#include "anyfile.h"
#include "memory.h"
#include "fill.h"
#include "Translate.h"
#include "bmpfile.h"
#include "Libraly.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
void GridYar(TImage* Image1,int indent, int N, float maxA, float maxi)//нпнесение сетки на график
{
	int  dob=(int)(N/(Image1->Height-2*indent)*2);
	dob++ ;
	int step=(Image1->Height-2*indent)/6  ;
	int step1=N/dob/6;

	Image1->Canvas->Pen->Color=clGreen;
	float stepi=maxA/maxi;
	float stepA=(int)(stepi*100000);
	//float stepA=float(tmp/1000/6);



	//float maxo=(int)(max*1000);
  //Image1->Canvas->TextOutA(Image1->Width/2,0,maxo/1000);
	for(int i=0;i<=6;i++)
	{
	Image1->Canvas->MoveTo(indent+step1*i,Image1->Height-indent);
	Image1->Canvas->LineTo(indent+step1*i,indent);
	Image1->Canvas->MoveTo(indent,Image1->Height-indent-step*i);
	Image1->Canvas->LineTo(indent+N/dob,Image1->Height-indent-step*i);
	//Image1->Canvas->TextExtent(28);
	//Image1->Canvas->
	Image1->Canvas->TextOutA(indent+step1*i-5,Image1->Height-indent+5,i*42);
	Image1->Canvas->TextOutA(5,Image1->Height-indent-step*i-5,i*stepA/10);
	//Image1->Canvas->TextOutA(indent/2,indent/2,);
	}

}
 int maxEl1(float*buf, int sizebuf)
 {
	 int max=1;
	 for(int i=0;i<sizebuf;i++)
	 if (buf[max]<buf[i])
	 {
		max=i;
	 }
 return max;
 }
 float maxEl(float*buf, int sizebuf)
 {
	 float max=buf[0];
	 for(int i=0;i<sizebuf;i++)
	 if (max<buf[i])
	 {
		max=buf[i];
	 }
 return max;
 }
void ClearImage(TImage* Image1)
{
	Image1->Canvas->Pen->Color=clBlack;
	Image1->Canvas->Brush->Color=clWhite;
	Image1->Canvas->Rectangle(0,0,Image1->Width,Image1->Height);
}

void ArrowGr(int indent, TImage* Image1)
{

	Image1->Canvas->Pen->Color=clBlack;
	//Image1->Width=300;
	//Image1->Height=300;
	
	Image1->Canvas->MoveTo(indent,indent);
	Image1->Canvas->LineTo(indent,Image1->Height-indent);
	Image1->Canvas->LineTo(Image1->Width-indent,Image1->Height-indent);
	Image1->Canvas->MoveTo(indent-5,indent+10);
	Image1->Canvas->LineTo(indent,indent);
	Image1->Canvas->LineTo(indent+5,indent+10);
	Image1->Canvas->MoveTo(Image1->Width-indent-10,Image1->Height-indent+5);
	Image1->Canvas->LineTo(Image1->Width-indent,Image1->Height-indent);
	Image1->Canvas->LineTo(Image1->Width-indent-10,Image1->Height-indent-5);
}
void GraficTA(int indent,TColor Col1,TColor Col2, complex<float>** array,complex<float>** array2, int numx,int  T,TImage* Image1)
{

  int  dob=(int)(T/(Image1->Height-2*indent)*2);
  dob++;
  float *buf=new float[T];
  for(int i=0; i<=T;i++)
  {
	  buf[i]=abs(array[numx][i]);
  }
  int max=maxEl1(buf,T+1);
  float *buf2=new float[T];
  for(int i=0; i<=T;i++)
  {
	  buf2[i]=abs(array2[numx][i]);
  }
  int max2=maxEl1(buf2,T+1);
  float MAX;
  if(buf2[max2]>buf[max])
  {MAX=buf2[max2];}
  else {MAX=buf[max];}
  ClearImage(Image1);
  GridYar(Image1,indent, T, MAX, 6)  ;
  ArrowGr(indent,Image1);
  //float maxo=(int)(max*1000);
  //Image1->Canvas->TextOutA(Image1->Width/2,0,maxo/1000);

	for(int i=0; i<=(int)(T/dob);i++)
  {
	  buf[i*dob]=buf[i*dob]/MAX*(Image1->Height-2*indent);
  }
	for(int i=0; i<=(int)(T/dob);i++)
  {
	  buf2[i*dob]=buf2[i*dob]/MAX*(Image1->Height-2*indent);
  }
  Image1->Canvas->Pen->Color=Col1;
  Image1->Canvas->MoveTo(indent,Image1->Height-indent+(int)buf[0]);
  for(int i=1;i<=(int)(T/dob);i++)
  {
  Image1->Canvas->LineTo(indent+i,Image1->Height-indent-(int)buf[i*dob]);
  }
  Image1->Canvas->Pen->Color=Col2;
  Image1->Canvas->MoveTo(indent,Image1->Height-indent+(int)buf2[0]);
  for(int i=1;i<=(int)(T/dob);i++)
  {
  Image1->Canvas->LineTo(indent+i,Image1->Height-indent-(int)buf2[i*dob]);
  }
}
void GraficTA(int indent,TColor Col1, complex<float>** array, int numx,int  T,TImage* Image1)
{

  int  dob=(int)(T/(Image1->Height-2*indent)*2);
  dob++;
  float *buf=new float[T];
  for(int i=0; i<=T;i++)
  {
	  buf[i]=abs(array[numx][i]);
  }
  int max=maxEl1(buf,T+1);
  float MAX=buf[max];
  ClearImage(Image1);
  if(MAX<0)
  {
	  ShowMessage("MAX<0");
	  return;
  }
  GridYar(Image1,indent, T, MAX, 6)  ;
  ArrowGr(indent,Image1);
  //float maxo=(int)(max*1000);
  //Image1->Canvas->TextOutA(Image1->Width/2,0,maxo/1000);

	for(int i=0; i<=(int)(T/dob);i++)
  {
      if(MAX==0){MAX=1;}
	  buf[i*dob]=buf[i*dob]/MAX*(Image1->Height-2*indent);
  }

  Image1->Canvas->Pen->Color=Col1;
  Image1->Canvas->MoveTo(indent,Image1->Height-indent+(int)buf[0]);
  for(int i=1;i<=(int)(T/dob);i++)
  {
  Image1->Canvas->LineTo(indent+i,Image1->Height-indent-(int)buf[i*dob]);
  }
}

/*void GraficTA(int indent,TColor Col1, complex<float>* buf, int numx,int  T,TImage* Image1)
{

  int  dob=(int)(T/(Image1->Height-2*indent)*2);
  dob++;
  float *buf=new float[T];
  for(int i=0; i<=T;i++)
  {
	  buf[i]=abs(array[numx][i]);
  }
  int max=maxEl1(buf,T+1);
  float MAX=buf[max];
  ClearImage(Image1);
  GridYar(Image1,indent, T, MAX, 6)  ;
  ArrowGr(indent,Image1);
  //float maxo=(int)(max*1000);
  //Image1->Canvas->TextOutA(Image1->Width/2,0,maxo/1000);

	for(int i=0; i<=(int)(T/dob);i++)
  {
	  buf[i*dob]=buf[i*dob]/MAX*(Image1->Height-2*indent);
  }

  Image1->Canvas->Pen->Color=Col1;
  Image1->Canvas->MoveTo(indent,Image1->Height-indent+(int)buf[0]);
  for(int i=1;i<=(int)(T/dob);i++)
  {
  Image1->Canvas->LineTo(indent+i,Image1->Height-indent-(int)buf[i*dob]);
  }
}*/



int one1(int n)   //возведение -1 в степень
{
	if (n%2==0) { return 1;} else {return -1;}
}
void Arrow(TImage *Image, int indent)//стрелки графика
{

	Image->Canvas->Pen->Color=clBlack;
	Image->Canvas->MoveTo(indent,indent/2);
	Image->Canvas->LineTo(indent,Image->Height-indent);
	Image->Canvas->LineTo(Image->Width-indent/2,Image->Height-indent);
	Image->Canvas->MoveTo(indent-5,indent/2+15);
	Image->Canvas->LineTo(indent,indent/2);
	Image->Canvas->LineTo(indent+5,indent/2+15);
	Image->Canvas->MoveTo(Image->Width-indent/2-15,Image->Height-indent-5);
	Image->Canvas->LineTo(Image->Width-indent/2,Image->Height-indent);
	Image->Canvas->LineTo(Image->Width-indent/2-15,Image->Height-indent+5);
}
void Arrow1(TImage *Image, int indent)//стрелки графика
{
	Image->Canvas->Pen->Color=clBlack;
	Image->Canvas->MoveTo(indent,indent);
	Image->Canvas->LineTo(indent,Image->Height-indent);
	Image->Canvas->LineTo(Image->Width-indent,Image->Height-indent);
	Image->Canvas->MoveTo(indent-5,indent+15);
	Image->Canvas->LineTo(indent,indent);
	Image->Canvas->LineTo(indent+5,indent+15);
	Image->Canvas->MoveTo(Image->Width-indent-15,Image->Height-indent-5);
	Image->Canvas->LineTo(Image->Width-indent,Image->Height-indent);
	Image->Canvas->LineTo(Image->Width-indent-15,Image->Height-indent+5);
}
float perSent(complex<float>**array, TEdit *Edit1, TEdit *Edit2, int N, int numx)
{
	float *buf=new float[N];
	for(int i=0; i<=N;i++)
	{
	  buf[i]=abs(array[numx][i]);
	}
	double max1=buf[1], max2=buf[1], min=buf[1],tmp;
	int i1=0,i2=0,tmpi;
	for(int i=0;i<N;i++)
	{
		if(buf[i]>max2) 
		{
			max2=buf[i];
			i2=i;
			if(max1<max2)
			{
				tmp=max1;
				tmpi=i1;
				max1=max2;
				i1=i2;
				max2=tmp;
				i2=tmpi;
            }
		}
		min=buf[i1];
		if(i1<i2)
		for(int i=i1;i<=i2;i++)
		{
			if(min>buf[i])
			{
				min=buf[i];
			}
		}
		else
		for(int i=i1;i>=i2;i--)
		{
			if(min>buf[i])
			{
				min=buf[i];
			}
		}
		Edit1->Text=FloatToStr(100*(max1-min)/max1);
		Edit2->Text=FloatToStr(100*(max2-min)/max1);
	}
	return (100*(max2-min)/max1);
}

void graf(TImage*Image, float* array, int N, int indent,int delx,int dely, TColor Color)//Рисуем разрез
{
	float max=maxEl(array,N);
	Image->Canvas->Pen->Color=clWhite;
	Image->Canvas->Rectangle(0,0,Image->Width,Image->Height);

	int hx=(Image->Width-2*indent)/delx;
	int hy=(Image->Height-2*indent)/dely;

		Image->Canvas->Pen->Color=Color;
	for(int i=1;i<=dely;i++)
	{
		Image->Canvas->MoveTo(indent+i*hy,Image->Height-indent);
		Image->Canvas->LineTo(indent+i*hy,indent);
		Image->Canvas->TextOutA(indent+i*hy-5,Image->Height-indent+5,FloatToStr((255*i/dely-1)));
	}
	int max1=(max*1000000);
		for(int i=0;i<delx;i++)
	{
		Image->Canvas->MoveTo(indent,indent+i*hx);
		Image->Canvas->LineTo(Image->Width-indent,indent+i*hx);
		Image->Canvas->TextOutA(indent-25,indent+i*hx-5,FloatToStr((float)((max1-max1*i/delx))/1000));
	}
	Image->Canvas->Pen->Color=clBlack;
	Arrow(Image,indent);
	Image->Canvas->Pen->Color=clBlack;
	Image->Canvas->MoveTo(indent,Image->Height-indent) ;

	float kp;
	for (int i=0; i <= N; i++)
	{
		kp=(array[i]/max)*(Image->Height-2*indent);
		Image->Canvas->LineTo(indent+i,Image->Height-kp-indent);
	}

}
int factorial(int p)
{
	if (p==0) {  return 1;}
	else{
	int i, f=1;
	for (i = 1; i <= p; i++) {
	  f=f*i;
	}
	return f;
	}
}
double degree(double n, int m)//возведение в целую степень
{
	int i=0;
	double z=1;
	for (i = 0; i < m; i++) {
	   z=z*n;
	}
	return z;
}
double degreef(double ch, float stepen)//возведение в дробную степень
{
	if(ch<0.0000001&ch>-0.0000001)return 0;
	double z=ch;
	z=log(z);
	z=stepen*z;
	z=exp(z);
	return z;//exp(stepen*abs(log(abs(ch))));  //не работает, понять в чем ошибка
}

void paintComGraf(float *buf, int N, TImage *Image, int indent, float max, TColor Col, float start, float final)
{
	float x,y;
	int degr=5;
	Arrow1(Image,indent);

	if (max<0)
	{
		max=maxEl(buf, N);
	}
	float unityY=(Image->Height-2*indent)/max;
	float unityX=(Image->Width-2*indent)/N;
	x=indent;
	y=-buf[0]+Image->Height-indent;
	Image->Canvas->Pen->Color=clBlack;
	Image->Canvas->Brush->Color=Col;
	Image->Canvas->MoveTo(x,y);
	double test;
	for(int i=0;i<N;i++)
	{
	   x=i*unityX+indent;
	   y=-buf[i]*unityY+Image->Height-indent;
	   Image->Canvas->LineTo(x,y);
	   Image->Canvas->Ellipse(x-3,y-3,x+3,y+3);
	}

	for(int j=0;j<degr;j++)
	{
		Image->Canvas->MoveTo(indent,Image->Height-indent-((double)(j+1)/degr)*(Image->Height-2*indent));
		Image->Canvas->LineTo(Image->Width-indent,Image->Height-indent-((double)(j+1)/degr)*(Image->Height-2*indent));
		Image->Canvas->MoveTo(indent+((double)(j+1)/degr)*(Image->Width-2*indent),Image->Height-indent);
		Image->Canvas->LineTo(indent+((double)(j+1)/degr)*(Image->Width-2*indent),indent);
		Image->Canvas->TextOutA(indent+((double)(j+1)/degr)*(Image->Width-2*indent), Image->Height-indent/2, start+((double)(j+1)/degr*(final-start)));
		Image->Canvas->TextOutA(indent/2, Image->Height-indent-((double)(j+1)/degr)*(Image->Height-2*indent),(int)((max/(double)degr*((double)j+1)) ));
	}

}

void ReadMassiveInt2D(char* filename, char* errorMessage,int **array)
{
	AnsiString path = ExtractFilePath(Application->ExeName)+filename;
	ifstream fin(path.c_str());
	int x,y;

	if (!fin.is_open())
	{
		ShowMessage(errorMessage);
	}
	else
	{
		fin >> x>>y;
		array=new int*[x];
		for(int i=0;i<x;i++)
		{
			array[x]=new int[y];
        }
		for(int i=0;i<x;i++)
		{
			for(int j=0;j<y;j++)
			{
				fin>>array[i][j];
            }
        }
	}
}
