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
	  int NearestSize();//Вычисление ближайшего числа кратного степени двойки
	  int fft1d (complex<double> *arr,int Size,int c);//Одномерное преобразование Фурье

	  public:
	  float Energy();//Вычисляет среднее значение квадрата изображения
	  float Max();//Вычисляет максимальное значение модуля изображения
	  float *Section;//Сечение
	  int SizeSection;//Размер сечения
	  int SizeImageX;//Размер изображения по горизонтали
	  int SizeImageY;//Размер изображения по вертикали
	  //int SizeR;//Размер круга вписанного в изображение
	  int Zeros;//Дополнение нулями
	  float SKO;//Среднеквадратичное отклонение
	  float Aver;//Среднее значение интенсивности
	  unsigned char **Image;//Изображение
	  ReadFile(unsigned char *FileName);//Чтение изображения из файла в фазу
	  ReadFileA(unsigned char *FileName);//Чтение изображения из файла в амплитуду


	  //Доп код


	  ImageBase::OutputToFile(char*filename);
	  bool ImageBase::InputFromFile(char*filename);
	  bool ImageBase::InputFromFile(char*filename,complex<float>**array);  //Считать не в текущий массив, а в переданный по ссылке

	  ImageBase::InputWave(char*filename);//создаем волновой фронт от каждой из заданных точек
													//файлов создается по количеству точек, путем прибавления цифры к концу имени файла
	  ImageBase::InputWave(float alfa, float sig);
													//нельзя(

	  ImageBase::InputLightSourse(char *filename) ;

	  ImageBase::FourierTransform(char*filename);
	  ImageBase::FourierTransform1(char*filename);
	  ImageBase::Coherence(char *filename,float mu);


	  ImageBase::ApodizationA(char* filename,float deg); //r^g вроде
	  ImageBase::ApodizationF(char* filename,float deg, float koef);
	  ImageBase::ReadAbberations(char* filesCount,char *filename, float degAbber);
	  ImageBase::Coherence(float mu, ImageBase IB1);//когерентность
	  ImageBase::AddFilter(char*filename);//фильтр
	  ImageBase::SumPoint(char*filename, float mu);   //собираем все массивы в 1
	  ImageBase::SumPoint(char*filename);
	  ImageBase::PaintSumPoint(TImage *Image1, TImage *Image2);

	  int ImageBase::GetSizeImageX();    //не уверен что надо...
	  int ImageBase::GetSizeImageY();

	  //фильтры
	  ImageBase::CatCenter(char* filename, int r, int size);
	  ImageBase::CatEdge(char* filename, int r, int size);
		//




	  WriteFile(char *FileName,int q);//Запись изображения в файл
	  complex <float> **ImageComplex;//Комплексное изображение
	  ImageBase & operator = (ImageBase & c);//Оператор присваивания
	  ImageBase & operator + (ImageBase & c);//Оператор сложения
	  ImageBase & operator * (ImageBase & c);//Оператор умножения
	  ImageBase & operator - (ImageBase & c);//Оператор вычитания
	  ImageBase & operator / (ImageBase & c);//Оператор деления
	  ImageBase & operator | (ImageBase & c);//Оператор вычисления СКО
	  Value(complex<float> Val);//Присвоение всему комплексному массиву значения complex<float> Val
	  Norm();//Нормировка комплексного изображения на 1
	  Crushing(int q);//Дробление изображения в q раз
	  void fft(int c);//Двумерное преобразование Фурье
	  frt2Dz (float Rx,float Ry,float Z,float Kw,int q);//Преобразование Френеля
	  IKG(float Rx,float Ry,float Z,float Kw);//Интеграл Кирхгофа
	  IKG_(float Rx,float Ry,float Z,float Kw,int n);//Интеграл Кирхгофа составной
	  ViewImage(TImage *ImageT,float inc);//Вывод на форму изображения
	  ViewImage_(TImage *ImageT);//Вывод на форму изображения по размеру
	  ViewImageComplex(TImage *Image,int q,float inc,float F_dec);//Вывод на форму комплексного изображения
	  ViewImageComplex_(TImage *Image,int q,float inc,float F_dec);//Вывод на форму комплексного изображения по размеру
	  CenterCat(int R);//Вырезать центр изображения
	  FourFunction(float **FourC,int Size);//Заполнение изображения косинусным рядом с коэф. FourC,
												 // Size-размерность массива
	  int VortexAxicon(int m,int KL,int *mn,float *ang,float freq,float size);//Заполненияе элемента вихревым аксиконом
	  float MomImageComplex(int n);//Определение момента светового поля
	  float EMomImageComplex(int n);//Определение момента светового поля
	  int   SRing();//Поиск колец
	  float ERing(int R1,int R2);// Определение энергии внутри кольца
	  ImageBase(int SX,int SY);
	  ImageBase(char*filename);
	  ~ImageBase();
	 };
ReadBMPFile(unsigned char *FileName,int &X,int &Y);//Чтение заголовка BMP файла


