#include "syscall.h"
#include "copyright.h"
#define LIMIT 255


int 
main(){

	char c;
	OpenFileID srcId;
	OpenFileID dstId;
	char source[255], dest[255];
	int srcSz, srcPos;
	char Content[255];

	PrintString("\t\tNHAP TEN FILE NGUON:");
	ReadString(source, 255);
	PrintString("\t\tNHAP TEN FILE DICH:");
	ReadString(dest, 255);

	srcId = OpenFile(source, 1);//chi doc
	CreateFile(dest);
	dstId = OpenFile(dest, 0);// doc va ghi
	if (srcId == -1 || dstId == -1)
	{

		PrintString("Cannot open file \n");
		return 0;
	}
	/* Seek source file to end of file */
	srcSz = SeekFile(-1, srcId);
	/* Seek destination file to begin of file */
	SeekFile(0, dstId);
	 
	while (srcSz>=0)
	{	
		SeekFile(srcSz, srcId);
		ReadFile(&c, 1, srcId);
		WriteFile(&c, 1, dstId);
		srcSz --;
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
	CloseFile(srcId);
	CloseFile(dstId);

Halt();
}
