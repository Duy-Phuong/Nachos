#include "syscall.h"
#include "copyright.h"

int 
main(){
int i = CreateFile("demo.txt");
OpenFileID open; 
	char Content[255];
int seek;
if(i == -1)
{
	PrintString("TAO FILE THAT BAI");
}
else
{
	PrintString("\t\tTAO FILE THANH CONG");
	open = OpenFile("demo.txt", 0);
	PrintString("OpenFileID la: ");
	PrintInt(open);
	PrintString("");
	if (open==-1)
	{ 
		PrintString("Cannot open file\n");
	}
	else
	{
		WriteFile("noi dung trong file", 19, open);
		seek = SeekFile(0, open);
		ReadFile(Content, 19, open);
	PrintString("\t\t-----------------------------");
	PrintString("Noi dung khi ban doc tu file la: ");
	PrintString(Content);
//PrintString("seek"); PrintInt(seek);
		CloseFile(open);
	PrintString("\t\tDONG FILE THANH CONG");
	}
}

Halt();
}
