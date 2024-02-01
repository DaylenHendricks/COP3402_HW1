//Homework 1: P-Machine
//Authors: Daylen Hendricks, Brandon Ramlagan
//COP 3402 Spring 2024
//Date

#include <stdio.h> //libraries

int pas[500] = {0}; //initializing process address space to 0

int base(int BP, int L) //Find base L levels down function
{
    int arb = BP; //arb =  activation record base
    while(L>0) //find base L levels down
    {
        arb = pas[arb];
        L--;
    }
    return arb;
}


int main(){
    printf("Start");//debug
    //curpc is indexing the instruction's values passed to the IR because pc increments after fetch but before execute
    int count = 0, flag = 1, curVal, pc = 0, curpc = 0, sp = 500, bp = sp - 1;
    FILE* inputFile;
    inputFile = fopen("text", "r"); //initialize file pointer & text input file in read mode
    printf("Begin File IO");//debug
    while(fscanf(inputFile, "%d", &curVal) == 1)//loop through text and insert in PAS
    {
        pas[count] = curVal;
        printf("%d", pas[count]);//checking insertion
        count++;
    }
    printf("Begin Fetch-Execute");
    while(flag == 1)//fetch loop
    {
        curpc = pc;//to keep track of index for current execution
        pc += 3;//actual program counter
        switch(pas[pc])//checking instruction type
        {

            case 1: //LIT 0,M
            {
                pas[sp] = pas[curpc + 2];
                sp -= 1;
                break;
            }
            case 2: //RTN 0,M
            {
                sp = bp + 1;
                bp = pas[sp - 2];
                pc = pas[sp - 3];
                break;
            }
            case 3: //LOD L,M
            {
                sp -= 1;
                pas[sp] = pas[base(bp, pas[curpc + 1]) - pas[curpc + 2]];
                break;
            }
            case 4: //STO L<M
            {
                pas[base(bp, pas[curpc + 1]) - pas[curpc + 2]] = pas[sp];
                sp += 1;
                break;
            }
            case 5: //CAL L,M | Initializing new Activation Record
            {
                pas[sp - 1] = base(bp, pas[curpc + 1]); //static link (SL)
                pas[sp - 2] = bp; //dynamic link (DL)
                pas[sp - 3] = pc; //return address (RA)
                bp = pas[sp - 1]; //base pointer points to static link
                pc = pas[curpc + 2]; //
                break;
            }
            case 6: //INC 0,M
            {
                sp -= pas[sp + 2];
                break;
            }
            case 7: //JMP 0,M
            {
                pc = pas[sp + 2];
                break;
            }
            case 8: //JPC 0,M
            {
                if (pas[sp] == 00)
                {
                    pc = pas[curpc + 2];
                    sp += 1;
                };
                break;
            }
            case 9: //SYS (Need to include three subroutines)
            {
                switch(pas[curpc + 2])
                {
                    case 1:
                    {
                        printf("%d", pas[sp]);
                        sp += 1;
                        break;
                    }
                    case 2:
                    {
                        sp =  sp - 1;
                        printf("Please Enter an Integer: ");
                        pas[sp] = getc(stdin);
                        break;
                    }
                    case 3:
                    {
                        flag = 0;
                        break;
                    }
                }
                break;
            }
        }
    }
    int i;
    while(i = 0, i < 500, i++)
    {
        printf(pas[i]); //checking pas[]
    }
}
