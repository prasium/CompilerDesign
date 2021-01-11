/* LEX FILE TO IDENTIFY TYPE OF TOKENS */

%{
#include <stdio.h>	
%}
DIGIT [0-9]
LETTER [A_Za-z]
DELIM [ \t\n\r]

%%

("auto")|("double")|("int")|("struct")|("break")|("else")|("long")|("switch")|("case")|("enum") {printf("%s\tKeyword\n",yytext);}
 ("register")|("typedef")|("char")|("extern")|("return")|("union")|("const")|("float")|("short") {printf("%s\tKeyword\n",yytext);}
 ("unsigned")|("continue")|("for")|("signed")|("void")|("default")|("goto")|("sizeof")|("volatile") {printf("%s\tKeyword\n",yytext);}
 ("do")|("if")|("static")|("while") {printf("%s\tKeyword\n",yytext);}


{LETTER}({LETTER}|{DIGIT})*  {printf("%s\tIdentifier\n",yytext);}


[+-]?{DIGIT}({DIGIT})* {printf("%s\tConstant\n",yytext);}


"<="|">="|"++"|"!="|"=="|"<"|">"|"+"|"-"|"*"|"/"|"%"|"="|"&&"|"||" {printf("%s\tOperator \n",yytext);}


\".*\" {printf("%s\tString \n",yytext);}


[?,.\[\]\(\)\{\}#&] {printf("%s\tSpecial Character \n",yytext);}

%%

int yywrap(){}
int main()
{
	yylex();

	return 0;
}