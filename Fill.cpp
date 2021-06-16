//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Fill.h"
//#include "lens.h"

#include <math.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)


Grafik(TImage *Image1,float *mas,float a,float b,int N,int nx,int ny)
{
 int i;
 float max,ky,kx;
 float *xm,*tx,*ty;
 float distx,disty;
 int bord = 50;
 TRect NewRect = Rect(0, 0, Image1->Width,Image1->Height);
 Image1->Canvas->Brush->Color = clWhite;
 Image1->Canvas->FillRect(NewRect);
 xm = new float[N];
 tx = new float[nx];
 ty = new float[ny];
 distx = (Image1->Width)/nx;
 disty = (Image1->Height-bord)/ny;
 max = 0;
 for(i=0;i<N;i++)
    {
     if(mas[i]>max)
       max = mas[i];
     xm[i] = a+(b-a)/N*i;
    }

 ky = (Image1->Height-bord)/max;
 kx = Image1->Width/(b-a);
 Image1->Canvas->Pen->Color = clBlack;
 Image1->Canvas->Pen->Style  = psSolid;
 Image1->Canvas->MoveTo(0,Image1->Height);
 Image1->Canvas->LineTo(0,0);
 Image1->Canvas->MoveTo(0,Image1->Height-bord);
 Image1->Canvas->LineTo(Image1->Width,Image1->Height-bord);
 Image1->Canvas->Font->Color = clRed;
 Image1->Canvas->Pen->Color = clGreen;
 Image1->Canvas->Pen->Style  = psDot;
 for(i=0;i<nx;i++)
    {
     Image1->Canvas->MoveTo(i*distx,0);
//     Image1->Canvas->LineTo(i*distx,Image1->Height-bord);
     tx[i] = a+(b-a)/nx*i;
	 Image1->Canvas->TextOut(i*distx,Image1->Height-bord+2,
	 FloatToStrF((long double)tx[i],(TFloatFormat) 2,3,3));

    }
 Image1->Canvas->Font->Color = clRed;
 Image1->Canvas->Pen->Color = clGreen;
 Image1->Canvas->Pen->Style  = psDot;
 for(i=0;i<ny;i++)
    {
     Image1->Canvas->MoveTo(0,i*disty);
  //   Image1->Canvas->LineTo(Image1->Width,i*disty);
     ty[i] = (max-max/ny*i);
	 Image1->Canvas->TextOut(0,i*disty,FloatToStrF((long double)ty[i],(TFloatFormat)2,3,3));
    }
 Image1->Canvas->Pen->Color = clRed;
 Image1->Canvas->Pen->Style  = psSolid;
 for(i=0;i<N-1;i++)
    {
     Image1->Canvas->MoveTo((xm[i]-a)*kx,Image1->Height-bord-mas[i]*ky);
     Image1->Canvas->LineTo((xm[i+1]-a)*kx,Image1->Height-bord-mas[i+1]*ky);
    }

// Image1->Canvas->Rectangle(x-t/2, y-D/2, x+t/2, y+D/2);
delete[] xm;
delete[] tx;
delete[] ty;
}
Grafik1(TImage *Image1,float *mas,float a,float b,int N,int n,int nx,int ny)
{
 int i;
 float max,ky,kx;
 float *xm,*tx,*ty;
 float distx,disty;
 int bord = 20;
 TRect NewRect = Rect(0, 0, Image1->Width,Image1->Height);
 Image1->Canvas->Brush->Color = clWhite;
 Image1->Canvas->FillRect(NewRect);
 xm = new float[N];
 tx = new float[nx];
 ty = new float[ny];
 distx = (Image1->Width)/nx;
 disty = (Image1->Height-bord)/ny;
 max = 0;
 for(i=N/2-n/2;i<N/2+n/2;i++)
    {
     if(mas[i]>max)
       max = mas[i];
     xm[i] = a+(b-a)/n*i;
    }

 ky = (Image1->Height-bord)/max;
 kx = Image1->Width/(b-a);
 Image1->Canvas->MoveTo(0,Image1->Height);
 Image1->Canvas->LineTo(0,0);
 Image1->Canvas->MoveTo(0,Image1->Height-bord);
 Image1->Canvas->LineTo(Image1->Width,Image1->Height-bord);
 Image1->Canvas->Pen->Color = clGreen;
 Image1->Canvas->Pen->Style  = psDot;
 for(i=0;i<nx;i++)
    {
     Image1->Canvas->MoveTo(i*distx,0);
     Image1->Canvas->LineTo(i*distx,Image1->Height-bord);
     tx[i] = a+(b-a)/nx*i;
     Image1->Canvas->TextOut(i*distx,Image1->Height-bord+2,
	 FloatToStrF((long double)tx[i],(TFloatFormat)2,3,3));

    }
 Image1->Canvas->Pen->Color = clGreen;
 Image1->Canvas->Pen->Style  = psDot;
 for(i=0;i<ny;i++)
    {
     Image1->Canvas->MoveTo(0,i*disty);
     Image1->Canvas->LineTo(Image1->Width,i*disty);
     ty[i] = (max-max/ny*i);
     Image1->Canvas->TextOut(0,i*disty,FloatToStrF((long double)ty[i],(TFloatFormat)2,3,3));
    }
 Image1->Canvas->Pen->Color = clBlack;
 Image1->Canvas->Pen->Style  = psSolid;
 for(i=N/2-n/2;i<N/2+n/2;i++)
    {
     Image1->Canvas->MoveTo((xm[i]-a)*kx,Image1->Height-bord-mas[i]*ky);
     Image1->Canvas->LineTo((xm[i+1]-a)*kx,Image1->Height-bord-mas[i+1]*ky);
    }

// Image1->Canvas->Rectangle(x-t/2, y-D/2, x+t/2, y+D/2);
}
void Dr_3Df (TImage *Image1,float **z, float rng, int Ni, int Nj, int X, int Y,
						     int p)
{
  int  i, l, k, j, xl, hy, hx, yl, nn,ii;
  int  filcol, clr, Nvi, Nvj, N, Np=64, Nv,ti,tj;
  int  cel[8];
  float  dy, min, max, r;
  int xx[65][65], yy[65][65];
  dy = Image1->Height;
  r = 1.5*Np/dy;
  Nv = Y*r;
  if ( Nv > Np )   Nv = Np;

  if ( p==0 )   { filcol = 0;  clr = 100000000; }
  else   { filcol = 100000;  clr = 1000000000; }

  if ( Ni > Nv )   { Nvi = Nv;   ti = (float)Ni/Nv; }
  else  { Nvi = Ni;   ti = 1; }
  if ( Nj > Nv )   { Nvj = Nv;   tj = (float)Nj/Nv; }
  else  { Nvj = Nj;   tj = 1; }

  if ( Nvi != Nvj )
     { if ( Nvi > Nvj )   { N = Nvj;   ti *= (float)Ni/N; }
       else    { N = Nvi;   tj *= (float)Nj/N; }            }
  else   N = Nvi;

  min=max=z[0][0];
  for(i=0;i<N;i++)
      for(j=0;j<N;j++)
	  { r = z[i*ti][j*tj];
            if ( max < r )   max = r;
	    if ( min > r )   min = r; }


  hx = X/(2*N);
  hy = Y*hx/X;
  dy = rng*Y/(2*(max-min));
  yl = Y/2+N*hy;
  xl = X/2-N*hx;
  nn = 4;

  for(i=0;i<N;i++)
      for(j=0;j<N;j++)
	  { r = (z[i*ti][j*tj]-min)*dy;
            yy[i][j] = yl-r-(i+j)*hy*.86;
	    if (yy[i][j]<1)  yy[i][j]=1;
	    if (yy[i][j]>Y)  yy[i][j]=Y;
	    xx[i][j] = xl+(N+1-i+j)*hx;     }

  TRect NewRect = Rect(0, 0, Image1->Width,Image1->Height);
 Image1->Canvas->Brush->Color = clWhite;
 Image1->Canvas->FillRect(NewRect);

  for(i=N-1; i>=1; i--)
     { for(j=1;j<N-i;j++)
           { k = i;
             l = j;
             cel[0] = xx[N-l][k+l];
             cel[1] = yy[N-l][k+l];
             cel[2] = xx[N-1-l][k+l];
             cel[3] = yy[N-1-l][k+l];
             cel[4] = xx[N-1-l][k+l-1];
             cel[5] = yy[N-1-l][k+l-1];
             cel[6] = xx[N-l][k+l-1];
             cel[7] = yy[N-l][k+l-1];
 for(ii=0;ii<nn;ii=ii+2)
    {
     Image1->Canvas->MoveTo(cel[ii],cel[ii+1]);
     Image1->Canvas->LineTo(cel[ii+2],cel[ii+3]);
    }
    Image1->Canvas->Pen->Color = clGreen;
    Image1->Canvas->Pen->Style  = psDot;
//             setcolor(clr);
//	     setfillstyle(SOLID_FILL, filcol);
/*             fillpoly(nn,cel);*/                      }
			       			     }

  for(i=1;i<N;i++)
      { for(j=1;j<N-i+1;j++)
            { k = 1-i;
              l = j+i-1;
              cel[0] = xx[N-l][k+l];
              cel[1] = yy[N-l][k+l];
              cel[2] = xx[N-1-l][k+l];
              cel[3] = yy[N-1-l][k+l];
              cel[4] = xx[N-1-l][k+l-1];
              cel[5] = yy[N-1-l][k+l-1];
              cel[6] = xx[N-l][k+l-1];
              cel[7] = yy[N-l][k+l-1];
   for(ii=0;ii<nn;ii=ii+2)
    {
     Image1->Canvas->MoveTo(cel[ii],cel[ii+1]);
     Image1->Canvas->LineTo(cel[ii+2],cel[ii+3]);
    }
//              setcolor(clr);
//	      setfillstyle(SOLID_FILL, filcol);
/*              fillpoly(nn,cel);*/                       }
                                                       }

//  settextstyle(SMALL_FONT, HORIZ_DIR, 5);
//  setcolor(clr);
//  outtextxy(Gr, Y-Gr, str);

}
GrafikI(TImage *Image1,short *mas,float a,float b,int N,int nx,int ny)
{
 int i;
 float max,ky,kx;
 float *xm,*tx,*ty;
 float distx,disty;
 int bord = 60;
 TRect NewRect = Rect(0, 0, Image1->Width,Image1->Height);
 Image1->Canvas->Brush->Color = clWhite;
 Image1->Canvas->FillRect(NewRect);
 xm = new float[N];
 tx = new float[nx];
 ty = new float[ny];
 distx = (Image1->Width)/nx;
 disty = (Image1->Height-bord)/ny;
 max = 0;
 for(i=0;i<N;i++)
    {
     if(mas[i]>max)
       max = mas[i];
     xm[i] = a+(b-a)/N*i;
    }
 if(max!=0)
 ky = (Image1->Height-bord)/max;
 else
 ky = 1;
 kx = Image1->Width/(b-a);
  Image1->Canvas->Pen->Width = 1;
 Image1->Canvas->Pen->Color = clBlack;
 Image1->Canvas->Pen->Style  = psSolid;
 Image1->Canvas->MoveTo(0,Image1->Height);
 Image1->Canvas->LineTo(0,0);
 Image1->Canvas->MoveTo(0,Image1->Height-bord);
 Image1->Canvas->LineTo(Image1->Width,Image1->Height-bord);
 Image1->Canvas->Font->Color = clBlack;
 Image1->Canvas->Pen->Color = clGreen;
 Image1->Canvas->Pen->Style  = psDot;
 for(i=0;i<nx;i++)
    {
     Image1->Canvas->MoveTo(i*distx,0);
     Image1->Canvas->LineTo(i*distx,Image1->Height-bord);
     tx[i] = a+(b-a)/nx*i;
     Image1->Canvas->TextOut(i*distx,Image1->Height-bord+2,
	 FloatToStrF((long double)tx[i],(TFloatFormat)2,3,3));

    }
 Image1->Canvas->Font->Color = clBlack;
 Image1->Canvas->Pen->Color = clGreen;
 Image1->Canvas->Pen->Style  = psDot;
 for(i=0;i<ny;i++)
    {
     Image1->Canvas->MoveTo(0,i*disty);
     Image1->Canvas->LineTo(Image1->Width,i*disty);
     ty[i] = (max-max/ny*i);
	 Image1->Canvas->TextOut(0,i*disty,FloatToStrF((long double)ty[i],(TFloatFormat)2,3,3));
    }
 Image1->Canvas->Pen->Color = clBlue;
 Image1->Canvas->Pen->Style  = psSolid;
 Image1->Canvas->Pen->Width = 3;
 for(i=0;i<N-1;i++)
    {
     Image1->Canvas->MoveTo((xm[i]-a)*kx,Image1->Height-bord-mas[i]*ky);
     Image1->Canvas->LineTo((xm[i+1]-a)*kx,Image1->Height-bord-mas[i+1]*ky);
    }

// Image1->Canvas->Rectangle(x-t/2, y-D/2, x+t/2, y+D/2);
}
Grafik_S(TImage *Image1,float *mas,float a,float b,int N,int nx,int ny,
         AnsiString sg,AnsiString sv)//График с подписями
{
 int i;
 float max,ky,kx;
 float *xm,*tx,*ty;
 float distx,disty;
 int bord = 50;
 TRect NewRect = Rect(0, 0, Image1->Width,Image1->Height);
 Image1->Canvas->Brush->Color = clWhite;
 Image1->Canvas->FillRect(NewRect);
 xm = new float[N];
 tx = new float[nx];
 ty = new float[ny];
 distx = (Image1->Width)/nx;
 disty = (Image1->Height-bord)/ny;
 max = 0;
 for(i=0;i<N;i++)
    {
     if(mas[i]>max)
       max = mas[i];
     xm[i] = a+(b-a)/N*i;
    }

  for(i=0;i<N;i++)
    {
     if(max>0)
       mas[i] = mas[i]/max;
     else
       mas[i] = 0.0000001;
    }
 max = 1;
 ky = (Image1->Height-bord)/max;
 kx = Image1->Width/(b-a);
 Image1->Canvas->Pen->Color = clBlack;
 Image1->Canvas->Pen->Style  = psSolid;
 Image1->Canvas->MoveTo(0,Image1->Height);
 Image1->Canvas->LineTo(0,0);
 Image1->Canvas->MoveTo(0,Image1->Height-bord);
 Image1->Canvas->LineTo(Image1->Width,Image1->Height-bord);
 Image1->Canvas->Font->Color = clRed;
 Image1->Canvas->Pen->Color = clGreen;
 Image1->Canvas->Pen->Style  = psDot;
 Image1->Canvas->Font->Size = 16;

 for(i=0;i<nx;i++)
    {
     Image1->Canvas->MoveTo(i*distx,0);
     Image1->Canvas->LineTo(i*distx,Image1->Height-bord);
     tx[i] = a+(b-a)/nx*i;
     Image1->Canvas->TextOut(i*distx,Image1->Height-bord+2,
	 FloatToStrF((long double)tx[i],(TFloatFormat)2,2,2));

    }

 Image1->Canvas->TextOut(Image1->Width-30,Image1->Height-bord+2,sg);
 Image1->Canvas->TextOut(Image1->Width/2-30,bord+2,sv);

 Image1->Canvas->Font->Color = clRed;
 Image1->Canvas->Pen->Color = clGreen;
 Image1->Canvas->Pen->Style  = psDot;
 for(i=0;i<ny;i++)
    {
     Image1->Canvas->MoveTo(0,i*disty);
     Image1->Canvas->LineTo(Image1->Width,i*disty);
     ty[i] = (max-max/ny*i);
	 Image1->Canvas->TextOut(0,i*disty,FloatToStrF((long double)ty[i],(TFloatFormat)2,2,2));
    }
 Image1->Canvas->Pen->Color = clRed;
 Image1->Canvas->Pen->Style  = psSolid;
 for(i=0;i<N-1;i++)
    {
     Image1->Canvas->MoveTo((xm[i]-a)*kx,Image1->Height-bord-mas[i]*ky);
     Image1->Canvas->LineTo((xm[i+1]-a)*kx,Image1->Height-bord-mas[i+1]*ky);
    }

// Image1->Canvas->Rectangle(x-t/2, y-D/2, x+t/2, y+D/2);
delete[] xm;
delete[] tx;
delete[] ty;
}
Grafik_S2(TImage *Image1,float *mas,float *mas1,float a,float b,int N,int nx,int ny,
         AnsiString sg,AnsiString sv)//График с подписями
{
 int i;
 float max,ky,kx;
 float *xm,*tx,*ty;
 float distx,disty;
 int bord = 50;
 TRect NewRect = Rect(0, 0, Image1->Width,Image1->Height);
 Image1->Canvas->Brush->Color = clWhite;
 Image1->Canvas->FillRect(NewRect);
 xm = new float[N];
 tx = new float[nx];
 ty = new float[ny];
 distx = (Image1->Width)/nx;
 disty = (Image1->Height-bord)/ny;
 max = 0;
 for(i=0;i<N;i++)
	{
     if(mas[i]>max)
       max = mas[i];
     xm[i] = a+(b-a)/N*i;
    }

  for(i=0;i<N;i++)
    {
     if(max>0)
       mas[i] = mas[i]/max;
     else
       mas[i] = 0.0000001;
    }
 max = 1;
 ky = (Image1->Height-bord)/max;
 kx = Image1->Width/(b-a);
 Image1->Canvas->Pen->Color = clBlack;
 Image1->Canvas->Pen->Style  = psSolid;
 Image1->Canvas->MoveTo(0,Image1->Height);
 Image1->Canvas->LineTo(0,0);
 Image1->Canvas->MoveTo(0,Image1->Height-bord);
 Image1->Canvas->LineTo(Image1->Width,Image1->Height-bord);
 Image1->Canvas->Font->Color = clRed;
 Image1->Canvas->Pen->Color = clGreen;
 Image1->Canvas->Pen->Style  = psDot;
 Image1->Canvas->Font->Size = 16;

 for(i=0;i<nx;i++)
    {
     Image1->Canvas->MoveTo(i*distx,0);
     Image1->Canvas->LineTo(i*distx,Image1->Height-bord);
     tx[i] = a+(b-a)/nx*i;
     Image1->Canvas->TextOut(i*distx,Image1->Height-bord+2,
	 FloatToStrF((long double)tx[i],(TFloatFormat)2,2,2));

	}

 Image1->Canvas->TextOut(Image1->Width-30,Image1->Height-bord+2,sg);

 Image1->Canvas->Font->Color = clRed;
 Image1->Canvas->Pen->Color = clGreen;
 Image1->Canvas->Pen->Style  = psDot;
 for(i=0;i<ny;i++)
    {
     Image1->Canvas->MoveTo(0,i*disty);
     Image1->Canvas->LineTo(Image1->Width,i*disty);
     ty[i] = (max-max/ny*i);
     Image1->Canvas->TextOut(0,i*disty,FloatToStrF((long double)ty[i],(TFloatFormat)2,2,2));
    }
 Image1->Canvas->Pen->Color = clRed;
 Image1->Canvas->Pen->Style  = psSolid;
 for(i=0;i<N-1;i++)
    {
     Image1->Canvas->MoveTo((xm[i]-a)*kx,Image1->Height-bord-mas[i]*ky);
     Image1->Canvas->LineTo((xm[i+1]-a)*kx,Image1->Height-bord-mas[i+1]*ky);
    }

 Image1->Canvas->Pen->Color = clBlue;
 Image1->Canvas->Pen->Style  = psSolid;
 for(i=0;i<N-1;i++)
    {
     Image1->Canvas->MoveTo((xm[i]-a)*kx,Image1->Height-bord-mas1[i]*ky);
     Image1->Canvas->LineTo((xm[i+1]-a)*kx,Image1->Height-bord-mas1[i+1]*ky);
    }
// Image1->Canvas->Rectangle(x-t/2, y-D/2, x+t/2, y+D/2);
delete[] xm;
delete[] tx;
delete[] ty;
}
float Gradient(float *mas,int N)//Определение среднего градиента по сечению
{
 int i;
 float gr;
 gr = 0;
 for(i=1;i<N-1;i++)
	{
	 if(fabs(mas[i+1]-mas[i-1])<200)
		gr += fabs(mas[i+1]-mas[i-1]);

	}
 gr /= (float)(N-2);
 return(gr);
}


