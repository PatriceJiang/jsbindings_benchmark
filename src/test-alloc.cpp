#include <stdio.h>
#include <iostream>


int main(int argc, char **argv)
{
    int start = 1000;
    while(true)
    {
        std::cout << " alloc :"<< start << std::endl;
        char *p =(char *) malloc(start);
        start*=2;
        if(p){
            free(p);
        }else{
            break;
        }
    }
    return 0;
}