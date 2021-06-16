//---------------------------------------------------------------------------

#ifndef FormForGraficsH
#define FormForGraficsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TGF10 : public TForm
{
__published:	// IDE-managed Components
	TImage *Image1;
	TImage *Image2;
	TImage *Image4;
	TImage *Image3;
	TImage *Image5;
	TButton *Button1;
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TGF10(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGF10 *GF10;
//---------------------------------------------------------------------------
#endif
