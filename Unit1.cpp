//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
int N=100
int i,j;
int A[N][N];    // ?????? ???????? ?????
for(i=0;i<N;i++) {
	for(j=0;j<N;j++) {
		A[i][j]=1;
    }
}

}
//---------------------------------------------------------------------------
