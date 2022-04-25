//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "Unit2.h"
#include "Unit1.h"
#include "Unit3.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall Tread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall Tread::Tread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
	FreeOnTerminate=true;
	MyEvent= new TEvent(NULL,true,false,"",false);
	dataBuffer = new byte[512];
	Tread2ptr=new Tread2(MyEvent,dataBuffer,true);
}
//---------------------------------------------------------------------------
void __fastcall Tread::Execute()
{
	j=0;
	wchar_t *fileName =L"\\\\.\\PhysicalDrive0";

   HANDLE fileHander=CreateFileW(fileName,
   GENERIC_READ,
   FILE_SHARE_READ | FILE_SHARE_WRITE,
   NULL,
   OPEN_EXISTING,
   FILE_ATTRIBUTE_NORMAL,
   NULL);

	if(fileHander == INVALID_HANDLE_VALUE)
	{
	Form1->Label1->Caption="Ошибка чтения диска, попробуйте запустить от имени Администратора.";
    Sleep(INFINITY);
	}

    Tread2ptr->Start();
	while(!Terminated)
	{
    LARGE_INTEGER sectorOffset;
	sectorOffset.QuadPart=j*512;

	unsigned long currentPosition = SetFilePointer(fileHander,sectorOffset.LowPart,&sectorOffset.HighPart ,FILE_BEGIN);

	 if(currentPosition != sectorOffset.LowPart)  {
		Form1->Label1->Caption="Ошибка1";
		CloseHandle(fileHander);
		delete[] dataBuffer;
        break;
	 }

	 while (MyEvent->WaitFor(0)==wrSignaled)
		 {
			 Sleep(1);
         }


	 DWORD bytesToRead=512;
	 DWORD bytesRead;
	 bool readResult = ReadFile(fileHander,dataBuffer,bytesToRead,&bytesRead,NULL);

	 if(readResult == false || bytesRead != bytesToRead){
		 Form1->Label1->Caption="Ошибка2";
		 CloseHandle(fileHander);
		 delete[] dataBuffer;
		 break;
	 }


	MyEvent->SetEvent();
	Synchronize(&UpdateCaption);
	j++;
	}

	Tread2ptr->Terminate();
	CloseHandle(fileHander);
	delete[] dataBuffer;
	Synchronize(&UpdateCaption);
	delete Tread2ptr;
}
//---------------------------------------------------------------------------
 void __fastcall Tread::UpdateCaption()
	  {
		Form1->Label1->Caption = j*512/1024;
        Form1->Label1->Caption +=L" Килобайт скопированно";
	  }