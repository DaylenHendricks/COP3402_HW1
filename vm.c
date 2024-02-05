//Homework 1: P-Machine
//Authors: Daylen Hendricks, Brandon Ramlagan
//COP 3402 Spring 2024
//Date 2/2/2024

#include <stdio.h> //libraries
#include <stdlib.h>

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
typedef struct instructionRegister //struct to store the values of the instruction register
{
    int OP;
    int L;
    int M;
}instructionRegister;


int main(int argc, char *fileName[]){
    int count = 0;//variable for file input tracking
    int flag = 1;//EOP flag
    int curVal; //current value in file input
    int pc = 0;//program counter
    int sp = 500; //stack pointer
    int bp = sp - 1; //base pointer
    int bpArr[10] = {499};//base pointer array for printing functionality
    int bpCount = 0;//count number of bp changes for printing functionality 
    instructionRegister IR;
    FILE* inputFile = fopen(fileName[1], "r"); //initialize file pointer & text input file in read mode
    while(fscanf(inputFile, "%d", &curVal) == 1)//loop through text and insert in PAS
    {
        pas[count] = curVal;
        count++;
    }
    printf(" \t\t PC BP SP  \tstack\n"); //Headers for the output file
    printf("Initial values:  %d %d %d\n", pc, bp, sp); 
    while(flag == 1)//fetch loop
    {
        IR.OP = pc;//tracks the OP component in IR register
        IR.M = pc + 2;//tracks the M component in IR register
        IR.L = pc + 1;//tracks the L component in IR register
        pc = pc + 3;//actual program counter
        switch(pas[IR.OP])//checking instruction type

        {

            case 1: //LIT 0,M
            {
                sp -= 1;
                pas[sp] = pas[IR.M];
                printf("LIT %d %d\t\t %d %d %d\t", pas[IR.L], pas[IR.M], pc, bp, sp);
                break;
            }
            case 2: //OPR 0,M
            {
                switch(pas[IR.M])//math opr or RTN check
                {
                    case 0://RTN
                    {
                    sp = bp + 1;
                    bp = pas[sp - 2];
                    pc = pas[sp - 3];
                    printf("RTN %d %d\t\t %d %d %d\t", pas[IR.L], pas[IR.M], pc, bp, sp);
                    bpCount--;
                    break;
                    }
                    case 1://ADD
                    {
                        pas[sp + 1] = pas[sp + 1] + pas[sp];
                        sp += 1;
                        printf("ADD %d %d\t\t %d %d %d\t", pas[IR.L], pas[IR.M], pc, bp, sp);
                        break;
                    }
                    case 2://SUB
                    {
                        pas[sp + 1] = pas[sp + 1] - pas[sp];
                        sp += 1;
                        printf("SUB %d %d\t\t %d %d %d\t", pas[IR.L], pas[IR.M], pc, bp, sp);
                        break;
                    }
                    case 3://MUL
                    {
                        pas[sp + 1] = pas[sp + 1] * pas[sp];
                        sp += 1;
                        printf("MUL %d %d\t\t %d %d %d\t", pas[IR.L], pas[IR.M], pc, bp, sp);
                        break;
                    }
                    case 4://DIV
                    {
                        pas[sp + 1] = pas[sp +1] / pas[sp];
                        sp += 1;
                        printf("DIV %d %d\t\t %d %d %d\t", pas[IR.L], pas[IR.M], pc, bp, sp);
                        break;
                    }
                    case 5://EQL
                    {
                        pas[sp +1] = pas[sp + 1] == pas[sp];
                        sp += 1;
                        printf("EQL %d %d\t\t %d %d %d\t", pas[IR.L], pas[IR.M], pc, bp, sp);
                        break;
                    }
                    case 6://NEQ
                    {
                        pas[sp + 1] = pas[sp + 1] != pas[sp];
                        sp += 1;
                        printf("NEQ %d %d\t\t %d %d %d\t", pas[IR.L], pas[IR.M], pc, bp, sp);
                        break;
                    }
                    case 7://LSS
                    {
                        pas[sp + 1] = pas[sp + 1] < pas[sp];
                        sp += 1;
                        printf("LSS %d %d\t\t %d %d %d\t", pas[IR.L], pas[IR.M], pc, bp, sp);
                        break;
                    }
                    case 8://LEQ
                    {
                        pas[sp + 1] = pas[sp + 1] <= pas[sp];
                        sp += 1;
                        printf("LEQ %d %d\t\t %d %d %d\t", pas[IR.L], pas[IR.M], pc, bp, sp);
                        break;
                    }
                    case 9://GTR
                    {
                        pas[sp + 1] = pas[sp + 1] > pas[sp];
                        sp += 1;
                        printf("GTR %d %d\t\t %d %d %d\t", pas[IR.L], pas[IR.M], pc, bp, sp);
                        break;
                    }
                    case 10://GEQ
                    {
                        pas[sp + 1] = pas[sp + 1] >= pas[sp];
                        sp += 1;
                        printf("GEQ %d %d\t\t %d %d %d\t", pas[IR.L], pas[IR.M], pc, bp, sp);
                        break;
                    }
                    case 11://ODD
                    {
                        pas[sp] =  pas[sp] % 2;
                        printf("ODD %d %d\t\t %d %d %d\t", pas[IR.L], pas[IR.M], pc, bp, sp);
                        break;
                    }
                }
                
                break;
            }
            case 3: //LOD L,M
            {
                sp -= 1;
                pas[sp] = pas[base(bp, pas[IR.L]) - pas[IR.M]];
                printf("LOD %d %d\t\t %d %d %d\t", pas[IR.L], pas[IR.M], pc, bp, sp);
                break;
            }
            case 4: //STO L<M
            {
                pas[base(bp, pas[IR.L]) - pas[IR.M]] = pas[sp];
                sp += 1;
                printf("STO %d %d\t\t %d %d %d\t", pas[IR.L], pas[IR.M], pc, bp, sp);
                break;
            }
            case 5: //CAL L,M | Initializing new Activation Record
            {
                pas[sp - 1] = base(bp, pas[IR.L]); //static link (SL)
                pas[sp - 2] = bp; //dynamic link (DL)
                pas[sp - 3] = pc; //return address (RA)
                bp = sp - 1; //base pointer points to static link
                pc = pas[IR.M]; //M value
                printf("CAL %d %d\t\t %d %d %d\t", pas[IR.L], pas[IR.M], pc, bp, sp);
                bpCount++;
                bpArr[bpCount] = bp;
                break;
            }
            case 6: //INC 0,M
            {
                sp -= pas[IR.M];
                printf("INC %d %d\t\t %d %d %d\t", pas[IR.L], pas[IR.M], pc, bp, sp);
                break;
            }
            case 7: //JMP 0,M
            {
                printf("JMP %d %d\t %d %d %d\t", pas[IR.L], pas[IR.M], pas[IR.M], bp, sp);
                pc = pas[IR.M];
                break;
            }
            case 8: //JPC 0,M
            {
                if (pas[sp] == 0)
                {
                    pc = pas[IR.M];
                    sp += 1;
                }
                else
                {
                    sp += 1;
                }
                printf("JPC %d %d\t %d %d %d\t", pas[IR.L], pas[IR.M], pc, bp, sp);
                break;
            }
            case 9: //SYS (Need to include three subroutines)
            {
                switch(pas[IR.M])
                {
                    case 1:
                    {
                        printf("Output result is: %d\n", pas[sp]);
                        sp += 1;
                        printf("SOU %d %d\t %d %d %d\t", pas[IR.L], pas[IR.M], pc, bp, sp);
                        break;
                    }
                    case 2:
                    {
                        sp =  sp - 1;
                        printf("Please Enter an Integer: ");
                        fscanf(stdin, "%d", &pas[sp]);
                        break;
                    }
                    case 3:
                    {
                        flag = 0;
                        printf("EOP %d %d\t %d %d %d\t", pas[IR.L], pas[IR.M], pc, bp, sp);
                        break;
                    }
                }
                break;
            }
        }
        //loop for printing
        for(int i = 0; i <= (499 - sp); i++)//the range of the print func
        {
            if(bpCount != 0)//checking if a new AR has been created
            {
                for(int tempCount = 1; tempCount <= bpCount; tempCount++)//^if so, then check the bp values for the delimiter
                {
                    if(499 - i == bpArr[tempCount])//if the index of the next print is the same as one of the AR bp values, print the vertical bar
                    {
                        printf("| ");
                    }
                }
            }
            printf("%d ", pas[499 - i]);//then print the value
        }
        printf("\n");//newline for spacing
    }
}
