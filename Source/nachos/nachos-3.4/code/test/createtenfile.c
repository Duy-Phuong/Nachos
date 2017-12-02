#include "syscall.h"
#include "copyright.h"
#define LIMIT 1000

int main(){
int id;
char a[LIMIT];
int i; 
for(i = 0; i < 10; i++)
{
	PrintString("\t\tMoi ban nhap ten file");
	ReadString(a,LIMIT); 
	id = CreateFile(a);
	if(id == -1)
	{
		PrintString("TAO FILE THAT BAI");
	}
	else
	{
		PrintString("\t\tTAO FILE THANH CONG");
	
	}
		PrintString("");
}
Halt();
}
