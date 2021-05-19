#include <stdio.h>
#include<string.h>
#include<ctype.h>

struct data
	{
		int ptr, left, right;
		char label;
	} dag[30];

int main()
{
	
	int  i = 0, state = 1, x, y, k, n=0, ptr, l, j, change;
	char store, inp[30], inptemp[30], var;
	memset(dag,0,sizeof(dag));
	printf("\nEnter the Arithmetic Expression (Use () to enclose the whole expression ): \n");
	scanf("%s", inp); 
    memset(inptemp,0,sizeof(inptemp));
	l = strlen(inp);
a:
	for (i = 0; inp[i] != ')'; i++)
		;
	for (j = i; inp[j] != '('; j--)
		;
	for (x = j + 1; x < i; x++)
		if (isalpha(inp[x]))
			inptemp[n++] = inp[x];
		else if (inp[x] != '0')
			store = inp[x];
	inptemp[n++] = store;

	for (x = j; x <= i; x++)
		inp[x] = '0';
	if (inp[0] != '0')
		goto a;
	for (i = 0; i < n; i++)
	{
		dag[i].label = inptemp[i];
		dag[i].ptr = i;
		if (!isalpha(inptemp[i]) && !isdigit(inptemp[i]))
		{
			dag[i].right = i - 1;
			ptr = i;

			var = inptemp[i - 1];
			if (isalpha(var))
				ptr = ptr - 2;
			else
			{
				ptr = i - 1;
			b:
				if (!isalpha(var) && !isdigit(var))
				{
					ptr = dag[ptr].left;
					var = inptemp[ptr];
					goto b;
				}
				else
					ptr = ptr - 1;
			}
			dag[i].left = ptr;
		}
	}
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if ((dag[i].label == dag[j].label && dag[i].left == dag[j].left) && dag[i].right == dag[j].right)
			{
				for (k = 0; k < n; k++)
				{
					if (dag[k].left == dag[j].ptr)
						dag[k].left = dag[i].ptr;
					if (dag[k].right == dag[j].ptr)
						dag[k].right = dag[i].ptr;
				}
				dag[j].ptr = dag[i].ptr;
			}
		}
	}
	printf("\n Directed Acyclic Graph for the expression is :-\n\n");
	printf("\n ptr\t left ptr\t right ptr\t label\n");
	for (i = 0; i < n; i++) 
		printf("\n %d\t\t%d\t\t%d\t\t%c\n", dag[i].ptr, dag[i].left, dag[i].right, dag[i].label);
    
    return 0;
}