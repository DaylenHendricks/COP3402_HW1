//Homework 1: P-Machine
//Authors: Daylen Hendricks, Brandon Ramlagan
//COP 3402 Spring 2024
//Date

#include <stdio.h> //libraries

int PAS[500] = {0}; //initializing process address space to 0

int base(int BP, int L) //Find base L levels down function
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
    int count = 0, curVal, PC, BP, SP;
    FILE* inputFile;
    inputFile = fopen("text", "r"); //initialize file pointer & text input file in read mode
    while(fscanf(inputFile, "%d", &curVal) == 1)//loop through text and insert in PAS
    {
        PAS[count] = curVal;
        printf("%d", PAS[count]);
        count++;
    }
}
