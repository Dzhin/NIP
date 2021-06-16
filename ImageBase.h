//---------------------------------------------------------------------------

#ifndef ImageBaseH
#define ImageBaseH
//---------------------------------------------------------------------------
#include "complex.h"
using namespace std;
#endif
class ImageBase
	 {
	  private:
	  int NearestSize();//���������� ���������� ����� �������� ������� ������
	  int fft1d (complex<double> *arr,int Size,int c);//���������� �������������� �����

	  public:
	  float Energy();//��������� ������� �������� �������� �����������
	  float Max();//��������� ������������ �������� ������ �����������
	  float *Section;//�������
	  int SizeSection;//������ �������
	  int SizeImageX;//������ ����������� �� �����������
	  int SizeImageY;//������ ����������� �� ���������
	  //int SizeR;//������ ����� ���������� � �����������
	  int Zeros;//���������� ������
	  float SKO;//������������������ ����������
	  float Aver;//������� �������� �������������
	  unsigned char **Image;//�����������
	  ReadFile(unsigned char *FileName);//������ ����������� �� ����� � ����
	  ReadFileA(unsigned char *FileName);//������ ����������� �� ����� � ���������


	  //��� ���


	  ImageBase::OutputToFile(char*filename);
	  bool ImageBase::InputFromFile(char*filename);
	  bool ImageBase::InputFromFile(char*filename,complex<float>**array);  //������� �� � ������� ������, � � ���������� �� ������

	  ImageBase::InputWave(char*filename);//������� �������� ����� �� ������ �� �������� �����
													//������ ��������� �� ���������� �����, ����� ����������� ����� � ����� ����� �����
	  ImageBase::InputWave(float alfa, float sig);
													//������(

	  ImageBase::InputLightSourse(char *filename) ;

	  ImageBase::FourierTransform(char*filename);
	  ImageBase::FourierTransform1(char*filename);
	  ImageBase::Coherence(char *filename,float mu);


	  ImageBase::ApodizationA(char* filename,float deg); //r^g �����
	  ImageBase::ApodizationF(char* filename,float deg, float koef);
	  ImageBase::ReadAbberations(char* filesCount,char *filename, float degAbber);
	  ImageBase::Coherence(float mu, ImageBase IB1);//�������������
	  ImageBase::AddFilter(char*filename);//������
	  ImageBase::SumPoint(char*filename, float mu);   //�������� ��� ������� � 1
	  ImageBase::SumPoint(char*filename);
	  ImageBase::PaintSumPoint(TImage *Image1, TImage *Image2);

	  int ImageBase::GetSizeImageX();    //�� ������ ��� ����...
	  int ImageBase::GetSizeImageY();

	  //�������
	  ImageBase::CatCenter(char* filename, int r, int size);
	  ImageBase::CatEdge(char* filename, int r, int size);
		//




	  WriteFile(char *FileName,int q);//������ ����������� � ����
	  complex <float> **ImageComplex;//����������� �����������
	  ImageBase & operator = (ImageBase & c);//�������� ������������
	  ImageBase & operator + (ImageBase & c);//�������� ��������
	  ImageBase & operator * (ImageBase & c);//�������� ���������
	  ImageBase & operator - (ImageBase & c);//�������� ���������
	  ImageBase & operator / (ImageBase & c);//�������� �������
	  ImageBase & operator | (ImageBase & c);//�������� ���������� ���
	  Value(complex<float> Val);//���������� ����� ������������ ������� �������� complex<float> Val
	  Norm();//���������� ������������ ����������� �� 1
	  Crushing(int q);//��������� ����������� � q ���
	  void fft(int c);//��������� �������������� �����
	  frt2Dz (float Rx,float Ry,float Z,float Kw,int q);//�������������� �������
	  IKG(float Rx,float Ry,float Z,float Kw);//�������� ��������
	  IKG_(float Rx,float Ry,float Z,float Kw,int n);//�������� �������� ���������
	  ViewImage(TImage *ImageT,float inc);//����� �� ����� �����������
	  ViewImage_(TImage *ImageT);//����� �� ����� ����������� �� �������
	  ViewImageComplex(TImage *Image,int q,float inc,float F_dec);//����� �� ����� ������������ �����������
	  ViewImageComplex_(TImage *Image,int q,float inc,float F_dec);//����� �� ����� ������������ ����������� �� �������
	  CenterCat(int R);//�������� ����� �����������
	  FourFunction(float **FourC,int Size);//���������� ����������� ���������� ����� � ����. FourC,
												 // Size-����������� �������
	  int VortexAxicon(int m,int KL,int *mn,float *ang,float freq,float size);//����������� �������� �������� ���������
	  float MomImageComplex(int n);//����������� ������� ��������� ����
	  float EMomImageComplex(int n);//����������� ������� ��������� ����
	  int   SRing();//����� �����
	  float ERing(int R1,int R2);// ����������� ������� ������ ������
	  ImageBase(int SX,int SY);
	  ImageBase(char*filename);
	  ~ImageBase();
	 };
ReadBMPFile(unsigned char *FileName,int &X,int &Y);//������ ��������� BMP �����


