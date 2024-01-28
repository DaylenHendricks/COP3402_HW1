//Homework 1: P-Machine
//Authors: Daylen Hendricks, Brandon Ramlagan
//COP 3402 Spring 2024
//Date

#include <stdio.h> //libraries

int PAS[500] = {0}; //initializing process address space to 0s

int base(int BP, int L) //Find base L levels down
{
    int arb = BP; //arb =  activation record base
    while(L>0) //find base L levels down
    {
        arb = pas(arb);
        L--;
    }
    return arb;
}
int main(){
    FILE* inFile = fopen("myfile.txt", "r"); //initialize file pointer & text input file in read mode
    
    
}
