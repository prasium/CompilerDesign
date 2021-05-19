// Thompson's algorithm for conversion of Regular Expressions to NFA

#include <stdio.h>
#include <string.h>

void main()
{

char regex[20];
int q[20][3];
int i,j,length,a,b;

//initializing transition table of NFA
for(a=0;a<20;a++)
{
    for(b=0;b<3;b++)
    {   
        q[a][b]=0;
    }
}

//Take input the Regular Expression
printf("Alphabet set for this program = {a,b,e} \ne=epsilon");
printf("\nEnter Regular expression : ");
scanf("%s",regex);

//length of regex
length=strlen(regex);

//counter variables
i=0,j=1;

//traversing the input
while(i<length)
{

    //when input scanned is 'a'
    if(regex[i]=='a'&&regex[i+1]!='/'&&regex[i+1]!='*')
    {
        q[j][0]=j+1;
        j++;
    }


    //when input scanned is 'b'
    if(regex[i]=='b'&&regex[i+1]!='/'&&regex[i+1]!='*')
    {
        q[j][1]=j+1;
        j++;
    }


    //when input scanned is 'e'
    if(regex[i]=='e'&&regex[i+1]!='/'&&regex[i+1]!='*')
    {
         q[j][2]=j+1;
        j++;
    }

    if(regex[i]=='a'&&regex[i+1]=='/'&&regex[i+2]=='b')
    {
        q[j][2]=((j+1)*10)+(j+3);
        j++;
        q[j][0]=j+1;
        j++;
        q[j][2]=j+3;
        j++;
        q[j][1]=j+1;
        j++;
        q[j][2]=j+1;
        j++;
        i+=2;
    }
    
    if(regex[i]=='b'&&regex[i+1]=='/'&&regex[i+2]=='a')
    {
        q[j][2]=((j+1)*10)+(j+3);
        j++;
        q[j][1]=j+1;
        j++;
        q[j][2]=j+3;
        j++;
        q[j][0]=j+1;
        j++;
        q[j][2]=j+1;
        j++;
        i+=2;
    }

    if(regex[i]=='a'&&regex[i+1]=='*')
    {
        q[j][2]=((j+1)*10)+(j+3);
        j++;
        q[j][0]=j+1;
        j++;
        q[j][2]=((j+1)*10)+(j-1);
        j++;
    }

    if(regex[i]=='b'&&regex[i+1]=='*')
    {
        q[j][2]=((j+1)*10)+(j+3);
        j++;
        q[j][1]=j+1;
        j++;
        q[j][2]=((j+1)*10)+(j-1);
        j++;
    }

    if(regex[i]==')'&&regex[i+1]=='*')
    {   
        q[0][2]=((j+1)*10)+1;
        q[j][2]=((j+1)*10)+1;
        j++;
    }
    //Next input char
    i++;
}

//printing transition functions
printf("\n The NFA Transition function of the Regex is :- \nOn Input \t States");
    for(i=0;i<=j;i++)
    {
        if(q[i][0]!=0)
        printf("\n q[%d,a] \t-> %d",i,q[i][0]);
        if(q[i][1]!=0)
        printf("\n q[%d,b] \t-> %d",i,q[i][1]);
        if(q[i][2]!=0)
        {
            if(q[i][2]<10)
            printf("\n q[%d,e] \t-> %d",i,q[i][2]);
            else
            printf("\n q[%d,e] \t-> %d & %d",i,q[i][2]/10,q[i][2]%10);
        }
    }
    printf("\n");
}