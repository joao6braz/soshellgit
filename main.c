#include "shell.h"

char prompt[100];

int main ()
{
  int numargs;
  int len;
  char linha[1024];/* um comando */
  char *args[64];/* com um maximo de 64 argumentos */

  strcpy (prompt, "SOSHELL: Introduza um comando : prompt>");
  while (1)
  {
    printf ("%s", prompt);
    if (fgets (linha, 1023, stdin) == NULL) //if end of file exit
    {
      printf ("\n");
      exit (0);
    }
    len = strlen (linha);

    if (1 == len)
      continue;/* linha é apenas \n */  //é so um enter logo continue

    if (linha[len - 1] == '\n')
      linha[len - 1] = '\0';		//remover o \n e mudar para \0 para fzr o parse das linhas
    numargs = parse (linha, args);/* particiona a string em argumentos */

    if (!builtin (args))
      execute (numargs, args);/* executa o comando */
    }


  return 0;
}

int builtin (char **args)
{
  if( 0==strcmp(args[0], "quemsoueu") ){
    system("id");
    return 1 ; //comando embutido
  }

  if( strlen(args[0])>4 && 0==strncmp(args[0], "PS1=",4) ){
    strcpy(prompt,args[0]+4);
    return 1 ; //comando embutido
  }

  if (strcmp (args[0], "obterinfo") == 0)
  {
    printf("SO_Shell 2022 versão 1.0\n");
    return 1; //comando embutido
  }

  if (strcmp (args[0], "sair") == 0)
  {
    exit (0);
    return 1;
  }

  if (strncmp (args[0], "42", 2) == 0)
  {
    printf ("42 is the answer to life the universe and everything\n");
    return 1;/* funcionalidade embutida */
  }

  if (0 == strcmp(args[0], "cd")) {
    
    int err;
    if ( (NULL == args[1]) || ( strcmp(args[1] ,"~") == 0) )
      err = chdir(getenv("HOME") ) ;
    else
    {
      err = chdir( args[1] );
      if (err<0) 
        perror (args[1]);
    }

    return 1 ; //comando embutido
  }

  if( 0==strcmp(args[0], "socp") )
  {
    socp( args[1], args[2] );
    return 1 ; //comando embutido
  }

  if ( 0 == strcmp(args[0], "calc") && args[1]!=NULL && args[2]!=NULL && args[3]!=NULL && args[4]==NULL) {
    calc( args[1], args[2], args[3]);
    return 1 ; //comando embutido
  }




  /* IMPORTANTE : 
   Devolver 0 para indicar que não existe comando embutido e que
   será executado usando exec() na função execute.c
  */
  return 0;
}
