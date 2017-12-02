// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"

//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	are in machine.h.
//----------------------------------------------------------------------
#define MAX_FILE_HANDLER 10
#define MAX_INT 10
#define LIMIT 1000
#include "string.h"
void
ExceptionHandler(ExceptionType which)
{
    int type = machine->ReadRegister(2); // doc tu thanh ghi so 2 de biet no co ma syscall la gi
	switch(which)
	{
		case NoException:
		printf("NoException\n");
		return;
		case SyscallException: //neu exception la syscall

			switch(type)
			{
				case SC_Halt:	//neu la syscall halt
				DEBUG('a', "Shutdown, initiated by user program.\n");
	   			interrupt->Halt(); //thuc hien halt tat may
				break;
				case SC_Open:
				break;
				case SC_Close:
				break;
				case SC_Create:
				break;
				case SC_Read:
				break;
				case SC_Write:
				break;
				case SC_Exit:
				break;
				case SC_Exec:
				break;
				case SC_Join:
				break;
				case SC_Fork:
				break;
				case SC_Yield:
				break;
				case SC_Sub:
				int op1; 
				int op2;
				int result;
				op1 = machine->ReadRegister (4);
				op2 = machine->ReadRegister (5);
				result = op1 - op2;
				machine->WriteRegister (2, result);
				interrupt->Halt();
				break;
				case SC_ReadInt:
				{

					DEBUG('a', "Doc so nguyen tu console.\n");
					int number = 0;
					int nlength = 0;
					int i;
					char* buffer = new char[MAX_INT];
					nlength = gSynchConsole->Read(buffer, MAX_INT);//doc chuoi tu man hinh console
					i = buffer[0] == '-' ? 1:0 ;//de xac dinh thu tu bat dau cua chuoi
					for (; i < nlength; ++i)
					{
						if(buffer[i] < '0' || buffer[i] > '9')//xu li neu k phai la so
						{
						number = 0;
						break;
						}
						number = number*10 + ((int)buffer[i] - 48);
					}
					number = buffer[0] == '-' ? -1*number : number;//neu la so am nhan vs -1
					machine->WriteRegister(2, number);//luu kq ra thanh ghi so 2
					delete buffer;
				}
				break;
				case SC_PrintInt:
				{
					char s[MAX_INT], neg, tmp;
					neg = '-';
					int i, n, mid, sz;
					i = n = 0;
					DEBUG('a', "Doc gia tri tu thanh ghi r4");
					n = machine->ReadRegister(4);//doc tu thanh ghi so 4
					if (n < 0)
					{
						gSynchConsole->Write(&neg,1);//xuat ra man hinh console 
						n = -n;
					}
					do {//doi ra chuoi xuat ra
						s[i++] = n%10 + '0';
					}	while (( n /= 10) > 0);
					sz = i;
					s[sz] = '\n';//end
					mid = i / 2;
					while (i-->mid)//swap
					{
						tmp = s[sz-i-1];
						s[sz-i-1] = s[i];
						s[i] = tmp;
					}
					gSynchConsole->Write(s, sz);//xuat ra console
				}
				break;
				case SC_ReadChar:
				{
					int nlength;
					char buffer[MAX_INT];
					nlength = gSynchConsole->Read(buffer, MAX_INT);//doc vao tu man hinh console
					machine->WriteRegister(2, buffer[nlength-1]);//luu ra thanh ghi so 2
				}
				break;
				case SC_PrintChar:
				{
					char ch;
					ch = (char) machine->ReadRegister(4);	//doc tu thanh ghi so 4
					gSynchConsole->Write(&ch, 1);		//xuat ra man hinh console
					break;
				}
				case SC_ReadString:
				{
					char *buf = new char[LIMIT];
					if (buf == 0) break;
					int bufAddrUser = machine->ReadRegister(4);//doc dia chi chuoi tu thanh ghi so 4(con tro toi vung nho cua chuoi do)
					int length = machine->ReadRegister(5);// doc chieu dai chuoi tu thanh ghi so 5
					int sz = gSynchConsole->Read(buf, length); // doc vao chuoi buf
					machine->System2User(bufAddrUser, sz, buf);// chuyen du lieu tu kernel space sang user space
					//ham nay de ghi chuoi buf voi length = sz vao vung nho ma bufAddrUser dang giu
					delete[] buf;
				}
				break;
				case SC_PrintString:
				{
					//char ch;
					int bufAddr = machine->ReadRegister(4);//doc tu thanh ghi so 4
					int i = 0;
					char *buf = new char[LIMIT];
					buf = machine->User2System(bufAddr, LIMIT);// doc gia tri chuoi trong vung nho ma bufAddr giu vao chuoi buf
					while (buf[i] != 0 && buf[i] != '\n')
					{
						gSynchConsole->Write(buf+i, 1);

					//ch = buf[i];//doc dia chi tu thanh ghi so 4
					//gSynchConsole->Write(&ch, 1);//viet ra man hinh console
						i++;
					}
					buf[i] = '\n';
					gSynchConsole->Write(buf+i,1);
					//ch = buf[i];//doc tu thanh ghi so 4
					//gSynchConsole->Write(&ch, 1);//viet ra man hinh console
					delete[] buf;
				}
				break;
				case SC_CreateFile: //------------- DO AN 2 --------------------
				{
					//lay tham so ten tep tu thanh ghi r4
					int bufAddr = machine->ReadRegister(4); // doc file name tu user
					char *buf = new char[LIMIT];
					buf = machine->User2System(bufAddr, LIMIT);//chuyen buffAddr con tro dang tro den tu user sang system
					
					if (buf == NULL)
					{
					printf("\nKhong du bo nho trong he thong!");

					machine->WriteRegister(2,-1); // tra ve loi vao thanh ghi r2
					
					}
					// tao file moi 
					if (fileSystem->Create(buf, 0) == false)
					{
						DEBUG('f',"Khong the tao file");
						printf("\nKhong du bo nho trong he thong!");

						machine->WriteRegister(2, -1);//tra ve loi cho nguoi dung
					} else 
					{
						DEBUG('f',"Tao file thanh cong");
						machine->WriteRegister(2, 0);
					};
					delete [] buf;
					break;
				}
				case SC_OpenFileID:
				{
					int bufAddr = machine->ReadRegister(4); 
					int type = machine->ReadRegister(5);// 0 la doc + ghi, 1 la doc
					char *buf = new char[LIMIT];
					if (fileSystem->index > 10)
					{
					printf("\n ban chi luu dac ta toi da 10 file");
						machine->WriteRegister(2, -1);
						delete[] buf;
						break;
					}
					buf = machine->User2System(bufAddr, LIMIT);
					if (strcmp(buf,"stdin") == 0)
					{
						printf("stdin mode\n");
						machine->WriteRegister(2, 0);//console input
						break;
					}
					if (strcmp(buf,"stdout") == 0)
					{
						printf("stdout mode\n");
						machine->WriteRegister(2, 1);//console ouput
						break;
					}
					if ((fileSystem->openf[fileSystem->index] = fileSystem->Open(buf, type)) != NULL)
					//openf: bang mo ta file in filesys.h
					{
						DEBUG('f',"mo file thanh cong");
						machine->WriteRegister(2, fileSystem->index-1);//tra ve id cua file
					} else 
					{
						DEBUG('f',"cannot open file");
						machine->WriteRegister(2, -1);
					};
					delete [] buf;
					break;
				}
				case SC_CloseFile:
				{
					int m_index = machine->ReadRegister(4);
					if (fileSystem->openf[m_index] == NULL) break;
					delete fileSystem->openf[m_index];
					fileSystem->openf[m_index] = NULL;
					break;
				}
				case SC_ReadFile:
				{
					int bufAddr = machine->ReadRegister(4);
					int NumBuf = machine->ReadRegister(5);
					int m_index = machine->ReadRegister(6);	
					int OldPos;
					int NewPos;
					char *buf = new char[NumBuf];
					int i = 0;
					// Check m_index
					if (m_index < 0 || m_index > 10)
					{
						machine->WriteRegister(2, -1);
						delete[] buf;
						break;
					}
					// check openf[m_index]
					if (fileSystem->openf[m_index] == NULL)
					{
						machine->WriteRegister(2, -1);
						delete[] buf;
						break;
					}
					OldPos = fileSystem->openf[m_index]->GetCurrentPos();
					buf = machine->User2System(bufAddr, NumBuf);
					if (fileSystem->openf[m_index]->type == 2)//stdin
					{

						int sz = gSynchConsole->Read(buf, NumBuf);

					
						machine->System2User(bufAddr, sz, buf);
						machine->WriteRegister(2, sz);
						break;
					}
					
					if ((fileSystem->openf[m_index]->Read(buf, NumBuf) ) > 0)
					{
						// Copy data from kernel to user space
					  NewPos = fileSystem->openf[m_index]->GetCurrentPos();
						machine->System2User(bufAddr, NewPos - OldPos +1, buf);
						machine->WriteRegister(2, NewPos - OldPos + 1);
					}
					else
					{
						machine->WriteRegister(2, -1);
						delete[] buf;
						break;
					}
					delete[] buf;
					break;
				}
				case SC_WriteFile:
				{
					int bufAddr = machine->ReadRegister(4);
					int NumBuf = machine->ReadRegister(5);
					int m_index =  machine->ReadRegister(6);
					int OldPos;
					int NewPos;
					char *buf = new char[NumBuf];
					// Check m_index
					if (m_index < 0 || m_index > 10)
					{
						machine->WriteRegister(2, -1);
						delete[] buf;
						break;
					}
					// check openf[m_index]
					if (fileSystem->openf[m_index] == NULL)
					{
						machine->WriteRegister(2, -1);
						delete[] buf;
						break;
					}
					OldPos = fileSystem->openf[m_index]->GetCurrentPos();
					
					// type phai bang '0' thi moi co the ghi
					buf = machine->User2System(bufAddr, NumBuf);
					if (fileSystem->openf[m_index]->type  == 0 || fileSystem->openf[m_index]->type == 3)// 3 la stdout
					{	
						if ((fileSystem->openf[m_index]->Write(buf, NumBuf)) > 0) 
						{
							// Copy data from kernel to user space
							printf("%s",buf);// in ra console ND file
							NewPos = fileSystem->openf[m_index]->GetCurrentPos();
							machine->WriteRegister(2, NewPos - OldPos + 1);
						}
						else if (fileSystem->openf[m_index]->type == 1);//only read type = 1
						{
							machine->WriteRegister(2, -1);
							delete[] buf;
							break;
						}
					}
					// xuat ra man hinh console
					if (fileSystem->openf[m_index]->type == 3)//stdout
					{
						int i = 0;
						printf("stdout mode\n");
						while (buf[i] != 0 && buf[i] != '\n')
						{
							gSynchConsole->Write(buf+i, 1);
							i++;
						}
						buf[i] = '\n';
						gSynchConsole->Write(buf+i,1);
						machine->WriteRegister(2, i-1);//tra ve so byte ghi
					}
					delete[] buf;
					break;
				}
				case SC_SeekFile:
				{
					int pos = machine->ReadRegister(4);
					int m_index = machine->ReadRegister(5);
					if (m_index < 0 || m_index > 10)
					{
						machine->WriteRegister(2, -1);
						break;
					}
					// check openf[m_index]
					if (fileSystem->openf[m_index] == NULL)
					{
						printf("seek fail \n");
						machine->WriteRegister(2, -1);
						break;
					}
						pos = (pos == -1) ? fileSystem->openf[m_index]->Length() : pos;//cuoi file khi pos = -1
					if (pos > fileSystem->openf[m_index]->Length() || pos < 0) {
						machine->WriteRegister(2, -1);
					} 
					else 
					{
						fileSystem->openf[m_index]->Seek(pos);
						machine->WriteRegister(2, pos);
					}
					break;
				}
			}
		machine->registers[PrevPCReg] = machine->registers[PCReg];	
									
		machine->registers[PCReg] = machine->registers[NextPCReg];
		machine->registers[NextPCReg] += 4;
		break;
	case  PageFaultException:    // No valid translation found
		printf("No valid translation found %d %d\n", which, type);
		ASSERT(FALSE);
		break;
	case  ReadOnlyException:     // Write attempted to page marked 
		printf("Write attempted tp page marked %d %d\n", which, type);
		ASSERT(FALSE);
		break;
	case  BusErrorException:     // Translation resulted in an 
		printf("Translaion resulted in an %d %d\n", which, type);
		ASSERT(FALSE);
		break;
	case  AddressErrorException: // Unaligned reference or one that
		printf("Unaligned reference or one that %d %d\n", which, type);
		ASSERT(FALSE);
		break;
	case  OverflowException:     // Integer overflow in add or sub.
		printf("Integer overflow in add or sub %d %d\n", which, type);
		ASSERT(FALSE);
		break;
	case  IllegalInstrException: // Unimplemented or reserved instr.
		printf("Unimplemented or reserved instr %d %d\n", which, type);
		ASSERT(FALSE);
		break;
		
		
	case NumExceptionTypes: 
		printf("NumExceptionTypes\n");
		ASSERT(FALSE);
		break;
	}
    //if ((which == SyscallException) && (type == SC_Halt)) {
	//DEBUG('a', "Shutdown, initiated by user program.\n");
   //	interrupt->Halt();
    //} else {
//	printf("Unexpected user mode exception %d %d\n", which, type);
//	ASSERT(FALSE);
  //  }
}
