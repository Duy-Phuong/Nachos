#include "copyright.h"
#include "syscall.h"
#define LIMIT 1000
int 
main(){
char a[LIMIT];
ReadString(a,LIMIT); 
PrintString(a);



Halt();
}
