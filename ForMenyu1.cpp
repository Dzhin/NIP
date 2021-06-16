//---------------------------------------------------------------------------
#include <fstream>
#include <vcl.h>
#pragma hdrstop
#include "Forma.h"
#include "Unit9.h"
#include "ForMenyu1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm8 *Form8;
//---------------------------------------------------------------------------
__fastcall TForm8::TForm8(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm8::Button1Click(TObject *Sender)
{
Form8->StringGrid1->Visible="true";
Form8->Label1->Visible="true";
int count=StrToInt(Form8->Edit1->Text),i,j;
Form8->StringGrid1->RowCount=count+1;
Form8->StringGrid1->Cells[0][0]="Cmn";
Form8->StringGrid1->Cells[1][0]="n";
Form8->StringGrid1->Cells[2][0]="m";


for (i = 0; i < 3; i++) {
	for (j = 1; j < count+2; j++) {
	   Form8->StringGrid1->Cells[i][j]="0";
	}
}
}
//---------------------------------------------------------------------------


void __fastcall TForm8::Button3Click(TObject *Sender)
{
Form8->Close();	
}
//---------------------------------------------------------------------------


void __fastcall TForm8::Button2Click(TObject *Sender)
{
int i,j,count=StrToInt(Form8->StringGrid1->RowCount);


ofstream fout;
AnsiString path = ExtractFilePath(Application->ExeName)+"cellarray1.txt";
fout.open(path.c_str());
fout << Form8->StringGrid1->RowCount-1;

for (j = 1; j < count; j++) {
	fout << "\n";
	for (i = 0; i < 3; i++) {
	   fout <<  StrToFloat(Form8->StringGrid1->Cells[i][j]) << " ";

	}
}
fout.close();
		Form8->Close();	
}
//---------------------------------------------------------------------------




