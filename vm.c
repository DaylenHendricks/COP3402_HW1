//Homework 1: P-Machine
//Authors: Daylen Hendricks, Brandon Ramlagan
//COP 3402 Spring 2024
//Date

#include <stdio.h> //libraries
#include <stdlib.h>

int pas[500] = {0}; //initializing process address space to 0
int stack[500] = {0};
int counter = 500;

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
    int count = 0;//variable for file input tracking
    int flag = 1;//EOP flag
    int curVal; //current value in file input
    int pc = 0;//program counter
    int curpc = 0;//program counter for execution(for how we wrote it, the ISA statements are the same)
    int sp = 500; //stack pointer
    int bp = sp - 1; //base pointer
    int bpArr[10] = {499};//base pointer array for printing functionality
    int bpCount = 0;//count number of bp changes for printing functionality
    FILE* inputFile;
    inputFile = fopen(fileName[1], "r"); //initialize file pointer & text input file in read mode
    printf("Begin File IO\n");//debug
    while(fscanf(inputFile, "%d", &curVal) == 1)//loop through text and insert in PAS
    {
        pas[count] = curVal;
        printf("%d", pas[count]);//checking insertion
        count++;
    }
    printf("\nBegin Fetch-Execute\n");
    printf("\t\t PC BP SP  \tstack\n");
    printf("Initial values:  %d %d %d\n", pc, bp, sp);
    while(flag == 1)//fetch loop
    {
        curpc = pc;//to keep track of index for current execution
        pc = pc + 3;//actual program counter
        //printf("PC: %d\n", pc);
        //printf("curpc: %d\n", curpc);
        //printf("Bottom 3 of stack: %d %d %d %d\n", pas[sp+3], pas[sp+2], pas[sp+1], pas[sp]);
        switch(pas[curpc])//checking instruction type

        {

            case 1: //LIT 0,M
            {
                //printf("LIT %d %d\n", pas[curpc + 1], pas[curpc + 2]);
                sp -= 1;
                pas[sp] = pas[curpc + 2];
                printf("LIT %d %d\t\t %d %d %d\t", pas[curpc + 1], pas[curpc + 2], pc, bp, sp);
                break;
            }
            case 2: //OPR 0,M
            {
                //printf("OPR- %d %d\n", pas[curpc + 1], pas[curpc + 2]);
                switch(pas[curpc + 2])//math opr or RTN check
                {
                    case 0://RTN
                    {
                    //printf("RTN %d %d\n", pas[curpc + 1], pas[curpc + 2]);
                    sp = bp + 1;
                    bp = pas[sp - 2];
                    pc = pas[sp - 3];
                    printf("RTN %d %d\t\t %d %d %d\t", pas[curpc + 1], pas[curpc + 2], pc, bp, sp);
                    bpCount--;// incrementing the number of activation records for printing functionality
                    break;
                    }
                    case 1://ADD
                    {
                        //printf("ADD %d %d\n", pas[curpc + 1], pas[curpc + 2]);
                        pas[sp + 1] = pas[sp + 1] + pas[sp];
                        sp += 1;
                        printf("ADD %d %d\t\t %d %d %d\t", pas[curpc + 1], pas[curpc + 2], pc, bp, sp);
                        break;
                    }
                    case 2://SUB
                    {
                        //printf("SUB %d %d\n", pas[curpc + 1], pas[curpc + 2]);
                        pas[sp + 1] = pas[sp + 1] - pas[sp];
                        sp += 1;
                        printf("SUB %d %d\t\t %d %d %d\t", pas[curpc + 1], pas[curpc + 2], pc, bp, sp);
                        break;
                    }
                    case 3://MUL
                    {
                        //printf("MUL %d %d\n", pas[curpc + 1], pas[curpc + 2]);
                        pas[sp + 1] = pas[sp + 1] * pas[sp];
                        sp += 1;
                        printf("MUL %d %d\t\t %d %d %d\t", pas[curpc + 1], pas[curpc + 2], pc, bp, sp);
                        break;
                    }
                    case 4://DIV
                    {
                        //printf("DIV %d %d\n", pas[curpc + 1], pas[curpc + 2]);
                        pas[sp + 1] = pas[sp +1] / pas[sp];
                        sp += 1;
                        printf("DIV %d %d\t\t %d %d %d\t", pas[curpc + 1], pas[curpc + 2], pc, bp, sp);
                        break;
                    }
                    case 5://EQL
                    {
                        //printf("EQL %d %d\n", pas[curpc + 1], pas[curpc + 2]);
                        pas[sp +1] = pas[sp + 1] == pas[sp];
                        sp += 1;
                        printf("EQL %d %d\t\t %d %d %d\t", pas[curpc + 1], pas[curpc + 2], pc, bp, sp);
                        break;
                    }
                    case 6://NEQ
                    {
                        //printf("NEQ %d %d\n", pas[curpc + 1], pas[curpc + 2]);
                        pas[sp + 1] = pas[sp + 1] != pas[sp];
                        sp += 1;
                        printf("NEQ %d %d\t\t %d %d %d\t", pas[curpc + 1], pas[curpc + 2], pc, bp, sp);
                        break;
                    }
                    case 7://LSS
                    {
                        //printf("LSS %d %d\n", pas[curpc + 1], pas[curpc + 2]);
                        pas[sp + 1] = pas[sp + 1] < pas[sp];
                        sp += 1;
                        printf("LSS %d %d\t\t %d %d %d\t", pas[curpc + 1], pas[curpc + 2], pc, bp, sp);
                        break;
                    }
                    case 8://LEQ
                    {
                        //printf("LEQ %d %d\n", pas[curpc + 1], pas[curpc + 2]);
                        pas[sp + 1] = pas[sp + 1] <= pas[sp];
                        sp += 1;
                        printf("LEQ %d %d\t\t %d %d %d\t", pas[curpc + 1], pas[curpc + 2], pc, bp, sp);
                        break;
                    }
                    case 9://GTR
                    {
                        //printf("GTR %d %d\n", pas[curpc + 1], pas[curpc + 2]);
                        pas[sp + 1] = pas[sp + 1] > pas[sp];
                        sp += 1;
                        printf("GTR %d %d\t\t %d %d %d\t", pas[curpc + 1], pas[curpc + 2], pc, bp, sp);
                        break;
                    }
                    case 10://GEQ
                    {
                        //printf("GEQ %d %d\n", pas[curpc + 1], pas[curpc + 2]);
                        pas[sp + 1] = pas[sp + 1] >= pas[sp];
                        sp += 1;
                        printf("GEQ %d %d\t\t %d %d %d\t", pas[curpc + 1], pas[curpc + 2], pc, bp, sp);
                        break;
                    }
                    case 11://ODD
                    {
                        //printf("ODD %d %d\n", pas[curpc + 1], pas[curpc + 2]);
                        pas[sp] =  pas[sp] % 2;
                        printf("ODD %d %d\t\t %d %d %d\t", pas[curpc + 1], pas[curpc + 2], pc, bp, sp);
                        break;
                    }
                }
                
                break;
            }
            case 3: //LOD L,M
            {
                //printf("LOD %d %d\n", pas[curpc + 1], pas[curpc + 2]);
                sp -= 1;
                pas[sp] = pas[base(bp, pas[curpc + 1]) - pas[curpc + 2]];
                printf("LOD %d %d\t\t %d %d %d\t", pas[curpc + 1], pas[curpc + 2], pc, bp, sp);
                break;
            }
            case 4: //STO L<M
            {
                //printf("STO %d %d\n", pas[curpc + 1], pas[curpc + 2]);
                pas[base(bp, pas[curpc + 1]) - pas[curpc + 2]] = pas[sp];
                sp += 1;
                printf("STO %d %d\t\t %d %d %d\t", pas[curpc + 1], pas[curpc + 2], pc, bp, sp);
                break;
            }
            case 5: //CAL L,M | Initializing new Activation Record
            {
                //printf("CAL %d %d\n", pas[curpc + 1], pas[curpc + 2]);
                pas[sp - 1] = base(bp, pas[curpc + 1]); //static link (SL)
                pas[sp - 2] = bp; //dynamic link (DL)
                pas[sp - 3] = pc; //return address (RA)
                bp = sp - 1; //base pointer points to static link
                pc = pas[curpc + 2]; //M value
                printf("CAL %d %d\t\t %d %d %d\t", pas[curpc + 1], pas[curpc + 2], pc, bp, sp);
                bpCount++;//incrementing number of activation records / bp changes for printing functionality
                bpArr[bpCount] = bp;//storing the bp value for printing function
                break;
            }
            case 6: //INC 0,M
            {
                sp -= pas[curpc + 2];
                printf("INC %d %d\t\t %d %d %d\t", pas[curpc + 1], pas[curpc + 2], pc, bp, sp);

                /*
                for(int i = 0; i <= 500-sp; i++)
                {
                    stack[counter] = pas[counter];
                    printf("%d ", stack[counter]);
                    counter--;
                }
                printf("\n");
                */
               while(counter >= sp)
               {
                    stack[counter] = pas[counter];
                    //printf("%d ", stack[counter]);
                    counter--;
               }
               counter = 500;
               //printf("");
                break;
            }
            case 7: //JMP 0,M
            {
                printf("JMP %d %d\t %d %d %d\t", pas[curpc + 1], pas[curpc + 2], pas[curpc + 2], bp, sp);
                pc = pas[curpc + 2];
                //printf(" %d\n", pc);
                break;
            }
            case 8: //JPC 0,M
            {
                //printf("JPC %d %d\n", pas[curpc + 1], pas[curpc + 2]);
                if (pas[sp] == 0)
                {
                   // printf(" hi%dhi", pas[sp]);
                    pc = pas[curpc + 2];
                    sp += 1;
                }
                else
                {
                    sp += 1;
                }
                //printf(" hi%dhi", pas[sp]);
                printf("JPC %d %d\t %d %d %d\t", pas[curpc + 1], pas[curpc + 2], pc, bp, sp);
                break;
            }
            case 9: //SYS (Need to include three subroutines)
            {
                //printf("SYS: ");
                switch(pas[curpc + 2])
                {
                    case 1:
                    {
                        //printf("1\n");
                        printf("Output result is: %d\n", pas[sp]);
                        sp += 1;
                        printf("SOU %d %d\t %d %d %d\n", pas[curpc + 1], pas[curpc + 2], pc, bp, sp);
                        break;
                    }
                    case 2:
                    {
                        //printf("2\n");
                        sp =  sp - 1;
                        printf("Please Enter an Integer: ");
                        fscanf(stdin, "%d", &pas[sp]);
                        //printf("SOU %d %d\t %d %d %d\n", pas[curpc + 1], pas[curpc + 2], pc, bp, sp);
                        break;
                    }
                    case 3:
                    {
                        //printf("3\n");
                        flag = 0;
                        printf("EOP %d %d\t %d %d %d\n", pas[curpc + 1], pas[curpc + 2], pc, bp, sp);
                        break;
                    }
                }
                break;
            }
        }
        for(int i = 0; i <= (499 - sp); i++)
        {
            if(bpCount != 0)
            {
                for(int tempCount = 1; tempCount <= bpCount; tempCount++)
                {
                    if(499 - i == bpArr[tempCount])
                    {
                        printf("| ");
                    }
                }
            }
            printf("%d ", pas[499 - i]);
        }
        printf("\n");
    }

    
}
