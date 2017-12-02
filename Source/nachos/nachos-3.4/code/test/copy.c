#include "syscall.h"
#include "copyright.h"
#define LIMIT 255


int 
main(){
OpenFileID srcId;
	OpenFileID dstId;
	char source[255], dest[255];
	int filesz,srcsz, i;
	char c;
	char Content[255];

	PrintString("\t\tNHAP TEN FILE NGUON:");
	ReadString(source, 255);
	PrintString("\t\tNHAP TEN FILE DICH:");
	ReadString(dest, 255);


	srcId = OpenFile(source, 1);
	CreateFile(dest);
	dstId = OpenFile(dest, 0);
	if (srcId == -1 || dstId == -1)
	{
		
		PrintString("Cannot open file \n");
		return 0;
	}
	filesz = SeekFile(-1, srcId);
	SeekFile(0, srcId);
	SeekFile(0, dstId);
	for (i = 0; i < filesz; ++i)
	{
		ReadFile(&c, 1, srcId);
		WriteFile(&c, 1, dstId);
	}
PrintString("\t\t-----------------------------");
	PrintString("\t\tNOI DUNG FILE NGUON LA:");
	SeekFile(0, srcId);
	ReadFile(Content, 255, srcId);

	PrintString(Content);

PrintString("\t\t-----------------------------");
	PrintString("\t\tNOI DUNG FILE DICH LA:");
	SeekFile(0, dstId);
	ReadFile(Content, 255, dstId);

	//PrintString(Content);
	CloseFile(srcId);
	CloseFile(dstId);
Halt();
}
