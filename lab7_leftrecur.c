#include<stdio.h>  
#include<string.h>  
#define SIZE 20  
  
int main () {  
    char non_terminal;  
    char beta,alpha;  
    int n;  
    char production[10][SIZE];  
    int index=3; // index of the string following "->"   
    printf("# represents (EPSILON) in this program\n");
    printf("Enter the number of productions : ");  
    scanf("%d",&n);  
    printf("Enter the grammar in this format - (S->S|A|b) :\n");  
    for(int i=0;i<n;i++){  
        printf("\n Enter Production %d : ",i+1);
        scanf("%s",production[i]);  
      }

for(int i=0;i<n;i++){
    printf("\nThe Production : %s",production[i]);  
        non_terminal=production[i][0]; 
        // If The Production is left recursive the LHS char and first char of RHS would be equal 
        
        if(non_terminal==production[i][index])
         {  
            printf(" is left recursive.\n");  
            // rest elements become alpha string
            alpha=production[i][index+1];  
            
            while(production[i][index]!=0 && production[i][index]!='|')  
                index++;  
                if(production[i][index]!=0) {  
                     beta=production[i][index+1];  
                      printf("Production without left recursion:\n");  
                      printf("%c->%c%c\'",non_terminal,beta,non_terminal);  
                      printf("\n%c\'->%c%c\'|#\n",non_terminal,alpha,non_terminal);  
               }  
                 else  
                      printf(" This can't be reduced not in the (Aa|B) format\n");  
            }  
           else  
                 printf(" is not left recursive.\n");  
            index=3;  
       }  
  } 