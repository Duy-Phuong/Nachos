#include "copyright.h"
#include "syscall.h"

int main()
{
	
	int b = 0;
	int i = 0;
	char a;
	a = (char)b;
	PrintString("\t\tBANG MA ASCII\n");
	
	for(; i < 127; i++)
	{
		a++;
		b++;
		PrintInt(b);
		PrintChar(' ');
		PrintChar(' ');
		PrintChar(' ');
		PrintChar(a);
		PrintString("\n");
	}









Halt();
}
