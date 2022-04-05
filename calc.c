#include "shell.h"

void calc(char *x, char *op, char *y)
{
    float val1 = atof(x);
    float val2 = atof(y);
    float result;

    switch (*op)
    {
        case '+':
            result = val1 + val2;
            break;

        case '*':
            result = val1 * val2;
            break;

        case '-':
            result = val1 - val2;
            break;

        case '/':
            if(val2==0)
                printf("Division by zero\n");
            else
                printf("&f\n", val1/val2);
            break;

        case '^':
            result = pow(val1,val2);
            break; 

    }

    if(*op!='/') //we already printed in this case
        printf("%f\n",result);
}


int isjpg(int fileDescriptor) //esboço da função
{
    unsigned char b[4];
    read(fileDescriptor,b,4);
    
    //voltar ao inicio do ficheiro com lseek
    if ( b[0]==0xff && b[1]==0xd8 && b[2]==0xff && b[3]==0xe0)
        return 1;
    return 0;
}