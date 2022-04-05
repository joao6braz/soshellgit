#include "shell.h"
#define BUFFSIZE 128

void socp(char *fonte, char *destino)
{
    int fdIn = open(fonte, O_RDONLY | O_CREAT, 0666);
    if (fdIn < 0)
        perror("Error ao abrir ficheiro! \n");

    int fdOut = open(destino,O_RDWR | O_CREAT | O_SYNC, 0666);
    if (fdOut < 0)
        perror("Erro no ficheiro de saida! \n");
    
    ioCopy( fdIn, fdOut);
}


void ioCopy (int IN, int OUT) //no error reporting
{
    int n;
    char buf[BUFFSIZE];
    while ( ( n = read (IN, buf, BUFFSIZE)) > 0)
    {
        if (write (OUT, buf, n) != n)
            perror("Erro de escrita!\n");
    }
    if (n < 0)
        perror("Erro de leitura!\n");

}