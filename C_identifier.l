/* LEX FILE TO IDENTIFY C Identifiers and Constants */

%{
#include <stdio.h>	
%}
DIGIT [0-9]
LETTER [A-Za-z_]
OP [+-/*]

%%

("int")|("float")|("char")|("case")|("default")|("if")|("for") { printf("%s is a keyword\n",yytext);}

{LETTER}+({LETTER}|{DIGIT})*  {printf("%s\tValid Identifier\n",yytext);}


({DIGIT}|^{LETTER})+{LETTER}+  {printf("%s\tInvalid Identifier\n",yytext);}

[+-]?{DIGIT}({DIGIT})* {printf("%s\tConstant\n",yytext);}


%%

int yywrap(){ return 1;}
int main()
{
	yylex();

	return 0;
}