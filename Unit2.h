//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class Tread : public TThread
{
private:
	class Tread2 *Tread2ptr;
protected:
	void __fastcall Execute();
	void __fastcall UpdateCaption();
public:
	__fastcall Tread(bool CreateSuspended);
	TEvent *MyEvent;
    byte *dataBuffer;
	int j=0;
};
//---------------------------------------------------------------------------
#endif
