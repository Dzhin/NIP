//---------------------------------------------------------------------------
#ifndef FillH
#define FillH
//---------------------------------------------------------------------------

Syst(TImage *Image1);
float SystAuto(TImage *Image1);
Grafik(TImage *Image1,float *mas,float a,float b,int N,int nx,int ny);
Grafik1(TImage *Image1,float *mas,float a,float b,int N,int n,int nx,int ny);
void Dr_3Df (TImage *Image1,float **z, float rng, int Ni, int Nj, int X, int Y,
					     int p);
GrafikI(TImage *Image1,short *mas,float a,float b,int N,int nx,int ny);
Grafik_S(TImage *Image1,float *mas,float a,float b,int N,int nx,int ny,
         AnsiString sg,AnsiString sv);//������ � ���������
Grafik_S2(TImage *Image1,float *mas,float *mas1,float a,float b,int N,int nx,int ny,
		 AnsiString sg,AnsiString sv);//������� � ���������
float Gradient(float *mas,int N);//����������� �������� ��������� �� �������
#endif
