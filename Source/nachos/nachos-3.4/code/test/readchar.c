#include "copyright.h"
#include "syscall.h"

int
main()
{
char c = ReadChar();
PrintChar(c);

Halt();
}
