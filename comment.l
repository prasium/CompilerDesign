/* LEX FILE TO IDENTIFY COMMENTS */
/* Definition section */
%{
%}

/* Transition rules */

%%

"//".*\n {printf("\n Single Line Comment");}
"/*"([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*"*/" {printf("\n Multiple line Comment");}

%%

/* Code Section */
int yywrap(){}
int main()
{
yylex();

return 0;
}

