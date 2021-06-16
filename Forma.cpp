//---------------------------------------------------------------------------
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
#include "FormForGrafics.h"
#include "CountPoint.h"
#include "ParametersLightSourse.h"
#include "ParametersFilter.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
TForm1 *Form1;
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}

void AddArr(complex<float> **array,complex<float> **array1,int Nx,int Ny, float mu)
{
	float temp;
	for(int x=0;x<Nx;x++)
		{

		for(int y=0;y<Ny;y++)
			{
			//IB.ImageComplex[x][y]=polar(abs(IB.ImageComplex[x][y])*abs(IB1.ImageComplex[x][y]),arg(IB1.ImageComplex[x][y])+arg(IB.ImageComplex[x][y]));
			temp=sqrt(abs(array[x][y])*abs(array1[x][y]));
			array[x][y]=array[x][y]+array1[x][y];/*+2*mu*sqrt(IB1.ImageComplex[x][y]*IB.ImageComplex[x][y]);/*cos(arg(IB.ImageComplex[x][y])-arg(IB1.ImageComplex[x][y])); */
			array[x][y]=polar(abs(array[x][y])+2*mu*temp,arg(array[x][y]));
			//IB.ImageComplex[x][y]=polar(abs(IB.ImageComplex[x][y])+abs(IB1.ImageComplex[x][y])+2*mu*sqrt(abs(IB1.ImageComplex[x][y])*abs(IB.ImageComplex[x][y])),(arg(IB1.ImageComplex[x][y])*arg(IB.ImageComplex[x][y])));/*cos(arg(IB.ImageComplex[x][y])-arg(IB1.ImageComplex[x][y])); */
			}
		}
}
//---------------------------------------------------------------------------











void __fastcall TForm1::N1Click(TObject *Sender)
{
Form8->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{

	AnsiString path = ExtractFilePath(Application->ExeName)+"InputWave";
	int j=0;
	while(DeleteFile(path+IntToStr(j)))
	{
		j++;
	}
	GF10->Close();
	Form1->Close();
}
//---------------------------------------------------------------------------





















//---------------------------------------------------------------------------

void __fastcall TForm1::ButWaveClick(TObject *Sender) //идеальная система
{
	int X=StrToInt(Form1->Edit1->Text);
	int Y=StrToInt(Form1->Edit1->Text);
	float FI2;
	ImageBase IB(X,Y);
	//double alfa=StrToFloat(Form1->Edit4->Text); //альфа волнового фронта(расстояние между источниками)
	float sig=StrToFloat(Form1->SigmaEd->Text);//сигма амплитуды

	//---------------Задаем входящий волновой фронт------------------------------
	IB.InputWave("InputWave");     //InputWave сюда выводим массивы
	IB.SumPoint("InputWave");
	IB.ViewImageComplex(Form1->Image5,1,1,1);
	IB.ViewImageComplex(Form1->Image6,2,1,1);

	GraficTA(40,clBlack, IB.ImageComplex, 127,255,GF10->Image1);
	GF10->Visible=true;
	IB.OutputToFile("SystemArray0");
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button2Click(TObject *Sender) //преобразование Фурье
{
	float mu=StrToFloat(Form1->Edit6->Text);//коэффициент когерентности
	int size=StrToInt(Form1->Edit3->Text)/*увеличение*/;
	int X=StrToInt(Edit1->Text),Y=StrToInt(Edit2->Text);
	ImageBase IB(X,Y);
	IB.Zeros=size;
	IB.FourierTransform("InputWave");
	IB.SumPoint("InputWave",mu);
	//IB.Coherence("InputWave", mu);
	IB.ViewImageComplex(Form1->Image3,1,1,1);
	IB.ViewImageComplex(Form1->Image4,2,1,1);
	IB.OutputToFile("SystemArray0");
	GraficTA(40,clBlack, IB.ImageComplex, 127,255,GF10->Image4);
	GF10->Visible=true;
	IB.WriteFile("test",1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)//амплитудная аподизация
{
	//int size=StrToInt(Form1->Edit3->Text)/*увеличение*/;
	int X=StrToInt(Edit1->Text),Y=StrToInt(Edit2->Text);
	ImageBase IB(X,Y);
	float g=StrToFloat(Form1->Edit9->Text);  //степень аподизации
	IB.ApodizationA("InputWave",g);
	IB.SumPoint("InputWave");
	IB.ViewImageComplex(Form1->Image1,1,1,1);
	IB.ViewImageComplex(Form1->Image2,2,1,1);
	IB.OutputToFile("SystemArray0");
	GraficTA(40,clBlack, IB.ImageComplex, 127,255,GF10->Image2);
	GF10->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
	float koef=StrToFloat(Form1->Edit7->Text);
	//int size=StrToInt(Form1->Edit3->Text)/*увеличение*/;
	int X=StrToInt(Edit1->Text),Y=StrToInt(Edit2->Text);
	ImageBase IB(X,Y);
	float g=StrToFloat(Form1->Edit9->Text);  //степень аподизации
	IB.ApodizationF("InputWave",g,koef);
	IB.SumPoint("InputWave");
	IB.ViewImageComplex(Form1->Image1,1,1,1);
	IB.ViewImageComplex(Form1->Image2,2,1,1);
	IB.OutputToFile("SystemArray0");
	//GraficTA(40,clBlack, IB.ImageComplex, 127,255,GF10->Image2);
	GF10->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
	//int size=StrToInt(Form1->Edit3->Text)/*увеличение*/;
	int X=StrToInt(Edit1->Text),Y=StrToInt(Edit2->Text);
	ImageBase IB(X,Y);
	IB.ReadAbberations("InputWave","cellarray1.txt",StrToFloat(Form1->Edit5->Text));
	IB.SumPoint("InputWave");
	IB.ViewImageComplex(Form1->Image7,1,1,1);
	IB.ViewImageComplex(Form1->Image8,2,1,1);
	IB.OutputToFile("SystemArray0");
	GraficTA(40,clBlack, IB.ImageComplex, 127,255,GF10->Image3);
	GF10->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
	Form1->Image1->Picture->Bitmap=NULL;
	Form1->Image2->Picture->Bitmap=NULL;
	Form1->Image3->Picture->Bitmap=NULL;
	Form1->Image4->Picture->Bitmap=NULL;
	Form1->Image5->Picture->Bitmap=NULL;
	Form1->Image6->Picture->Bitmap=NULL;
	Form1->Image7->Picture->Bitmap=NULL;
	Form1->Image8->Picture->Bitmap=NULL;
	AnsiString path = ExtractFilePath(Application->ExeName)+"InputWave";
	int j=0;
	while(DeleteFile(path+IntToStr(j)))
	{
		j++;
	}
	//for(int j=0;j<100;j++)
	//{
	//	DeleteFile(path+IntToStr(j));
	//}
	Form1->Memo1->Lines->Clear();
	/*Form1->Image1->Picture->Bitmap->FreeImage();
	Form1->Image2->Picture->Bitmap->FreeImage();
	Form1->Image3->Picture->Bitmap->FreeImage();
	Form1->Image4->Picture->Bitmap->FreeImage();
	Form1->Image5->Picture->Bitmap->FreeImage();
	Form1->Image6->Picture->Bitmap->FreeImage();
	Form1->Image7->Picture->Bitmap->FreeImage();
	Form1->Image8->Picture->Bitmap->FreeImage();*/
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button8Click(TObject *Sender)
{
	int X=StrToInt(Form1->Edit1->Text);
	int Y=StrToInt(Form1->Edit1->Text);
	float FI2;
	ImageBase IB(X,Y);
	double alfa=StrToFloat(Form1->Edit4->Text); //альфа волнового фронта(расстояние между источниками)
	float sig=StrToFloat(Form1->SigmaEd->Text);//сигма амплитуды

	//---------------Задаем входящий волновой фронт------------------------------
	IB.InputWave(alfa,sig);
	IB.ViewImageComplex(Form1->Image5,1,1,1);
	IB.ViewImageComplex(Form1->Image6,2,1,1);
	GraficTA(40,clBlack, IB.ImageComplex, 127,255,GF10->Image1);
	GF10->Visible=true;
	IB.OutputToFile("SystemArray0");
}
//---------------------------------------------------------------------------


void __fastcall TForm1::N2Click(TObject *Sender)
{
	  CPForm->Visible=true;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button9Click(TObject *Sender)//Еще одно преобразование Фурье
{
	float mu=StrToFloat(Form1->Edit6->Text);//коэффициент когерентности
	int size=StrToInt(Form1->Edit3->Text)/*увеличение*/;
	int X=StrToInt(Edit1->Text),Y=StrToInt(Edit2->Text);
	ImageBase IB(X,Y);
	IB.Zeros=size;
	IB.FourierTransform("InputWave");
	IB.SumPoint("InputWave");
	//IB.Coherence("InputWave", mu);
	IB.ViewImageComplex(Form1->Image1,1,1,1);
	IB.ViewImageComplex(Form1->Image2,2,1,1);
	IB.OutputToFile("SystemArray0");
	GraficTA(40,clBlack, IB.ImageComplex, 127,255,GF10->Image4);
	GF10->Visible=true;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button10Click(TObject *Sender)
{
	float mu=StrToFloat(Form1->Edit6->Text);//коэффициент когерентности
	int size=StrToInt(Form1->Edit3->Text)/*увеличение*/;
	int X=StrToInt(Edit1->Text),Y=StrToInt(Edit2->Text);
	ImageBase IB(X,Y);
	IB.Zeros=size;
	IB.FourierTransform1("SystemArray0");
	//IB.Coherence("InputWave", mu);
	IB.ViewImageComplex(Form1->Image7,1,1,1);
	IB.ViewImageComplex(Form1->Image8,2,1,1);
	IB.OutputToFile("SystemArray0");
	GraficTA(40,clBlack, IB.ImageComplex, 127,255,GF10->Image4);
	GF10->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button11Click(TObject *Sender)
{
	int X=StrToInt(Edit1->Text),Y=StrToInt(Edit2->Text);
	ImageBase IB(X,Y);
	IB.AddFilter("InputWave");
	IB.AddFilter("System Array");
	IB.SumPoint("InputWave");
	IB.ViewImageComplex(Form1->Image5,1,1,1);
	IB.ViewImageComplex(Form1->Image6,2,1,1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button12Click(TObject *Sender)
{
	int X=StrToInt(Form1->Edit1->Text);
	int Y=StrToInt(Form1->Edit1->Text);
	float FI2;
	ImageBase IB(X,Y);
	//double alfa=StrToFloat(Form1->Edit4->Text); //альфа волнового фронта(расстояние между источниками)
	float sig=StrToFloat(Form1->SigmaEd->Text);//сигма амплитуды

	//---------------Задаем входящий волновой фронт------------------------------
	IB.InputLightSourse("InputWave");     //InputWave сюда выводим массивы
	IB.SumPoint("InputWave");
	IB.ViewImageComplex(Form1->Image5,1,1,1);
	IB.ViewImageComplex(Form1->Image6,2,1,1);

	GraficTA(40,clBlack, IB.ImageComplex, 127,255,GF10->Image1);
	GF10->Visible=true;
	IB.OutputToFile("SystemArray0");
	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N3Click(TObject *Sender)
{
	PLSForm->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::expifi1Click(TObject *Sender)
{
	int X=StrToInt(Edit1->Text),Y=StrToInt(Edit2->Text);
	ImageBase IB(X,Y);
	IB.AddFilter("InputWave");
	IB.AddFilter("System Array");
	IB.SumPoint("InputWave");
	IB.ViewImageComplex(Form1->Image7,1,1,1);
	IB.ViewImageComplex(Form1->Image8,2,1,1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N6Click(TObject *Sender)
{
	Form10->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N7Click(TObject *Sender)
{
	int X=StrToInt(Edit1->Text),Y=StrToInt(Edit2->Text);
	ImageBase IB(X,Y);
	IB.CatCenter("InputWave",StrToInt(Form10->Edit1->Text),StrToInt(Form1->Edit3->Text));
	IB.SumPoint("InputWave");
	IB.ViewImageComplex(Form1->Image7,1,1,1);
	IB.ViewImageComplex(Form1->Image8,2,1,1);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::N8Click(TObject *Sender)
{
	int X=StrToInt(Edit1->Text),Y=StrToInt(Edit2->Text);
	ImageBase IB(X,Y);
	IB.CatEdge("InputWave",StrToInt(Form10->Edit1->Text), StrToInt(Form1->Edit3->Text));
	IB.SumPoint("InputWave");
	IB.ViewImageComplex(Form1->Image7,1,1,1);
	IB.ViewImageComplex(Form1->Image8,2,1,1);
}
//---------------------------------------------------------------------------


