//Homework 1: P-Machine
//Authors: Daylen Hendricks, Brandon Ramlagan
//COP 3402 Spring 2024
//Date

#include <stdio.h> //libraries

int pas[500] = {0}; //initializing process address space to 0

int base(int BP, int L) //Find base L levels down function
{
    int arb = BP; //arb =  activation record base
    while(L > 0) //find base L levels down
    {
        arb = pas[arb];
        L--;
    }
    return arb;
}


int main(int argc, char *fileName[]){
    printf("Start");//debug
    //curpc is indexing the instruction's values passed to the IR because pc increments after fetch but before execute
    int count = 0, flag = 1, curVal, pc = 0, curpc = 0, sp = 500, bp = sp - 1;
    FILE* inputFile;
    inputFile = fopen(fileName[1], "r"); //initialize file pointer & text input file in read mode
    printf("Begin File IO\n");//debug
    while(fscanf(inputFile, "%d", &curVal) == 1)//loop through text and insert in PAS
    {
        pas[count] = curVal;
        printf("%d", pas[count]);//checking insertion
        count++;
    }
    printf("Begin Fetch-Execute\n");
    printf("\tPC BP SP stack");
    while(flag == 1)//fetch loop
    {
        curpc = pc;//to keep track of index for current execution
        pc = pc + 3;//actual program counter
        printf("PC: %d\n", pc);
        printf("curpc: %d\n", curpc);
        switch(pas[curpc])//checking instruction type
        {

            case 1: //LIT 0,M
            {
                printf("LIT\n");
                pas[sp] = pas[curpc + 2];
                sp -= 1;
                break;
            }
            case 2: //RTN 0,M
            {
                switch(pas[curpc + 2] == 0)//math opr or RTN check
                {
                    case 0:
                    {
                    printf("RTN\n");
                    sp = bp + 1;
                    bp = pas[sp - 2];
                    pc = pas[sp - 3];
                    break;
                    }
                }
                
                break;
            }
            case 3: //LOD L,M
            {
                printf("LOD\n");
                sp -= 1;
                pas[sp] = pas[base(bp, pas[curpc + 1]) - pas[curpc + 2]];
                break;
            }
            case 4: //STO L<M
            {
                printf("STO\n");
                pas[base(bp, pas[curpc + 1]) - pas[curpc + 2]] = pas[sp];
                sp += 1;
                break;
            }
            case 5: //CAL L,M | Initializing new Activation Record
            {
                printf("CAL\n");
                pas[sp - 1] = base(bp, pas[curpc + 1]); //static link (SL)
                pas[sp - 2] = bp; //dynamic link (DL)
                pas[sp - 3] = pc; //return address (RA)
                bp = pas[sp - 1]; //base pointer points to static link
                pc = pas[curpc + 2]; //
                break;
            }
            case 6: //INC 0,M
            {
                printf("INC\n");
                sp -= pas[sp + 2];
                break;
            }
            case 7: //JMP 0,M
            {
                printf("JMP\n");
                pc = pas[curpc + 2];
                break;
            }
            case 8: //JPC 0,M
            {
                printf("JPC\n");
                if (pas[sp] == 00)
                {
                    pc = pas[curpc + 2];
                    sp += 1;
                };
                break;
            }
            case 9: //SYS (Need to include three subroutines)
            {
                printf("SYS: ");
                switch(pas[curpc + 2])
                {
                    case 1:
                    {
                        printf("1\n");
                        printf("%d", pas[sp]);
                        sp += 1;
                        break;
                    }
                    case 2:
                    {
                        printf("2\n");
                        sp =  sp - 1;
                        printf("Please Enter an Integer: ");
                        pas[sp] = getc(stdin);
                        break;
                    }
                    case 3:
                    {
                        printf("3\n");
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
        printf("%d", &pas[i]); //checking pas[] values
    }
}
