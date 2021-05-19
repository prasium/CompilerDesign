/* Basic Lex program to count the number of: 
(a) Lines (b) Words (c) Capital Letters (d) Small Letters (e) Numbers (10,21) (f)Digits (0-9) 
(g)Special Character (h)Delimiter (i)Operator (j)Relational Operator (k)Total Characters
*/

%{

	int lines=0, words=1, capletters=0, smallletters=0;
	int numrange=0, digits=0, special=0, delim=0, operator=0;
	int relop=0, totalchar=0;

%}


%%

"\n" {lines++;
		delim++;
	}
[\t ] { words++;
		delim++;
		}
[A-Z] { 	capletters++;
			totalchar++;}

[a-z] { 	smallletters++;
			totalchar++;}

[0-9]* { int num = atoi(yytext);
      		if (num>=10 && num<=21) {
     			numrange++; 
    		}
    digits += yyleng;
    totalchar += yyleng;
}	 
"?"|","|"."|"{"|"}"|"#"|"&" { special++;
								totalchar++;}
[\r]   { delim++;
			totalchar++;}

"+"|"-"|"/"|"*"|"="|"%" { operator++;
			totalchar++;
			}

"<="|">="|"!="|"=="|"<"|">"   { relop++;
								totalchar++;}

. { totalchar+=yyleng;}

%%

int yywrap() {}

int main()
{

	yylex();

	printf("\nNumber of \nLines :%d \nWords :%d",lines,words);
	printf("\nCapital letters :%d \nSmall letters :%d",capletters,smallletters);
	printf("\nNumbers(10-21) : %d \nDigits :%d",numrange,digits);
	printf("\nSpecial characters :%d \nDelimiters :%d",special,delim);
	printf("\nOperators :%d \nRelational Operators :%d",operator,relop);
	printf("\nTotal Characters :%d",totalchar);


	return 0;
}