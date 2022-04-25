//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class Tread2 : public TThread
{
private:
	TEvent *MyEvent;
	byte *DataBuffer;
	int j;
protected:
	void __fastcall Execute();
public:
	__fastcall Tread2(TEvent *myEvent,byte *dataBuffer, bool CreateSuspended);

};
//---------------------------------------------------------------------------
#endif
