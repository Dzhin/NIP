//---------------------------------------------------------------------------

#ifndef LibralyH
#define LibralyH
//---------------------------------------------------------------------------
#endif

int one1(int n);
void Arrow(TImage *Image, int indent);
void graf(TImage*Image, float* array, int N, int indent,int delx,int dely);
int factorial(int p);
double degree(double n, int m);
double degreef(double ch, float stepen);//возведение в дробную степень
void ClearImage(TImage* Image1);
float perSent(complex<float>**array, TEdit *Edit1, TEdit *Edit2, int N, int numx);
void ArrowGr(int indent, TImage* Image1);
void GraficTA(int indent,TColor Col1,TColor Col2, complex<float>** array,complex<float>** array2, int numt,int  X,TImage* Image1);
void GraficTA(int indent,TColor Col1, complex<float>** array, int numx,int  T,TImage* Image1);
void paintComGraf(float *buf, int N, TImage *Image, int indent, float max, TColor Col,float start, float final);




