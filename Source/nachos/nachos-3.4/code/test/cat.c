#include "syscall.h"
#include "copyright.h"
#define LIMIT 255


int 
main(){
char filename[LIMIT];
int i;
OpenFileID open; 
char Content[255];
char a[LIMIT];

PrintString("\t\tMOI BAN NHAP TEN FILE:");
ReadString(filename, LIMIT); 


/*i = CreateFile(filename);

PrintString("\t\tMOI BAN NHAP NOI DUNG VAO FILE:");
ReadString(a,LIMIT); 
if(i == -1)
{
	PrintString("TAO FILE THAT BAI");
}
else
{*/
	open = OpenFile(filename, 0);
	
	//PrintString("");
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
//}

Halt();
}
