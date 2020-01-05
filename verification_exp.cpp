#include <stdio.h>
#include <stdlib.h> 
#include <string.h>


int CorrectExpression( char* expr )
{
   char symbol[21] = "0123456789.eE()*/%+-"; /* il y a 20 symboles autorisés */
   int i, j, trouve = 0, brackets = 0, len = strlen(expr);

   /** Verification Lexicale:**/

   for( i=0; i < len; i++ )
   {
      trouve = 0;

      /* Verifier si le expre[i] apartiens à la liste des symboles autorisé */
      for( j=0; j < 20; j++ )
      {
         if( expr[i] == symbol[j] )
         {
            trouve = 1;
            break;
         }
      }

      /* s'il ne se trouve pas dans la liste des symboles autorisé : */
      if( ! trouve )
      {
         printf("Erreur Lexicale: caractere non autoriser.\n");
         return 0;   /* Expression Incorrecte */
      }
   }

   /** Verification Syntaxique:**/

   /* Verifier si le nbr de ')' est egale au nbr de '(' */
   for( i=0; i < len; i++ )
   {
      if( expr[i] == '(' )
         brackets++;
      else if( expr[i] == ')' )
         brackets--;
   }

   if( brackets > 0 )
   {
      printf("Il manque %d caractere ')' dans l'expression.\n", brackets);
      return 0;
   }
   else if( brackets < 0 )
   {
      printf("Il manque %d caractere '(' dans l'expression.\n", (-1) * brackets);
      return 0;
   }

   /* Verification de l'ordre des caracteres: */
   for( i=0; i < len; i++ )
   {
      /* pour les caracteres + - * / % */
      if( expr[i] == '+' || expr[i] == '/' || expr[i] == '*' ||
             expr[i] == '%' || expr[i] == '-' )
      {
         /* si l'operateur ce trouve tout en debut ou en fin de l'expression: */
         if( i == len-1 )
         {
            printf("Erreur Syntaxique: presence de caractere(s) mal placer.\n");
            return 0;   /* Expression Incorrecte */
         }
         else if( i == 0 )
                {
                  if( expr[i] != '-' )
                {
                   printf("Erreur Syntaxique: presence de caractere(s) mal placer.\n");
                   return 0;   /* Expression Incorrecte */
                }
                 else   if( expr[i+1] == '(' ) )
                         {
                              printf("Erreur Syntaxique: presence de caractere(s) mal placer.\n");
                             return 0;   /* Expression Incorrecte */
                         }

                }

         /* Dans le cas d'un operateur differant de '-' :
            il faut que l'operateur soi suivi d'un nombre ou bien d'une '(' ou
            bien un '-'  ,ET, il faut qu'il soi préceder par un nombre
            ou bien par une ')' , Dans le cas contrere, C'est une erreur */
         else if( expr[i] != '-' )
            {
            if( !( (operande(i+1) || expr[i+1] == '(' || expr[i+1] == '-') &&  (isdigit(expr[i-1]) || expr[i-1] == ')') ) )
            {
               printf("Erreur Syntaxique: presence caractere(s) mal placer.\n");
               return 0;   /* Expression Incorrecte */
            }
         }

         /* Si l'operateur est un '-' : */
         else if( !( (operande(i+1) || expr[i+1] == '(' ) && (operande(i+1) || expr[i-1]==')' || expr[i-1]=='('|| expr[i-1] == 'E' || expr[i-1] == 'e' || expr[i-1]=='+'||
                expr[i-1]=='*' || expr[i-1]=='/'||expr[i-1]=='%') ))
         {
            printf("Erreur Syntaxique: presence caractere(s) mal placer.\n");
            return 0;   /* Expression Incorrecte */
         }

      }

      /* pour le caractere '(' */
      if( expr[i] == '(' )
      {
         /* s'il ce trouve au début de l'expression */
         if( i == 0 )
         {
            /* il faut qu'il soit suivi par soi un nbr soi '(' soi '-'  */
            if( ! (operande(i+1) || expr[i+1]=='(' || expr[i+1]=='-') )
            {
               printf("Erreur Syntaxique: presence caractere(s) mal placer.\n");
               return 0;
            }
         }
         /* s'il ce trouve a la fin de l'expression, alors c'est une erreur */
         else if( i == len-1 )
         {
            printf("Erreur Syntaxique: presence caractere(s) mal placer.\n");
            return 0;
         }
         /* s'il ce trouve quelque part dans l'expression */
         else
         {
            if( ! ( (isdigit(expr[i+1]) || expr[i+1]=='(' || expr[i+1]=='-') &&
                    (expr[i-1]=='*' || expr[i-1]=='-'|| expr[i-1]=='/' ||
                     expr[i-1]=='+' || expr[i-1]=='%'|| expr[i-1]=='(') ) )
            {
              printf("Erreur Syntaxique: presence caractere(s) mal placer.\n");
              return 0;
            }
         }
      }

      /* pour le caractere ')' */
      if( expr[i] == ')' )
      {
         /* s'il ce trouve a la fin de l'expression */
         if( i == len-1 )
         {
            /* il faut qu'il soit preceder par soi un nbr soi ')'  */
            if( ! ( isdigit(expr[i-1]) || expr[i-1]==')' ) )
            {
               printf("Erreur Syntaxique: presence caractere(s) mal placer.\n");
               return 0;
            }
         }
         /* s'il ce trouve au début de l'expression, alors c'est une erreur */
         else if( i == 0 )
         {
            printf("Erreur Syntaxique: presence caractere(s) mal placer.\n");
            return 0;
         }
         /* s'il ce trouve quelque part dans l'expression */
         else
         {
            if( ! ( (operande(i+1) || expr[i-1]==')') &&
                    (expr[i+1]=='*' || expr[i+1]=='-'|| expr[i+1]=='/' ||
                     expr[i+1]=='+' || expr[i+1]=='%'|| expr[i+1]==')') ) )
            {
              printf("Erreur Syntaxique: presence caractere(s) mal placer.\n");
              return 0;
            }
         }
      }

      if(expr[0]=='e' || expr[0]=='E' || expr[len-1]=='e' || expr[len-1]=='E' )
      {
         printf("Erreur Syntaxique: presence caractere(s) mal placer.\n");
         return 0;
      }

      else if( (expr[i] == 'E' || expr[i] == 'e' ) &&
               (expr[i+1]== '*' || expr[i+1]== '/' || expr[i+1]== '+' || expr[i+1]== '%') )
      {
         printf("Erreur Syntaxique:nnn presence caractere(s) mal placer.\n");
         return 0;
      }

   }

   return 1;   /* Expression correcte */
}



int main ()
{
   char expr[MAX_LEN];  /* l'expression sous forme de chaine */
   elem* expr_vect;  /* pour l'expression sous forme d'un vecteur */
   int len_vect;
   stack *P;
   float the_result;

   /* demander la saisi tantque l'expression est incorrecte */
   do
   {
      puts ("Donnez une Expression Arithmetique correcte:");
      gets (expr);
   }
   while( ! CorrectExpression(expr) );
}
