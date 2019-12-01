#include "halfsize.h"
#include "halfsize.cpp"

int main()
{
    tga p;
    // unsigned char a='10';
    // printf("0x20 is char:%c and int:%d.",a,a);
    // return 0;
    // int i;
    // char q;
    // q = '2';
    // std::cout<<"\nQ: "<<q<<"\n";
	p.resizeTGA("original.tga","half.tga");
    return 0;
}