#include "copyright.h"
#include "syscall.h"

int main(){

int i, j, tmp;
int a;
int arr[100];
do{
PrintString("\t\t-------Moi ban nhap so phan tu( > 0 va <= 100):-------- ");

a = ReadInt();
if(a <= 0 || a > 100)
{
	PrintString("\t\tMoi ban nhap lai so phan tu( > 0 va <= 100)!");

}
}while(a <= 0 || a > 100);
	PrintString("\t\t-------Moi ban nhap cac phan tu:------- ");
	for(i = 0; i< a; i++)
	{
		arr[i] = ReadInt();
	}
	//sort
	for(i = 0; i < a-1; i++)
	{
		for(j=a-1; j>i;j--)
		{
			if(arr[j] < arr[j-1])
			{
				      tmp = arr[j];
				      arr[j] = arr[j - 1];
				      arr[j - 1] = tmp;
			}
		}
	}
	PrintString("\t\t-------Xuat mang da duoc sap xep theo bubblesort: -------");
	for(i = 0; i< a; i++)
	{
		PrintInt(arr[i]);
		PrintString("\n");
	}



Halt();
}
