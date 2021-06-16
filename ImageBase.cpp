//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ImageBase.h"
#include "Memory.h"
#include "anyfile.h"
#include "bmpfile.h"
#include <values.h>
#include "Libraly.h"
#include <fstream>
#include <complex.h>
#include "Forma.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
ImageBase & ImageBase::operator = (ImageBase & c)//Оператор присваивания
{
 int i,j;
 if((this->SizeImageY==c.SizeImageY)&&(this->SizeImageX==c.SizeImageX))
   {
    for(i=0;i<this->SizeImageY;i++)
        for(j=0;j<this->SizeImageX;j++)
           {
            this->Image[i][j] = c.Image[i][j];
            this->ImageComplex[i][j] = c.ImageComplex[i][j];
           }
   }
 else
   {
	DeleteArrayUC2(this->SizeImageY,Image);
    DeleteArrayComplex2(this->SizeImageY,ImageComplex);
    this->SizeImageX = c.SizeImageX;
    this->SizeImageY = c.SizeImageY;
    CreateArrayUC2(SizeImageY,SizeImageX,Image);
    CreateArrayComplex2(SizeImageY,SizeImageX,ImageComplex);
	for(i=0;i<this->SizeImageY;i++)
		for(j=0;j<this->SizeImageX;j++)
           {
            this->Image[i][j] = c.Image[i][j];
            this->ImageComplex[i][j] = c.ImageComplex[i][j];
           }
   }
 return(*this);
}
ImageBase & ImageBase::operator + (ImageBase & c)//Оператор сложения
{
 int i,j;
 int minY,minX;
 if(this->SizeImageY<c.SizeImageY)
   minY = this->SizeImageY;
 else
   minY = c.SizeImageY;
 if(this->SizeImageX<c.SizeImageX)
   minX = this->SizeImageX;
 else
   minX = c.SizeImageX;
 if((this->SizeImageY==c.SizeImageY)&&(this->SizeImageX==c.SizeImageX))
   {
    for(i=0;i<this->SizeImageY;i++)
        for(j=0;j<this->SizeImageX;j++)
           {
            this->Image[i][j] += c.Image[i][j];
			this->ImageComplex[i][j] += c.ImageComplex[i][j];
		   }
   }
 else
   {
    for(i=0;i<minY;i++)
        for(j=0;j<minX;j++)
           {
            this->Image[i][j] += c.Image[i][j];
			this->ImageComplex[i][j] += c.ImageComplex[i][j];
           }
   }
 return(*this);
}
ImageBase & ImageBase::operator * (ImageBase & c)//Оператор умножения
{
 int i,j;
 int minY,minX;
 if(this->SizeImageY<c.SizeImageY)
   minY = this->SizeImageY;
 else
   minY = c.SizeImageY;
 if(this->SizeImageX<c.SizeImageX)
   minX = this->SizeImageX;
 else
   minX = c.SizeImageX;
 if((this->SizeImageY==c.SizeImageY)&&(this->SizeImageX==c.SizeImageX))
   {
	for(i=0;i<this->SizeImageY;i++)
        for(j=0;j<this->SizeImageX;j++)
           {
            this->Image[i][j] *= c.Image[i][j];
            this->ImageComplex[i][j] *= c.ImageComplex[i][j];
           }
   }
 else
   {
	for(i=0;i<minY;i++)
		for(j=0;j<minX;j++)
		   {
			this->Image[i][j] *= c.Image[i][j];
			this->ImageComplex[i][j] *= c.ImageComplex[i][j];
		   }
   }
 return(*this);
}
ImageBase & ImageBase::operator - (ImageBase & c)//Оператор вычитания
{
 int i,j;
 int minY,minX;
 if(this->SizeImageY<c.SizeImageY)
   minY = this->SizeImageY;
 else
   minY = c.SizeImageY;
 if(this->SizeImageX<c.SizeImageX)
   minX = this->SizeImageX;
 else
   minX = c.SizeImageX;
 if((this->SizeImageY==c.SizeImageY)&&(this->SizeImageX==c.SizeImageX))
   {
	for(i=0;i<this->SizeImageY;i++)
		for(j=0;j<this->SizeImageX;j++)
		   {
			this->Image[i][j] -= c.Image[i][j];
			this->ImageComplex[i][j] -= c.ImageComplex[i][j];
		   }
   }
 else
   {
	for(i=0;i<minY;i++)
		for(j=0;j<minX;j++)
		   {
			this->Image[i][j] -= c.Image[i][j];
			this->ImageComplex[i][j] -= c.ImageComplex[i][j];
		   }
   }
 return(*this);
}

ImageBase & ImageBase::operator / (ImageBase & c)//Оператор деления
{
 int i,j;
 int minY,minX;
 if(this->SizeImageY<c.SizeImageY)
   minY = this->SizeImageY;
 else
   minY = c.SizeImageY;
 if(this->SizeImageX<c.SizeImageX)
   minX = this->SizeImageX;
 else
   minX = c.SizeImageX;
 if((this->SizeImageY==c.SizeImageY)&&(this->SizeImageX==c.SizeImageX))
   {
	for(i=0;i<this->SizeImageY;i++)
		for(j=0;j<this->SizeImageX;j++)
		   {
			if(c.Image[i][j]!=0)
			this->Image[i][j] /= c.Image[i][j];
			else
			this->Image[i][j] = 255;
			if(abs(c.ImageComplex[i][j])>1E-10)
			this->ImageComplex[i][j] /= c.ImageComplex[i][j];
			else
			this->ImageComplex[i][j] = 1E10;//MAXFLOAT/1000.;
		   }
   }
 else
   {
	for(i=0;i<minY;i++)
		for(j=0;j<minX;j++)
		   {
			if(c.Image[i][j]!=0)
			this->Image[i][j] /= c.Image[i][j];
			else
			this->Image[i][j] = 255;
			if(abs(c.ImageComplex[i][j])>1E-10)
			this->ImageComplex[i][j] /= c.ImageComplex[i][j];
			else
			this->ImageComplex[i][j] = 1E10;//MAXFLOAT/1000.;
		   }
   }
 return(*this);
 }
ImageBase & ImageBase::operator | (ImageBase & c)//Оператор вычисления СКО
{
 int i,j;
 int minY,minX;
 float max1,max2,k;
 if(this->SizeImageY<c.SizeImageY)
   minY = this->SizeImageY;
 else
   minY = c.SizeImageY;
 if(this->SizeImageX<c.SizeImageX)
   minX = this->SizeImageX;
 else
   minX = c.SizeImageX;
 max1 = 0;max2 = 0;
 if((this->SizeImageY==c.SizeImageY)&&(this->SizeImageX==c.SizeImageX))
   {
	for(i=0;i<this->SizeImageY;i++)
		for(j=0;j<this->SizeImageX;j++)
		   {
			if(norm(this->ImageComplex[i][j])>max1)
			max1 = norm(this->ImageComplex[i][j]);
			if(norm(c.ImageComplex[i][j])>max2)
			max2 = norm(this->ImageComplex[i][j]);
		   }
   }
 else
   {
	for(i=0;i<minY;i++)
		for(j=0;j<minX;j++)
		   {
			if(norm(this->ImageComplex[i][j])>max1)
			max1 = norm(this->ImageComplex[i][j]);
			if(norm(c.ImageComplex[i][j])>max2)
			max2 = norm(this->ImageComplex[i][j]);
		   }
   }
  SKO = 0;
  Aver = 0;
  k = max2/max1;
  if((this->SizeImageY==c.SizeImageY)&&(this->SizeImageX==c.SizeImageX))
   {
	for(i=0;i<this->SizeImageY;i++)
		for(j=0;j<this->SizeImageX;j++)
		   {
			SKO += (k*norm(this->ImageComplex[i][j])-norm(c.ImageComplex[i][j]))*
				   (k*norm(this->ImageComplex[i][j]-norm(c.ImageComplex[i][j])));
			Aver +=norm(c.ImageComplex[i][j]);
		   }
   }
 else
   {
	for(i=0;i<minY;i++)
		for(j=0;j<minX;j++)
		   {
			SKO += (k*norm(this->ImageComplex[i][j])-norm(c.ImageComplex[i][j]))*
				   (k*norm(this->ImageComplex[i][j])-norm(c.ImageComplex[i][j]));
			Aver +=norm(c.ImageComplex[i][j]);
		   }
  }
 if((this->SizeImageY==c.SizeImageY)&&(this->SizeImageX==c.SizeImageX))
   {
	Aver = Aver/SizeImageX/SizeImageY;
	SKO = sqrt(SKO/SizeImageX/SizeImageY)/Aver;
   }
 else
   {
	Aver = Aver/minX/minY;
	SKO = sqrt(SKO/minX/minY)/Aver;
   }
 return(*this);
}
ImageBase::Value(complex<float> Val)//Присвоение всему комплексному массиву значения complex<float> Val
{
 int i,j;
	for(i=0;i<SizeImageY;i++)
	   {
		for(j=0;j<SizeImageX;j++)
           {
            ImageComplex[i][j] = Val;
           }
       }
}
ImageBase::Norm()//Нормировка комплексного изображения на 1
{
 int i,j;
 float k;
 float max = 0;
 for(i=0;i<SizeImageY;i++)
    {
     for(j=0;j<SizeImageX;j++)
        {
         k = abs(ImageComplex[i][j]);
         if(k>max)
           {
            max = k;
           }
        }
    }
    for(i=0;i<SizeImageY;i++)//Чтение изображения из файла
       {
        for(j=0;j<SizeImageX;j++)
           {
            if(max>0)
			ImageComplex[i][j] = ImageComplex[i][j]/max;
           }
       }
}
int ImageBase::NearestSize()//Вычисление ближайшего числа кратного степени двойки
{
        int Size;
        int i;
        if(SizeImageX>SizeImageY)
		  {
		   Size = SizeImageX;
          }
        else
          {
           Size = SizeImageY;
          }
	for (i=0;(1 << i)<Size;i++);
	return 1 << i;

}
int ImageBase::fft1d (complex<double> *arr,int Size,int c)//Одномерное преобразование Фурье
{

	int i,k,m=0;
	for (i=1;i<Size;i<<=1,m++);
	if (i != Size)
		return -1;
	float q=1.;
	for (i=0;i<Size;i++,q=-q)
		arr[i]*=q;
	int n_2=Size/2,n_1=Size-1,j=0;
	for (i=0;i<n_1;i++)
	{
		if (i<j)
		{
			complex<double> t=arr[i];
			arr[i]=arr[j];
			arr[j]=t;
		}
		for (k=n_2;k<=j;j-=k,k>>=1);
		j+=k;
	}

        int le=1;
	float ed=1;
	float c_M_PI=c*M_PI;
	for (int l=0;l<m;l++)
	{
		int le1=le;
		le*=2;
		complex<double> u=1.;
		complex<double> w=polar(1.,(double)(-c_M_PI/le1));
		for (j=0;j<le1;j++,u*=w)
			for (i=j;i<Size;i+=le)
			{
				int ip=i+le1;
				complex<double> t=arr[ip]*u;
				arr[ip]=arr[i]-t;
				arr[i]+=t;
			}
	}
	for (i=0,q=1./(c==1 ? Size : 1);i<Size;i++,q=-q)
		arr[i]*=q;
	return(0);
}
float ImageBase::Energy()
{
int i,j;
float Aver=0;
for(i=0;i<SizeImageY;i++)
   {
	for(j=0;j<SizeImageX;j++)                         
	   {
		Aver+=norm(ImageComplex[i][j]);
	   }
   }
Aver = Aver/SizeImageY/SizeImageX;
return(Aver);
}
float ImageBase::Max()//Вычисляет максимальное значение модуля изображения
{
int i,j;
float mx=0;
for(i=0;i<SizeImageY;i++)
   {
	for(j=0;j<SizeImageX;j++)
	   {
		if(abs(ImageComplex[i][j])>mx)
		  mx = abs(ImageComplex[i][j]);
	   }
   }
return(mx);
}
ImageBase::ReadFile(unsigned char *FileName)//Чтение изображения из файла
{
 int i,j;
 unsigned char *buf=new unsigned char[SizeImageX];
 BmpFile BMP;
 fileReturnedCode rc=frcOk;
 if((rc=BMP.OpenFile((char *)FileName))==frcOk )
   {
	for (int i=0;i<SizeImageX;i++)//Инициация буфера
		 buf[i]=0;
	for(i=0;i<SizeImageY;i++)//Чтение изображения из файла
	   {
		BMP.ReadString(i,buf);
		for(j=0;j<SizeImageX;j++)
		   {
			Image[i][j] = buf[j];
			ImageComplex[i][j] = polar((float)1.,(float)(buf[j]/255.*2*M_PI));
		   }
	   }
	BMP.CloseFile();
   }
 delete buf;

}
ImageBase::ReadFileA(unsigned char *FileName)//Чтение изображения из файла
{
 int i,j;
 unsigned char *buf=new unsigned char[SizeImageX];
 BmpFile BMP;
 fileReturnedCode rc=frcOk;
 if((rc=BMP.OpenFile((char *)FileName))==frcOk )
   {
	for (int i=0;i<SizeImageX;i++)//Инициация буфера
		 buf[i]=0;
	for(i=0;i<SizeImageY;i++)//Чтение изображения из файла
	   {
		BMP.ReadString(i,buf);
		for(j=0;j<SizeImageX;j++)
		   {
			Image[i][j] = buf[j];
			ImageComplex[i][j] = polar((float)(buf[j]/255.),(float)(0));
		   }
	   }
	BMP.CloseFile();
   }
 delete buf;
}
ImageBase::WriteFile(char *FileName,int q)//Запись изображения в файл
{
 int i,j;
 float max,k;
 switch(q)
	   {
		case 0:
			   {
				max = 0;
				for(i=0;i<SizeImageY;i++)
				   {
                    for(j=0;j<SizeImageX;j++)
                       {
                        k = norm(ImageComplex[i][j]);
                        if(k>max)
                          {
                           max = k;
                          }
                       }
				   }
				break;
               }
		case 1:
			   {
                max = 0;
                for(i=0;i<SizeImageY;i++)
                   {
                    for(j=0;j<SizeImageX;j++)
                       {
						k = abs(ImageComplex[i][j]);
                        if(k>max)
                          {
						   max = k;
                          }
					   }
                   }
                break;
               }
	   }
 unsigned char *buf=new unsigned char[SizeImageX];
 BmpFile BMP;
 BMP.OpenFile(FileName,SizeImageY,SizeImageX,8);
 for (int i=0;i<SizeImageX;i++)//Инициация буфера
     buf[i]=0;
    for(i=0;i<SizeImageY;i++)//Запись изображения в файл
	   {
        BMP.ReadString(i,buf);
        for(j=0;j<SizeImageX;j++)
		   {
            switch(q)
                  {
                   case 0:
                          buf[j] = norm(ImageComplex[i][j])/max*255;
                          break;
                   case 1:
						  buf[j] =  abs(ImageComplex[i][j])/max*255;
                          break;
                   case 2:
                          buf[j] = arg(ImageComplex[i][j])/2./M_PI*255.;
						  break;
				  }
		   }
		BMP.WriteString(i,buf);
	   }
	BMP.CloseFile();

 delete buf;
}
//Мой код
   //Не буду)
ImageBase::OutputToFile(char*filename)
{
	ofstream fout;
	AnsiString path = ExtractFilePath(Application->ExeName)+filename;
	//ShowMessage(path);
	fout.open(path.c_str());
	fout << SizeImageX<<" "<<SizeImageY<<endl;

	for (int i = 0; i < SizeImageX ; i++) {
		fout << "\n";
		for (int j = 0; j < SizeImageY; j++) {
			fout <<  ImageComplex[i][j] << " ";
		}
	}
	fout.close();
}

bool ImageBase::InputFromFile(char*filename)
{
	ifstream fin;
	AnsiString path = ExtractFilePath(Application->ExeName)+filename;
	//ShowMessage(path);
	fin.open(path.c_str());
	if (!fin.is_open())
	{
		return false;
		//ShowMessage("Не открывается файл коэффициентов");
	}
	fin >> SizeImageX>>SizeImageY;

	for (int i = 0; i < SizeImageX ; i++) {
		for (int j = 0; j < SizeImageY; j++) {
			fin >>  ImageComplex[i][j];
		}
	}
	fin.close();
	return true;
}
bool ImageBase::InputFromFile(char*filename,complex<float>**array)  //Считать не в текущий массив, а в переданный по ссылке
{
	int SizeX,SizeY;
	ifstream fin;
	AnsiString path = ExtractFilePath(Application->ExeName)+filename;
	//ShowMessage(path);
	fin.open(path.c_str());
	if (!fin.is_open())
	{
		return false;
		//ShowMessage("Не открывается файл коэффициентов");
	}
	fin >> SizeX>>SizeY;

	for (int i = 0; i < SizeX ; i++) {
		for (int j = 0; j < SizeY; j++) {
			fin >>  array[i][j];
		}
	}
	fin.close();
	return true;
}

ImageBase::InputWave(char*filename)
{
	Form1->Memo1->Lines->Add("Задаем источники света") ;
	int sizeInputArray;
	float alfa,betta, c, sig;
	float r0,r;
	float temp;
	float fi;//угол в полярных координатах
	complex<float>tmp(0.,0.);
	int countCol;
	int i,j;   //читаем количество источников и их параметры
	//ofstream fout;
	//AnsiString pathOut = ExtractFilePath(Application->ExeName)+"InputWave";
	ifstream fin;
	AnsiString pathIn = ExtractFilePath(Application->ExeName)+"ParameterPoint.txt";
	fin.open(pathIn.c_str());
	fin >> sizeInputArray >> countCol;


	for (j = 0; j < sizeInputArray; j++) {
		fin >> alfa >> betta >> c >> sig >> fi;
		if (SizeImageX<SizeImageY)
		{
			r0=SizeImageY/2;
		}
		else
		{
			r0=SizeImageX/2;
		}
		int X,Y;
		for(int y=0;y<SizeImageY;y++)
		{
			Y=y-SizeImageY/2;
			for(int x=0;x<SizeImageX;x++)
			{
				X=x-SizeImageX/2;
				r=sqrt((float)(X*X+Y*Y));
				if (r/r0<=1)
				{
					ImageComplex[x][y]=polar(c*(float)exp(-r*r/2/sig/sig),(float)(alfa*X+betta*Y+fi));
					//tmp=polar((float)exp(-r*r/2/sig/sig),(float)(alfa*y+betta*x));
					//ImageComplex[x][y]=ImageComplex[x][y]+tmp;
				}
				else
				{
					ImageComplex[x][y]=polar((float)0.,(float)0.);
				}
			}
		}
		AnsiString zv=filename+IntToStr(j);
		ImageBase::OutputToFile(zv.c_str());
	}
	fin.close();
}

ImageBase::InputWave(float alfa, float sig)
{
	Form1->Memo1->Lines->Add("Задаем источники света") ;

	float r0,r;
	float temp;
	complex<float>tmp(0.,0.);
	if (SizeImageX<SizeImageY)
	{
		r0=SizeImageY/2;
	}
	else
	{
		r0=SizeImageX/2;
	}

	for(int x=0;x<SizeImageX;x++)
	{
		for(int y=0;y<SizeImageY;y++)
		{
			r=sqrt((float)((x-SizeImageX/2)*(x-SizeImageX/2)+(y-SizeImageY/2)*(y-SizeImageY/2)));
			if (r/r0<=1)
			{
//				ImageComplex[x][y]=polar((float)exp(-r*r/2/sig/sig),(float)(-alfa*y+M_PI));
//				tmp=polar((float)exp(-r*r/2/sig/sig),(float)(alfa*(y)));
//				temp=sqrt(abs(ImageComplex[x][y])*abs(tmp))*cos(abs(arg(ImageComplex[x][y])-arg(tmp)));
//				ImageComplex[x][y]=ImageComplex[x][y]+tmp;
//				ImageComplex[x][y]=polar(abs(ImageComplex[x][y])+2*mu*temp,arg(ImageComplex[x][y]));
				ImageComplex[x][y]=polar((float)exp(-r*r/2/sig/sig),(float)(-alfa*y+M_PI*2/3));
				tmp=polar((float)exp(-r*r/2/sig/sig),(float)(alfa*y));
				//temp=(abs(ImageComplex[x][y])*abs(tmp))*cos(abs(arg(ImageComplex[x][y])-arg(tmp)));
				ImageComplex[x][y]=ImageComplex[x][y]+tmp;
				//ImageComplex[x][y]=polar(sqrt(abs(ImageComplex[x][y])-2*mu*temp),arg(ImageComplex[x][y]));
				//tmp=polar((float)exp(-r*r/2/sig/sig),(float)(-5/2*alfa*(y)+M_PI));
				//ImageComplex[x][y]=ImageComplex[x][y]+tmp;
			}
			else
			{
				ImageComplex[x][y]=polar((float)0.,(float)0.);
			}
		}
	}
}

ImageBase::InputLightSourse(char *filename)
{
	Form1->Memo1->Lines->Add("Задаем источники света") ;
	int sizeInputArray;
	float cx,cy, c, sig;
	float r;
	float temp;
	float fi;//угол в полярных координатах
	complex<float>tmp(0.,0.);
	int countCol;
	int i,j;   //читаем количество источников и их параметры
	//ofstream fout;
	//AnsiString pathOut = ExtractFilePath(Application->ExeName)+"InputWave";
	ifstream fin;
	AnsiString pathIn = ExtractFilePath(Application->ExeName)+"ParameterPoint.txt";
	fin.open(pathIn.c_str());
	fin >> sizeInputArray >> countCol;


	for (j = 0; j < sizeInputArray; j++) {
		fin >> cx >> cy >> r >> c >> sig >> fi;

		int X,Y;
		for(int y=0;y<SizeImageY;y++)
		{
			Y=y-SizeImageY/2;
			for(int x=0;x<SizeImageX;x++)
			{
				X=x-SizeImageX/2;
				//r=sqrt((float)(X*X+Y*Y));
				if ((cx-X)*(cx-X)+(cy-Y)*(cy-Y)<r*r)
				{
					ImageComplex[x][y]=polar(c*(float)exp(-((cx-X)*(cx-X)+(cy-Y)*(cy-Y))/sig/sig),fi);
					//tmp=polar((float)exp(-r*r/2/sig/sig),(float)(alfa*y+betta*x));
					//ImageComplex[x][y]=ImageComplex[x][y]+tmp;
				}
				else
				{
                    ImageComplex[x][y]=polar(0.,0.);
                }
			}
		}
		AnsiString zv=filename+IntToStr(j);
		ImageBase::OutputToFile(zv.c_str());
	}
	fin.close();

}

ImageBase::Coherence(char *filename,float mu)    //сырой код проверить, дописать
{
	AnsiString path =filename;
	int j=0;
	complex<float>**tmp;
	complex<float> temp(0.,0.);
	CreateArrayComplex2(SizeImageX,SizeImageY,tmp);
	for(int x=0;x<SizeImageX;x++)
		{
			for(int y=0;y<SizeImageY;y++)
				tmp[x][y]=temp;
		}
	while(InputFromFile((path+IntToStr(j)).c_str()))
	{
		for(int x=0;x<SizeImageX;x++)
		{
			for(int y=0;y<SizeImageY;y++)
				tmp[x][y]=tmp[x][y]+ImageComplex[x][y];
		}
		j++;
	}
	for(int x=0;x<SizeImageX;x++)
	{
		for(int y=0;y<SizeImageY;y++)
			ImageComplex[x][y]=tmp[x][y];
	}
	DeleteArrayComplex2(SizeImageX,tmp);
	for(int x=0;x<SizeImageX;x++)
	{
		for(int y=0;y<SizeImageY;y++)
		{
			//ImageComplex[x][y]=polar((float)sqrt(degree(abs(ImageComplex[x][y]),2)),arg(ImageComplex[x][y]));   //учитываем когерентность
		}
	}
}
ImageBase::SumPoint(char*filename, float mu)   //собираем все массивы в 1
{
	Form1->Memo1->Lines->Add("Суммируем волновой фронт") ;
	AnsiString path =filename;
	int j=0;
	complex<float>**tmp,**array2;
	complex<float> temp(0.,0.);
	CreateArrayComplex2(SizeImageX,SizeImageY,tmp);
	CreateArrayComplex2(SizeImageX,SizeImageY,array2);
	for(int x=0;x<SizeImageX;x++)
		{
			for(int y=0;y<SizeImageY;y++)
				ImageComplex[x][y]=temp;
		}
	while(InputFromFile((path+IntToStr(j)).c_str(),tmp))
	{
		//Form1->Memo1->Lines->Add(IntToStr(j));
		for(int x=0;x<SizeImageX;x++)
		{
			for(int y=0;y<SizeImageY;y++)
				ImageComplex[x][y]=ImageComplex[x][y]+polar(abs(tmp[x][y])*abs(tmp[x][y]),arg(tmp[x][y]));
		}
		j++;
	}
	Form1->Memo1->Lines->Add("Учитываем когерентность") ;
	if((mu>0)&&(mu<=1))      //когерентность
	{
	int e=0,f=1;
		while(InputFromFile((path+IntToStr(e)).c_str(),tmp))
		{
			f=e+1;
			Form1->Memo1->Lines->Add("Открываю файл"+(path+IntToStr(e))) ;
			while(InputFromFile((path+IntToStr(f)).c_str(),array2))
			{
				if(e!=f)
				{
					for(int x=0;x<SizeImageX;x++)
					{
						for(int y=0;y<SizeImageY;y++)
							ImageComplex[x][y]=ImageComplex[x][y]+polar(2*mu*(abs(tmp[x][y])*abs(array2[x][y]))*cos(arg(tmp[x][y])-arg(array2[x][y])),(float)0.);
					}
				}
				++f;
			}
			++e;
		}
	}
	for(int x=0;x<SizeImageX;x++)
	{
		for(int y=0;y<SizeImageY;y++)
			ImageComplex[x][y]=polar(sqrt(abs(ImageComplex[x][y])),arg(ImageComplex[x][y]));
	}
	DeleteArrayComplex2(SizeImageX,tmp);
	DeleteArrayComplex2(SizeImageX,array2);
}
ImageBase::AddFilter(char*filename)
{
	Form1->Memo1->Lines->Add("Добавляем фильтр") ;
	AnsiString path =filename;
	int j=0;
	float f;
	while(InputFromFile((path+IntToStr(j)).c_str()))
	{
		//Form1->Memo1->Lines->Add(IntToStr(j));
		for(int x=0;x<SizeImageX;x++)
		{
			for(int y=0;y<SizeImageY;y++)
			{
				if(atan2(y-SizeImageY/2,x-SizeImageX/2+0.0000001)>0)
				{
					f=atan2(y-SizeImageY/2,x-SizeImageX/2+0.0000001);
				}
				else
				{
					f=atan2(y-SizeImageY/2,x-SizeImageX/2+0.0000001)+2*M_PI;
				}
				ImageComplex[x][y]=polar(abs(ImageComplex[x][y]), arg(ImageComplex[x][y])+f);
			}
		}
		OutputToFile((path+IntToStr(j)).c_str());
		j++;
	}
}
ImageBase::SumPoint(char*filename)   //собираем все массивы в 1
{
	Form1->Memo1->Lines->Add("Суммируем волновой фронт") ;
	AnsiString path =filename;
	int j=0;
	complex<float>**tmp,array2;
	complex<float> temp(0.,0.);
	CreateArrayComplex2(SizeImageX,SizeImageY,tmp);
	for(int x=0;x<SizeImageX;x++)
		{
			for(int y=0;y<SizeImageY;y++)
				tmp[x][y]=temp;
		}
	while(InputFromFile((path+IntToStr(j)).c_str()))
	{
		//Form1->Memo1->Lines->Add(IntToStr(j));
		for(int x=0;x<SizeImageX;x++)
		{
			for(int y=0;y<SizeImageY;y++)
				tmp[x][y]=tmp[x][y]+ImageComplex[x][y];
		}
		j++;
	}
	for(int x=0;x<SizeImageX;x++)
	{
		for(int y=0;y<SizeImageY;y++)
			ImageComplex[x][y]=tmp[x][y];
	}
	DeleteArrayComplex2(SizeImageX,tmp);
}


ImageBase::PaintSumPoint(TImage *Image1, TImage *Image2)
{

}
ImageBase::CatCenter(char* filename, int r, int size)
{
	int X,Y;
	AnsiString path =filename;
	int j=0;
	complex<float> tmp;
	while(InputFromFile((path+IntToStr(j)).c_str()))
	{
		//Form1->Memo1->Lines->Add(IntToStr(j));
		for(int x=0;x<SizeImageX;x++)
		{
			X=x-SizeImageX/2;
			for(int y=0;y<SizeImageY;y++)
			{
				Y=y-SizeImageY/2;
				if(X*X+Y*Y<r*r/size/size)
				{
					//ImageComplex[x][y]=polar(abs(ImageComplex[x][y]),(float)0.0001);
					ImageComplex[x][y]=polar((float)0.00000001,arg(ImageComplex[x][y]));
				}
					//abs(ImageComplex[x][y])    ImageComplex[y][x]=polar(abs(ImageComplex[y][x])*apodization,arg(ImageComplex[y][x]));
			}

		}
		OutputToFile((path+IntToStr(j)).c_str());
		j++;
	}
}
ImageBase::CatEdge(char* filename, int r, int size)
{
	int X,Y;
	AnsiString path =filename;
	int j=0;
	while(InputFromFile((path+IntToStr(j)).c_str()))
	{
		//Form1->Memo1->Lines->Add(IntToStr(j));
		for(int x=0;x<SizeImageX;x++)
		{
			X=x-SizeImageX/2;
			for(int y=0;y<SizeImageY;y++)
			{
				Y=y-SizeImageY/2;
				if(X*X+Y*Y>r*r/size/size)
					ImageComplex[x][y]=polar((float)0.000001,arg(ImageComplex[x][y]));
					//ImageComplex[x][y]=polar(abs(ImageComplex[x][y]),(float)0.0000001);
			}

		}
		OutputToFile((path+IntToStr(j)).c_str());
		j++;
	}
}

ImageBase::ApodizationA(char* filename,float deg)   //радиусная аподизация  1-амплитудная, 2-фазовая
{
	float r0,r;

	if (SizeImageX<SizeImageY)
	{
		r0=SizeImageY/2;
	}
	else
	{
		r0=SizeImageX/2;
	}
	int X,Y;
	float apodization;
	AnsiString path=filename;
	int j=0;
	Form1->Memo1->Lines->Add("Добавляем амплитудную аподизацию") ;
	while(InputFromFile((path+IntToStr(j)).c_str()))
	{
		//Form1->Memo1->Lines->Add(IntToStr(j));
		for(int x=0;x<SizeImageX;x++)
		{
			X=x-SizeImageX/2;
			for(int y=0;y<SizeImageY;y++)
			{
				Y=y-SizeImageY/2;
				r=sqrt((float)((X)*(X)+(Y)*(Y)));
				if (r/r0<=1)
				{
					apodization=degreef(r/r0,deg);
					ImageComplex[y][x]=polar(abs(ImageComplex[y][x])*apodization,arg(ImageComplex[y][x]));
				}
				else
				{
					ImageComplex[y][x]=polar((float)0.,(float)0.);
				}
			}
		}
		OutputToFile((path+IntToStr(j)).c_str());
		j++;
	}
}

ImageBase::ApodizationF(char* filename,float deg, float koef)   //радиусная аподизация
{
	float r0,r;

	if (SizeImageX<SizeImageY)
	{
		r0=SizeImageY/2;
	}
	else
	{
		r0=SizeImageX/2;
	}
	int X,Y;
	float apodization;
	AnsiString path=filename;
	int j=0;
	Form1->Memo1->Lines->Add("Добавляем фазовую аподизацию") ;
	while(InputFromFile((path+IntToStr(j)).c_str()))
	{
		//Form1->Memo1->Lines->Add(IntToStr(j));
		for(int x=0;x<SizeImageX;x++)
		{
			X=x-SizeImageX/2;
			for(int y=0;y<SizeImageY;y++)
			{
				Y=y-SizeImageY/2;
				r=sqrt((float)((X)*(X)+(Y)*(Y)));
				if (r/r0<=1)
				{
					apodization=koef*degreef(r/r0,deg);
					ImageComplex[y][x]=polar(abs(ImageComplex[y][x]),arg(ImageComplex[y][x])+apodization);
				}
				else
				{
					ImageComplex[y][x]=polar((float)0.,(float)0.);
				}
			}
		}

		OutputToFile((path+IntToStr(j)).c_str());
		j++;
	}
}

ImageBase::ReadAbberations(char* filesCount,char *filename, float degAbber)
{
	float r0,r;
	if (SizeImageX<SizeImageY)
	{
		r0=SizeImageY/2;
	}
	else
	{
		r0=SizeImageX/2;
	}
	//--------------------------Считываем коэффиценты полином из файла----------
	AnsiString path = ExtractFilePath(Application->ExeName)+filename;
	ifstream fin(path.c_str());
	int count;
	if (!fin.is_open())
	{
		ShowMessage("Не открывается файл коэффициентов");
	}
	else
	{
		fin >> count;
		double **cellsarray = new double* [count];
		for (int i = 0; i < (int)count; i++)
			cellsarray[i] = new double [3];
		for (int i = 0; i < (int)count; i++)
		{
		  for (int j = 0; j < 3; j++)
		  {
			  fin >> cellsarray [i][j];
		  }
		}
		fin.close();
//--------------------------Нормируем коэффиценты----------------------------
		double norma=0;
		for (int i = 0; i < (int)count; i++)
		{
			norma=norma+cellsarray[i][0]*cellsarray[i][0];
		}
		if (norma==0)
		{
		}
		else
		{
			for (int i = 0; i < (int)count; i++)
			{
				cellsarray[i][0]=cellsarray[i][0]/sqrt(norma);
			}
		}
//--------------------------Считаем полиномы---------------------------------
		complex<float>FI=polar((float)0.,(float)0.),FI1=polar((float)0.,(float)0.);
		float R,R1,R2,R3,Anm,FI2,f,k;
		int a,n,m;
		AnsiString path=filesCount;
		int j=0;
		while(InputFromFile((path+IntToStr(j)).c_str()))
		{
			Form1->Memo1->Lines->Add(IntToStr(j));
			for (int x = 0; x < SizeImageX; x++)
			{
				for (int y = 0; y < SizeImageY; y++)
				{
					r=sqrt((float)((x-SizeImageX/2)*(x-SizeImageX/2)+(y-SizeImageY/2)*(y-SizeImageY/2)));
					if (r/r0<=1)
					{
						FI=polar((float)0.,(float)0.);
						FI2=0;
						FI1=polar((float)0.,(float)0.);
						for (int i=0; i < (int)count; i++)
						{
							a=(int)cellsarray[i][0];
							n=(int)cellsarray[i][1];
							m=(int)cellsarray[i][2];
							if(atan2(y-SizeImageY/2,x-SizeImageX/2+0.0000001)>0)
							{
								f=atan2(y-SizeImageY/2,x-SizeImageX/2+0.0000001);
							}
							else
							{
								f=atan2(y-SizeImageY/2,x-SizeImageX/2+0.0000001)+2*M_PI;
							}
							Anm=sqrt((n-1)/M_PI/r0/r0);
							for (int p = 0; p <= (n-abs(m))/2; p++)
							{
								R=0;
								R1=one1(p)*factorial(n-p);
								R2=factorial(p)*factorial((n+m)/2-p)*factorial((n-m)/2-p);
								R3=degree(r/r0,n-2*p);
								R=R+R3/R2*R1;
								if (m>0)
								{
									if (cos(m*f)>0)
									{
										k=0;
									}
									else
									{
										k=M_PI;
									}
									FI2=FI2+a*R*cos(m*f);
								}
								else
								{
									if (sin(m*f)>0)
									{
										k=0;
									}
									else
									{
										k=M_PI;
									}
									FI2=FI2+a*R*sin(m*f);
								}
							}
							FI1=FI1+polar((float)1.,(float)(degAbber*FI2));
						}
						ImageComplex[x][y]=polar(abs(FI1)*abs(ImageComplex[x][y]),arg(FI1)+arg(ImageComplex[x][y]));
					}
					else
					{
						ImageComplex[x][y]=polar((float)0.,(float)0.);
					}
				}

			}
			OutputToFile((path+IntToStr(j)).c_str());
			j++;
		}
	}
}

ImageBase::FourierTransform(char*filename)
{
	int j=0;
	AnsiString path = filename;
	Form1->Memo1->Lines->Add("Делаем Фурье преобразование") ;
	while(InputFromFile((path+IntToStr(j)).c_str()))
	{
		//Form1->Memo1->Lines->Add(IntToStr(j)) ;
		fft(1);
		OutputToFile((path+IntToStr(j)).c_str());
		j++;
	}
}
ImageBase::FourierTransform1(char*filename)
{
	AnsiString path = filename;
	Form1->Memo1->Lines->Add("Делаем Фурье преобразование") ;
	InputFromFile((path).c_str());
	//Form1->Memo1->Lines->Add(IntToStr(j)) ;
	fft(1);
	OutputToFile((path).c_str());
}




int ImageBase::GetSizeImageX()
{
	return SizeImageX;
}
int ImageBase::GetSizeImageY()
{
	return SizeImageY;
}


			//немой

ImageBase::Crushing(int q)//Дробление изображения в q раз
{
 int i,j;
 unsigned char **ImageTemp;
 complex<float> **ImageComplexTemp;
 CreateArrayUC2(SizeImageY,SizeImageX,ImageTemp);
 CreateArrayComplex2(SizeImageY,SizeImageX,ImageComplexTemp);
 for(i=0;i<SizeImageY;i++)
	   {
		for(j=0;j<SizeImageX;j++)
		   {
			ImageTemp[i][j] = Image[i][j];
			ImageComplexTemp[i][j] = ImageComplex[i][j];
		   }
	   }
 DeleteArrayUC2(SizeImageY,Image);
 DeleteArrayComplex2(SizeImageY,ImageComplex);
 SizeImageX = q*SizeImageX;
 SizeImageY = q*SizeImageY;
 CreateArrayUC2(SizeImageY,SizeImageX,Image);
 CreateArrayComplex2(SizeImageY,SizeImageX,ImageComplex);
 for(i=0;i<SizeImageY;i++)
	   {
		for(j=0;j<SizeImageX;j++)
		   {
			Image[i][j] = ImageTemp[i/q][j/q];
			ImageComplex[i][j] = ImageComplexTemp[i/q][j/q];
		   }
	   }
 DeleteArrayUC2(SizeImageY/q,ImageTemp);
 DeleteArrayComplex2(SizeImageY/q,ImageComplexTemp);
}

void ImageBase::fft(int c)//Двумерное преобразование Фурье
{

//        float e1 = Energy();
        int i,j;
	int LineSize = NearestSize()*Zeros;
	int St=(LineSize-SizeImageX)/2;
	int End=St+SizeImageX;
	complex<double> *line = new complex<double>[LineSize];

	for(i=0;i<SizeImageY;i++)
	   {
	    for (j=0;j<LineSize;j++)
		{
	         if((j>=St) && (j<End))
		   line[j]=ImageComplex[i][j-St];
		 else line[j]=0.;
		}
	    fft1d(line,LineSize,c);
	    for (j=0;j<SizeImageX;j++)
	    	ImageComplex[i][j]=line[j+St];
	   }

	delete line;



	LineSize=NearestSize()*Zeros;
	St=(LineSize-SizeImageY)/2;
	End=St+SizeImageY;
	line=new complex<double>[LineSize];

	for(i=0;i<SizeImageX;i++)
	   {
	    for (j=0;j<LineSize;j++)
		{
			 if((j>=St) && (j<End))
		   line[j]=ImageComplex[j-St][i];
		 else line[j]=0.;
		}
	    fft1d(line,LineSize,c);
	    for (j=0;j<SizeImageY;j++)
	    	ImageComplex[j][i]=line[j+St];
	}
	delete line;
 //float e2 = Energy();
// e2 = sqrt(e1/e2);
/*for(i=0;i<SizeImageY;i++)
   {
	for(j=0;j<SizeImageX;j++)
	   {
   //     ImageComplex[i][j] = ImageComplex[i][j]*e2;
	   }
   }*/

}

ImageBase::frt2Dz (float Rx, float Ry, float Z,float Kw,int q)
{
  int  i, j;
  float  x, y, Hx, Hy, t;
  complex<float>  ex, ey;

  Hx = Rx/(SizeImageX-1);
  Hy = Ry/(SizeImageX-1);
  t = Kw/(2*Z)*q;
  for(i=0;i<SizeImageY;i++)
	  {
	   y = -Ry/2+i*Hy;
	   ex = polar((float)1.,y*y*t);
	   for(j=0;j<SizeImageX;j++)
		   {
			x = -Rx/2+j*Hx;
			ey = polar((float)1.,x*x*t);
			ImageComplex[i][j] = ImageComplex[i][j]*ex*ey;
		   }
	 }
  fft(q);
}
ImageBase::IKG(float Rx,float Ry,float Z,float Kw)//Интеграл Кирхгофа
{
 int i,j,k,l,I,J;
 float x,y,x1,y1,dx;
 dx = Rx/(SizeImageX-1);
 complex<double>** Array;
 complex<double>** Array1;
 float ** Arrayr;
 float** Arrayi;
 float** Array1r;
 float** Array1i;
 float** Array2r;
 float** Array2i;
 CreateArrayComplexD2(SizeImageX,SizeImageY,Array);
 CreateArrayComplexD2(SizeImageX,SizeImageY,Array1);
 CreateArrayFloat2(SizeImageX,SizeImageY,Arrayr);
 CreateArrayFloat2(SizeImageX,SizeImageY,Arrayi);
 CreateArrayFloat2(SizeImageX,SizeImageY,Array1r);
 CreateArrayFloat2(SizeImageX,SizeImageY,Array1i);
 CreateArrayFloat2(SizeImageX,SizeImageY,Array2r);
 CreateArrayFloat2(SizeImageX,SizeImageY,Array2i);


 for(i=0;i<SizeImageY;i++)
    {
     for(j=0;j<SizeImageX;j++)
        {
		 Array[i][j] = ImageComplex[i][j];
         ImageComplex[i][j]=0.;
		 I = i-SizeImageY/2;J = j-SizeImageX/2;
		 Array1[i][j] = polar(1.,(double)(sqrt((j*dx)*(j*dx)+(i*dx)*(i*dx)+Z*Z)*Kw))/(double)Z*(double)cos(atan(sqrt((j*dx)*(j*dx)+(i*dx)*(i*dx))/Z));

         Arrayr[i][j] = real(Array[i][j]);
         Arrayi[i][j] = imag(Array[i][j]);
         Array1r[i][j] = real(Array1[i][j]);
         Array1i[i][j] = imag(Array1[i][j]);
         Array2r[i][j] = 0.;
         Array2i[i][j] = 0.;
        }
    }


 for(k=0;k<SizeImageY;k++)
    {
     for(l=0;l<SizeImageX;l++)
        {
         for(i=0;i<SizeImageY;i++)
            {
             for(j=0;j<SizeImageX;j++)
                {
//                 ImageComplex[k][l]+=Array[i][j]*Array1[abs(k-i)][abs(l-j)];
                 I = abs(k-i);J = abs(l-j);
                 Array2r[k][l]+=(Arrayr[i][j]*Array1r[I][J]-Arrayi[i][j]*Array1i[I][J]);
                 Array2i[k][l]+=(Arrayr[i][j]*Array1i[I][J]+Arrayi[i][j]*Array1r[I][J]);
//                 ImageComplex[k][l]+=Array[i][j]*polar(1.,(double)(sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1)+Z*Z)*Kw))/(double)Z*cos(atan(sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1))/Z));

                }
            }
		}
    }
for(i=0;i<SizeImageY;i++)
    {
     for(j=0;j<SizeImageX;j++)
        {
         ImageComplex[i][j]=polar(sqrt(Array2r[i][j]*Array2r[i][j]+Array2i[i][j]*Array2i[i][j]),
                                  atan2(Array2i[i][j],Array2r[i][j]));
        }
    }

DeleteArrayComplexD2(SizeImageX,Array);
DeleteArrayComplexD2(SizeImageX,Array1);
DeleteArrayFloat2(SizeImageX,Arrayr);
DeleteArrayFloat2(SizeImageX,Arrayi);
DeleteArrayFloat2(SizeImageX,Array1r);
DeleteArrayFloat2(SizeImageX,Array1i);
DeleteArrayFloat2(SizeImageX,Array2r);
DeleteArrayFloat2(SizeImageX,Array2i);
}
ImageBase::IKG_(float Rx,float Ry,float Z,float Kw,int n)//Интеграл Кирхгофа
{
 int i,j,k,l,I,J,n1,n2;
 float x,y,x1,y1,dx;
 dx = Rx/(SizeImageX-1)*n;
 complex<double>** Array;
 complex<double>** Array1;
 float ** Arrayr;
 float** Arrayi;
 float** Array1r;
 float** Array1i;
 float** Array2r;
 float** Array2i;
 CreateArrayComplexD2(SizeImageX,SizeImageY,Array);
 CreateArrayComplexD2(SizeImageX,SizeImageY,Array1);
 CreateArrayFloat2(SizeImageX,SizeImageY,Arrayr);
 CreateArrayFloat2(SizeImageX,SizeImageY,Arrayi);
 CreateArrayFloat2(SizeImageX,SizeImageY,Array1r);
 CreateArrayFloat2(SizeImageX,SizeImageY,Array1i);
 CreateArrayFloat2(SizeImageX,SizeImageY,Array2r);
 CreateArrayFloat2(SizeImageX,SizeImageY,Array2i);

 n1 = SizeImageX*(n-1)/2/n;
 n2 = SizeImageX*(n+1)/2/n;
 for(i=0;i<SizeImageY;i++)
    {
     for(j=0;j<SizeImageX;j++)
        {
         Array[i][j] = ImageComplex[i][j];
         ImageComplex[i][j]=0.;
		 I = i-SizeImageY/2;J = j-SizeImageX/2;
		 Array1[i][j] = polar(1.,(double)(sqrt((j*dx)*(j*dx)+(i*dx)*(i*dx)+Z*Z)*Kw))/(double)Z*(double)cos(atan(sqrt((j*dx)*(j*dx)+(i*dx)*(i*dx))/Z));
         Arrayr[i][j] = real(Array[i][j]);
         Arrayi[i][j] = imag(Array[i][j]);
		 Array1r[i][j] = real(Array1[i][j]);
         Array1i[i][j] = imag(Array1[i][j]);
         Array2r[i][j] = 0.;
         Array2i[i][j] = 0.;
		}
    }
 for(k=0;k<SizeImageY;k++)
    {
     for(l=0;l<SizeImageX;l++)
        {
         for(i=n1;i<n2;i++)
            {
             I = abs(k-i);
             for(j=n1;j<n2;j++)
                {
                 J = abs(l-j);
                 Array2r[k][l]+=(Arrayr[i][j]*Array1r[I][J]-Arrayi[i][j]*Array1i[I][J]);
                 Array2i[k][l]+=(Arrayr[i][j]*Array1i[I][J]+Arrayi[i][j]*Array1r[I][J]);
                }
            }
        }
    }
for(i=0;i<SizeImageY;i++)
	{
     for(j=0;j<SizeImageX;j++)
		{
         ImageComplex[i][j]=polar(sqrt(Array2r[i][j]*Array2r[i][j]+Array2i[i][j]*Array2i[i][j]),
								  atan2(Array2i[i][j],Array2r[i][j]));
        }
    }

DeleteArrayComplexD2(SizeImageX,Array);
DeleteArrayComplexD2(SizeImageX,Array1);
DeleteArrayFloat2(SizeImageX,Arrayr);
DeleteArrayFloat2(SizeImageX,Arrayi);
DeleteArrayFloat2(SizeImageX,Array1r);
DeleteArrayFloat2(SizeImageX,Array1i);
DeleteArrayFloat2(SizeImageX,Array2r);
DeleteArrayFloat2(SizeImageX,Array2i);
}
ImageBase::ViewImage(TImage *ImageT,float inc)//Вывод на форму изображения
{
int i,j;
 double max,k;
 ImageT->Width=SizeImageX*inc;
 ImageT->Height=SizeImageY*inc;
 max = 0;
 for(i=0;i<SizeImageY;i++)
    {
     for(j=0;j<SizeImageX;j++)
		{
         k = (Image[i][j]);
         if(k>max)
           {
			max = k;
           }
        }
    }
 for(i=0;i<SizeImageY;i++)
    {
     if(i%(int)(1/inc)==0)
     for(j=0;j<SizeImageX;j++)
		{
         k = (Image[i][j]);
         if(j%(int)(1/inc)==0)
         ImageT->Canvas->Pixels[int(inc*j)][int(inc*i)] = (TColor)RGB((int)k,(int)k,(int)k);
        }
    }

}
ImageBase::ViewImage_(TImage *ImageT)//Вывод на форму изображения по размеру
{
int i,j;

double max,k,incX,incY,inc;
 incX = (double)ImageT->Width/SizeImageX;
 incY = (double)ImageT->Height/SizeImageX;
 if(incX>incY)
    inc = incY;
 else
    inc = incX;
 max = 0;
 if(inc<1)
 for(i=0;i<SizeImageY;i++)
    {
     if(i%(int)(1/inc)==0)
     for(j=0;j<SizeImageX;j++)
        {
         k = (Image[i][j]);
         if(j%(int)(1/inc)==0)
         ImageT->Canvas->Pixels[inc*j][inc*i] = (TColor)RGB((int)k,(int)k,(int)k);
		}
    }
 else
 for(i=0;i<SizeImageY*inc;i++)
    {
	 for(j=0;j<SizeImageX*inc;j++)
		{
		 k = (Image[(int)(i/inc)][(int)(j/inc)]);
         ImageT->Canvas->Pixels[j][i] = (TColor)RGB((int)k,(int)k,(int)k);
        }
    }
}
ImageBase::ViewImageComplex(TImage *Image,int q,float inc,float F_dec)//Вывод на форму комплексного изображения
{                                                                     //q=1 - амплитуда, q=2 фаза
 int i,j;
 double max,k;
 for(i=0;i<SizeImageY;i++)//Снижение уровня функции
	{
     for(j=0;j<SizeImageX;j++)
        {
         ImageComplex[i][j] = ImageComplex[i][j]/F_dec;
		}
    }
 Image->Width=SizeImageX*inc;
 Image->Height=SizeImageY*inc;
 switch(q)
       {
        case 0:
               {
				max = 0;
                for(i=0;i<SizeImageY;i++)
                   {
                    for(j=0;j<SizeImageX;j++)
                       {
                        k = norm(ImageComplex[i][j]);
                        if(k>max)
                          {
                           max = k;
                          }
                       }
				   }
                for(i=0;i<SizeImageY;i++)
                   {
                    if(i%(int)(1/inc)==0)
					for(j=0;j<SizeImageX;j++)
                       {
						if(max>0)
						k = norm(ImageComplex[i][j])/max*255.;
						if(j%(int)(1/inc)==0)
						Image->Canvas->Pixels[inc*j][inc*i] = (TColor)RGB((int)k,(int)k,(int)k);
					   }
				   }

				break;
			   }
		case 1:    //амплитуда
			   {
				max = 0;
				for(i=0;i<SizeImageY;i++)
                   {
                    for(j=0;j<SizeImageX;j++)
					   {
                        k = abs(ImageComplex[i][j]);
						if(k>max)
                          {
                           max = k;
                          }
					   }
				   }
				for(i=0;i<SizeImageY;i++)
                   {
					if(i%(int)(1/inc)==0)
                    for(j=0;j<SizeImageX;j++)
                       {
						if(max>0)
                        k = abs(ImageComplex[i][j])/max*255.;
                        if(j%(int)(1/inc)==0)
                        Image->Canvas->Pixels[inc*j][inc*i] = (TColor)RGB((int)k,(int)k,(int)k);
					   }
				   }
				break;
			   }
        case 2:
			   {

                for(i=0;i<SizeImageY;i++)
                   {
					if(i%(int)(1/inc)==0)
                    for(j=0;j<SizeImageX;j++)
                       {
                        k = arg(ImageComplex[i][j])/2/M_PI*255.;
                        if(j%(int)(1/inc)==0)
                        Image->Canvas->Pixels[inc*j][inc*i] = (TColor)RGB((int)k,(int)k,(int)k);
                       }
				   }
                break;
               }
		case 3:        //интенсивность
		{
			max = 0;
			for(i=0;i<SizeImageY;i++)
				   {
				   for(j=0;j<SizeImageX;j++)
				   {
					   k = abs(ImageComplex[i][j])*abs(ImageComplex[i][j]);
						if(k>max)
                          {
                           max = k;
                          }
					   }
				   }
				for(i=0;i<SizeImageY;i++)
                   {
					if(i%(int)(1/inc)==0)
                    for(j=0;j<SizeImageX;j++)
                       {
						if(max>0)
						k = abs(ImageComplex[i][j])*abs(ImageComplex[i][j])/max*255.;
                        if(j%(int)(1/inc)==0)
                        Image->Canvas->Pixels[inc*j][inc*i] = (TColor)RGB((int)k,(int)k,(int)k);
					   }
				   }
				break;
			   }
	   }
}
ImageBase::ViewImageComplex_(TImage *Image,int q,float inc,float F_dec)//Вывод на форму комплексного изображения по размеру
{
 int i,j;
 double max,k,incX,incY;
 for(i=0;i<SizeImageY;i++)//Снижение уровня функции
    {
     for(j=0;j<SizeImageX;j++)
        {
		 ImageComplex[i][j] = ImageComplex[i][j]/F_dec;
        }
    }
// Image->Width=SizeImageX*inc;
// Image->Height=SizeImageY*inc;
 incX = (double)Image->Width/SizeImageX;
 incY = (double)Image->Height/SizeImageX;
 if(incX>incY)
	inc = incY;
 else
    inc = incX;

 switch(q)
	   {
        case 0:
               {
                max = 0;
				for(i=0;i<SizeImageY;i++)
                   {
                    for(j=0;j<SizeImageX;j++)
                       {
                        k = norm(ImageComplex[i][j]);
                        if(k>max)
                          {
                           max = k;
                          }
                       }
                   }
                if(inc<1)
				for(i=0;i<SizeImageY;i++)
                   {
                    if(i%(int)(1/inc)==0)
					for(j=0;j<SizeImageX;j++)
                       {
                        if(max>0)
                        k = norm(ImageComplex[i][j])/max*255.;
                        if(j%(int)(1/inc)==0)
						Image->Canvas->Pixels[inc*j][inc*i] = (TColor)RGB((int)k,(int)k,(int)k);
                       }
                   }
				 else
                 for(i=0;i<SizeImageY*inc;i++)
                    {
                     for(j=0;j<SizeImageX*inc;j++)
						{
                         if(max>0)

                         k = norm(ImageComplex[(int)(i/inc)][(int)(j/inc)])/max*255.;
                         Image->Canvas->Pixels[j][i] = (TColor)RGB((int)k,(int)k,(int)k);
                        }
                    }
                break;
               }
        case 1:
               {
                max = 0;
                for(i=0;i<SizeImageY;i++)
                   {
					for(j=0;j<SizeImageX;j++)
                       {
						k = abs(ImageComplex[i][j]);
						if(k>max)
                          {
                           max = k;
                          }
                       }
				   }
				if(inc<1)
                for(i=0;i<SizeImageY;i++)
                   {
                    if(i%(int)(1/inc)==0)
					for(j=0;j<SizeImageX;j++)
                       {
                        if(max>0)
                        k = abs(ImageComplex[i][j])/max*255.;
                        if(j%(int)(1/inc)==0)
                        Image->Canvas->Pixels[inc*j][inc*i] = (TColor)RGB((int)k,(int)k,(int)k);
                       }
                   }
                else
                 for(i=0;i<SizeImageY*inc;i++)
                    {
                     for(j=0;j<SizeImageX*inc;j++)
                        {
                         if(max>0)
                         k = abs(ImageComplex[(int)(i/inc)][(int)(j/inc)])/max*255.;
                         Image->Canvas->Pixels[j][i] = (TColor)RGB((int)k,(int)k,(int)k);
						}
                    }
                break;
			   }
        case 2:
               {
				if(inc<1)
				for(i=0;i<SizeImageY;i++)
				   {
                    if(i%(int)(1/inc)==0)
                    for(j=0;j<SizeImageX;j++)
					   {
                        k = arg(ImageComplex[i][j])/2/M_PI*255.;
                        if(j%(int)(1/inc)==0)
                        Image->Canvas->Pixels[inc*j][inc*i] = (TColor)RGB((int)k,(int)k,(int)k);
                       }
                   }
                else
                 for(i=0;i<SizeImageY*inc;i++)
                    {
                     for(j=0;j<SizeImageX*inc;j++)
						{
						 if(max>0)
						 k = arg(ImageComplex[(int)(i/inc)][(int)(j/inc)])/2/M_PI*255.;
						 Image->Canvas->Pixels[j][i] = (TColor)RGB((int)k,(int)k,(int)k);
						}
					}
				break;
			   }

	   }
}
int ImageBase::VortexAxicon(int m,int KL,int *mn,float *ang,float freq,float size)//Заполненияе элемента вихревым аксиконом
{
  int i,j,k;
 float x,y,r,fi,p,dx;
 dx = size/SizeImageX;
 int IB_;
 IB_ = 0;
 for ( i=0;i<SizeImageY;i++ ){
	   y = (i-SizeImageY/2)*dx;
	   for ( j=0;j<SizeImageX;j++ ){
		   x = (j-SizeImageX/2)*dx;
		   r = sqrt(x*x+y*y);
		   if (atan2(y,(float)(x+0.0000001))>=0)
			  fi = atan2(y,(float)(x+0.0000001));
		   else
			  fi = atan2(y,(float)(x+0.0000001))+2*M_PI;
		   if (r<(SizeImageX/2.)*dx)
		   {
			   ImageComplex[i][j] = polar((float)1.,(float)(m*fi));
		   }
		   else {
			   ImageComplex[i][j] = polar((float)0.,(float)(0));
		   }
		   ImageComplex[i][j] = ImageComplex[i][j]*polar((float)1.,(float)(freq)*(r));
		   Image[i][j] = arg(ImageComplex[i][j])/(float)2./(float)M_PI*(float)255.;
		   IB_ = Image[i][j]/(int)(256/KL);
		   if (r<(SizeImageX/2.)*dx)
		   {
			  k = IB_;
			  ImageComplex[i][j] = polar((float)1.,(float)(mn[k]*fi+M_PI/180.*ang[k]));
		   }
		   else
		   {
			  ImageComplex[i][j] = polar((float)0.,(float)(0));
		   }
		}
	  }



}
float ImageBase::MomImageComplex(int n)//Определение момента светового поля
{
int i,j,k,l,k1,k2,l1,l2,Num;
float x,y,r,fii,dfii,dfiin,mom,f1,f2,dm;
dfiin = M_PI/50;
mom = 0;
Num = 0;
for(i=10;i<SizeImageY/2;i++)
   {
    r = i;
//    dfiin = 8./r;
    for(j=0;j<n;j++)
       {
        fii = j*2*M_PI/n;
        k1 = SizeImageY/2+r*cos(fii+dfiin);
		l1 = SizeImageY/2+r*sin(fii+dfiin);
		f1 = arg(ImageComplex[k1][l1]);
        k2 = SizeImageY/2+r*cos(fii-dfiin);
		l2 = SizeImageY/2+r*sin(fii-dfiin);
        f2 = arg(ImageComplex[k2][l2]);
        dfii = 0.5*
               acos(
                    ((k1-SizeImageY/2)*(k2-SizeImageY/2)+(l1-SizeImageY/2)*(l2-SizeImageY/2))/
                    (
					 sqrt((float)
						  (k1-SizeImageY/2)*(k1-SizeImageY/2)+(l1-SizeImageY/2)*(l1-SizeImageY/2)
						  )*
					 sqrt((float)
                          (k2-SizeImageY/2)*(k2-SizeImageY/2)+(l2-SizeImageY/2)*(l2-SizeImageY/2)
                         )
                     )
                    );
        dm = (f2-f1);
		if(dfii==0)
          dfii=dfiin;
        if(fabs(dm)<M_PI)
          dm = dm/2/dfii;
		else
          if(dm>0)
            dm = (dm-2*M_PI)/2/dfii;
		  else
			dm = (dm+2*M_PI)/2/dfii;
		mom +=dm;
		Num++;
	   }
   }
   ;
mom = mom/Num;
//mom = mom/2/M_PI;
return (mom);
}
float ImageBase::EMomImageComplex(int n)//Определение момента светового поля
{
int i,j,Num;
float x,y,r,fii,mom,dfx,dfy,dm;
Num = 0;
mom = 0;
for(i=1;i<SizeImageY-1;i++)
   {
	x = i-SizeImageY/2;
	for(j=1;j<SizeImageX-1;j++)
	   {
		y = j-SizeImageX/2;
		r = sqrt(x*x+y*y);
		if (atan2(y,(float)(x+0.000001))>=0)
		   fii = atan2(y,(float)(x+0.000001));
		else
		   fii = atan2(y,(float)(x+0.000001))+2*M_PI;
		dm = arg(ImageComplex[i+1][j])-arg(ImageComplex[i-1][j]);
		if(fabs(dm)<M_PI)
		  dm = dm;
		else
		  if(dm>0)
			dm = dm-2*M_PI;
		  else
			dm = dm+2*M_PI;
		dfx = dm/2.;
		dm = (arg(ImageComplex[i][j+1])-arg(ImageComplex[i][j-1]));
		if(fabs(dm)<1.95*M_PI)
		  dm = dm;
		else
		  if(dm>0)
			dm = dm-2*M_PI;
		  else
			dm = dm+2*M_PI;
		dfy = dm/2.;

		dm = -r*sin(fii)*dfx+r*cos(fii)*dfy;
		if(r<SizeImageX/2)
		  {
		   mom +=dm;
		   Num++;
		  }
	   }
   }
   ;
mom = mom/Num;
//mom = mom/2/M_PI;
return (mom);
}
ImageBase::CenterCat(int R)//Вырезать центр изображения
{
 int i,j;
  if (R!=0)
  for(i=-R;i<=R;i++)
	 {
	  for(j=-R;j<=R;j++)
		 {
		  ImageComplex[SizeImageY/2+i][SizeImageX/2+j]=0;
		 }
	 }
}
ImageBase::FourFunction(float **FourC,int Size)//Заполнение изображения косинусным рядом с коэф. FourC,
												 // Size-размерность массива
{
 int i,j,n,m;
 float c1,c2;
 float **mas;
 CreateArrayFloat2(SizeImageX,SizeImageY,mas);
 for(i=0;i<SizeImageY;i++)
	{
	 for(j=0;j<SizeImageX;j++)
		{
		 ImageComplex[i][j] = polar((float)1.,(float)M_PI);
		 mas[i][j] = M_PI;
		}
	}
 for(n=0;n<Size;n++)
	{
	 for(m=0;m<Size;m++)
		{
		 for(i=0;i<SizeImageY;i++)
			{
			 for(j=0;j<SizeImageX;j++)
				{
				 c1 = cos((2*M_PI*i*(n+1))/(float)SizeImageY);
				 c2 = cos((2*M_PI*j*(m+1))/(float)SizeImageX);
				 mas[i][j] += FourC[n][m]*M_PI*(c1*c2);
				 ImageComplex[i][j] = polar((float)1.,mas[i][j]);
//                 ImageComplex[i][j] += polar((float)1.,
  //               (float)(FourC[n][m]*M_PI*(c1+c2)/2.));
				}
			}
		}
	}
}
float ImageBase::ERing(int R1,int R2)// Определение энергии внутри кольца R1<r<R2
{
 int i,j;
 float energy=0,r;
 for(i=0;i<SizeImageY;i++)
	{
	 for(j=0;j<SizeImageX;j++)
		{
		 r=sqrt((float)(i-SizeImageY/2)*(i-SizeImageY/2)+
				(float)(j-SizeImageX/2)*(j-SizeImageX/2));
		 if((r>R1)&&(r<R2))
		   energy += norm(ImageComplex[i][j] );
		}
	}
 return (energy);
}
int   ImageBase::SRing()//Поиск колец
{
 int i;
 float a,b,c;
 float *SectionR;
 Section  = new float[SizeImageY/2];
 SectionR = new float[SizeImageY/2];
 for(i=SizeImageY/2;i<SizeImageY;i++)
	{
	 Section = 0;
	 SectionR[i] = norm(ImageComplex[i][SizeImageX/2]);
	}
  for(i=0;i<SizeImageY/2-3;i++)
	{
	 a=SectionR[i];b=SectionR[i+1];c=SectionR[i+2];
	 if((a<b)&&(b<c))
	   Section[i]=1;
	 else
	   if((a>b)&&(b>c))
		 Section[i+2]=2;
	}
  for(i=1;i<SizeImageY/2-2;i++)
	 {
	 // if((Section[i]==2)&&(Section[i+1]==2))
		Section[i]=0;
	 }
  for(i=SizeImageY/2-2;i>0;i--)
	 {
	  if((Section[i]==1)&&(Section[i-1]==1))
		Section[i]=0;
	 }
}
ImageBase::ImageBase(int SX,int SY)
{
 SizeImageX  = SX;
 SizeImageY  = SY;
 Zeros = 1;
 CreateArrayUC2(SizeImageY,SizeImageX,Image);
 CreateArrayComplex2(SizeImageY,SizeImageX,ImageComplex);
}
ImageBase::ImageBase(char*filename)
{
	AnsiString path = ExtractFilePath(Application->ExeName)+filename;
	ifstream fin(path.c_str());
	if (!fin.is_open()) //tесли не открылся
	{
		ShowMessage("Не могу открыть файл");
		SizeImageX=1;
		SizeImageY=1;
		Zeros=1;
		CreateArrayUC2(SizeImageY,SizeImageX,Image);
		CreateArrayComplex2(SizeImageY,SizeImageX,ImageComplex);
	}
	else
	{
		fin >> SizeImageX >> SizeImageY;
		Zeros = 1;
		CreateArrayUC2(SizeImageY,SizeImageX,Image);
		CreateArrayComplex2(SizeImageY,SizeImageX,ImageComplex);
		for(int i=0; i<SizeImageX;i++)
		{
			for(int j=0; j<SizeImageY;j++)
			{
				fin>>ImageComplex[i][j];
			}
		}
	}
	fin.close();
}
ImageBase::~ImageBase()
{
 DeleteArrayUC2(SizeImageY,Image);
 DeleteArrayComplex2(SizeImageY,ImageComplex);
}

ReadBMPFile(unsigned char *FileName,int &X,int &Y)//Чтение заголовка BMP файла
{
 BmpFile BMP;
 fileReturnedCode rc=frcOk;
 if((rc=BMP.OpenFile((char *)FileName))==frcOk )
   {
	Y = BMP.GetVerSize();
	X = BMP.GetHorSize();
   }
	BMP.CloseFile();
}

