#include "syscall.h"
#include "copyright.h"
#define LIMIT 255


int 
main(){
char a[LIMIT];
//int i = CreateFile("stdin");
OpenFileID open; 
char Content[255];


	PrintString("\t\tMOI BAN NHAP NOI DUNG:");
//ReadString(a,LIMIT); 

	open = OpenFile("stdin", 0);
	
	if (open==-1)
	{ 
		PrintString("Cannot open file\n");
	}
	else
	{
		//WriteFile(a, 255, open);
		SeekFile(0, open);
		ReadFile(Content, 255, open);
	PrintString("\t\t-----------------------------");
	PrintString("Noi dung khi ban doc tu file la: ");
	PrintString(Content);
		CloseFile(open);

	}


Halt();
}
