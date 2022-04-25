//---------------------------------------------------------------------------

#include <System.hpp>
#include <fstream>
#pragma hdrstop

#include "Unit3.h"
#include "Unit2.h"
#include "Unit1.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall Tread2::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall Tread2::Tread2(TEvent *myEvent,byte *dataBuffer, bool CreateSuspended)
	: TThread(CreateSuspended)
{
	 MyEvent=myEvent;
	 DataBuffer=dataBuffer;
}
//---------------------------------------------------------------------------
void __fastcall Tread2::Execute()
{
	ofstream out("Copy.txt");
	j=0;
	//Form1->Label1->Caption = j;
	while(!Terminated){

		if(MyEvent->WaitFor(0)==wrSignaled)
		{
		out.write(reinterpret_cast<char*>(DataBuffer),512);
		j++;
		MyEvent->ResetEvent();
		}
	}
	out.close();
}
//---------------------------------------------------------------------------


