/* Lex program to validate arithmetic operations and follow BODMAS rile*/

%{
	
	#include<stdio.h>
	
	//Variables to keep count of operators
	int operators=0,operands=0;
	int add=0,sub=0, mul=0, divi=0, mod=0;
	int lPar=0, rPar=0, lcb=0,rcb=0;
	int counta=0, counts=0, countm=0, countd=0, countmod=0;	// for counting number of add,sub,mul,div and mod operators 
%}


id [a-zA-Z]+ 
digit [0-9]+ 


%%

{id} {	printf("\n %s is an identifier \n",yytext);
		operands++; }
{digit} {	printf("\n %s is a constant \n",yytext);
			operands++; }

[+] { add++; counta=1;}
[-] { sub++; counts=1;}
[*] { mul++; countm=1;}
[/] { divi++; countd=1;}
[%] { mod++;  countmod=1;}
[(] { lPar++; }
[)] { rPar++; }
[{] { lcb++; }
[}] { rcb++; }
%%


int yywrap()  
{  
    return 1;  
}  

int main()
{
printf("\n Enter the expression : ");
yylex();


operators=add+sub+divi+mul+mod;

if((lPar-rPar==0||lcb-rcb==0)&&(operators==(operands-1)))
{
printf("\n Expression is valid.");
}
else
{
printf("\n Expression is invalid !");
}
	printf("\nThe Operators count :-\nAdd=%d\nSub=%d\nMul=%d\nDiv=%d\nMod=%d\n",add,sub,mul,divi,mod);
printf("Operators are:-");
	if(counta)
		printf("\n+\n");
	if(counts)
		printf("-\n");
	if(countm)
		printf("*\n");
	if(countd)
		printf("/\n");
	if(countmod)
		printf("%\n");
return 0;
}