//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormForGrafics.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGF10 *GF10;
//---------------------------------------------------------------------------
__fastcall TGF10::TGF10(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TGF10::Button1Click(TObject *Sender)
{
	GF10->Image1->Picture->Bitmap=NULL;
	GF10->Image2->Picture->Bitmap=NULL;
	GF10->Image3->Picture->Bitmap=NULL;
	GF10->Image4->Picture->Bitmap=NULL;
	GF10->Image5->Picture->Bitmap=NULL;
//	GF10->Image6->Picture->Bitmap=NULL;
//	GF10->Image7->Picture->Bitmap=NULL;
//	GF10->Image8->Picture->Bitmap=NULL;
}
//---------------------------------------------------------------------------

