/* LEX FILE TO COUNT WORD AND CHARACTER */

%{
	int countWord=0; //for counting word
	int countChar=0; //for counting characters
%}
/* Production Rules */
%%

([A-Za-z0-9])* {countWord++;
				countChar+=strlen(yytext);}
. countChar++;

"\n" {printf("Number of characters :%d \nNumber of words :%d",countChar,countWord);}
%%

int yywrap(){}
int main()
{
	yylex();
	return 0;
}