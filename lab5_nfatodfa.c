// C PROGRAM TO CONVERT E-NFA to DFA

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#define MAX_LEN 100 

char NFA_FILE[MAX_LEN]; 
char buffer[MAX_LEN]; 
int zz = 0; 

// Structure to store DFA states with their mappings
struct DFA { 
char *states; 
int count; 
} dfa; 

int last_index = 0; 
FILE *fp; 
int symbols; 

// reset the hash map
void reset(int ar[], int size) { 
int i; 
// reset all the values of array to zero 
for (i = 0; i < size; i++) { 
	ar[i] = 0; 
} 
} 

// Check the States that are present in the e-closure, map them to hash set
void check(int ar[], char S[]) { 
int i, j; 
// Parse the individual states of NFA 
int len = strlen(S); 
for (i = 0; i < len; i++) { 
	// Set hash map for the position of the states which is found 
	j = ((int)(S[i]) - 65); 
	ar[j]++; 
} 
} 

//  find closure of new states 
void state(int ar[], int size, char S[]) { 
int j, k = 0; 
// join multiple states of NFA to create new states of DFA 
for (j = 0; j < size; j++) { 
	if (ar[j] != 0) 
	S[k++] = (char)(65 + j); 
} 
//end of the state 
S[k] = '\0'; 
} 

// pick the next closure from closure set 
int closure(int ar[], int size) { 
int i; 
// check new closure present or not 
for (i = 0; i < size; i++) { 
	if (ar[i] == 1) 
	return i; 
} 
return (100); 
} 

// check whether new DFA states can be entered in DFA table or not 
int indexing(struct DFA *dfa) { 
int i; 

for (i = 0; i < last_index; i++) { 
	if (dfa[i].count == 0) 
	return 1; 
} 
return -1; 
} 

// display epsilon closure
void Display_closure(int states, int closure_ar[], 
					char *closure_table[], 
					char *NFA_TABLE[][symbols + 1], 
					char *DFA_TABLE[][symbols]) { 
int i; 
for (i = 0; i < states; i++) { 
	reset(closure_ar, states); 
	closure_ar[i] = 2; 

	// neglect blank entry 
	if (strcmp((char *)&NFA_TABLE[i][symbols], "-") != 0) { 

	// copy the NFA transition state to buffer 
	strcpy(buffer,(char *) &NFA_TABLE[i][symbols]); 
	check(closure_ar, buffer); 
	int z = closure(closure_ar, states); 

	// till closure get completely saturated 
	while (z != 100) 
	{ 
		if (strcmp((char *)&NFA_TABLE[z][symbols], "-") != 0) { 
		strcpy(buffer,(char *) &NFA_TABLE[z][symbols]); 

		// call the check function 
		check(closure_ar, buffer); 
		} 
		closure_ar[z]++; 
		z = closure(closure_ar, states); 
	} 
	} 

	// print the e closure for every states of NFA 
	printf("\nEpsilon-Closure (%c) :\t", (char)(65 + i)); 

	bzero((void *)buffer, MAX_LEN); 
	state(closure_ar, states, buffer); 
	strcpy((char *)&closure_table[i], buffer); 
	printf("%s", (char *)&closure_table[i]); 
} 
} 

// check New States in DFA 
int new_states(struct DFA *dfa, char S[]) { 

int i; 

// To check the current state is already being used as a DFA state or not in 
// DFA transition table 
for (i = 0; i < last_index; i++) { 
	if (strcmp((char *)&dfa[i].states, S) == 0) 
	return 0; 
} 

// push the new 
strcpy((char *)&dfa[last_index++].states, S); 

// set the count for new states entered to zero 
dfa[last_index - 1].count = 0; 
return 1; 
} 

// Transition function from NFA to DFA  (union of closure operation ) 
void trans(char S[], int M, char *clsr_t[], int st, 
			char *NFT[][symbols + 1], char TB[]) { 
int len = strlen(S); 
int i, j, k, g; 
int arr[st]; 
int sz; 
reset(arr, st); 
char temp[MAX_LEN], temp2[MAX_LEN]; 
char *buff; 

// Transition function from NFA to DFA 
for (i = 0; i < len; i++) { 

	j = ((int)(S[i] - 65)); 
	strcpy(temp, (char *)&NFT[j][M]); 

	if (strcmp(temp, "-") != 0) { 
	sz = strlen(temp); 
	g = 0; 

	while (g < sz) { 
		k = ((int)(temp[g] - 65)); 
		strcpy(temp2,(char *) &clsr_t[k]); 
		check(arr, temp2); 
		g++; 
	} 
	} 
} 

bzero((void *)temp, MAX_LEN); 
state(arr, st, temp); 
if (temp[0] != '\0') { 
	strcpy(TB, temp); 
} else
	strcpy(TB, "-"); 
} 

// display DFA transition state table
void Display_DFA(int last_index, struct DFA *dfa_states, 
				char *DFA_TABLE[][symbols]) { 
int i, j; 
printf("\n\t DFA TRANSITION STATE TABLE \t\t "); 
printf("\nSTATES OF DFA :\t\t"); 

for (i = 1; i < last_index; i++) 
	printf("%s, ",(char *) &dfa_states[i].states); 
printf("\n"); 
printf("\nSYMBOLS FOR DFA: \t"); 

for (i = 0; i < symbols; i++) 
	printf("%d, ", i); 
printf("\n\n"); 
printf("STATES\t"); 

for (i = 0; i < symbols; i++) 
	printf("|%d\t", i); 
printf("\n"); 

// display the DFA transition state table 
printf("--------+-----------------------\n"); 
for (i = 0; i < zz; i++) { 
	printf("%s\t",(char *) &dfa_states[i + 1].states); 
	for (j = 0; j < symbols; j++) { 
	printf("|%s \t",(char *) &DFA_TABLE[i][j]); 
	} 
	printf("\n"); 
} 
} 

void inputNFA(char *NFA_TABLE[][symbols+1],int states, int symbols)
{
    printf("\nEnter INPUT in NFA TABLE FORMAT (States(i),Symbols(j)) format -\n ");
    printf("\nIf no output state mapping on a symbol just enter - \n");
   int i,j;
   for (i=0;i<states;i++)
    {
        printf("State %c :-\n",(char)(65+i));
        for(j=0;j<=symbols;j++)
        {
            if(j==symbols)
                printf("Symbol epsilon (e) :");
            else
             printf("Symbol %d :",j);
             char s[5];
             scanf("%s",s);
             strcpy((char *)&NFA_TABLE[i][j], s); 
        }
    }
}


// Main Function
int main() { 
int i, j, states; 
char T_buf[MAX_LEN]; 

// creating an array dfa structures 
struct DFA *dfa_states = malloc(MAX_LEN * (sizeof(dfa))); 
printf("\nEnter number of States : ");
scanf("%d",&states);
printf("Enter number of Symbols : ");
scanf("%d",&symbols);

printf("\nNFA STATES:\t"); 
for (i = 0; i < states; i++) 
	printf("%c, ", (char)(65 + i)); 

printf("\nALPHABET SET FOR NFA: \t"); 
for (i = 0; i < symbols; i++) 
	printf("%d, ", i); 
printf("epsilon (e)"); 

char *NFA_TABLE[states][symbols + 1]; 

inputNFA(NFA_TABLE,states,symbols);

char *DFA_TABLE[MAX_LEN][symbols]; 

printf("\n\t NFA STATE TRANSITION TABLE \n"); 
printf("STATES\t"); 

for (i = 0; i < symbols; i++) 
	printf("|%d\t", i); 
printf("epsilon(e)\n"); 

// Displaying the matrix of NFA transition table 
printf("--------+------------------------------------\n"); 
for (i = 0; i < states; i++) { 
	printf("%c\t", (char)(65 + i)); 

	for (j = 0; j <= symbols; j++) { 
	printf("|%s \t",(char *) &NFA_TABLE[i][j]); 
	} 
	printf("\n"); 
} 
int closure_ar[states]; 
char *closure_table[states]; 

Display_closure(states, closure_ar, closure_table, NFA_TABLE, DFA_TABLE); 
strcpy((char *)&dfa_states[last_index++].states, "-"); 

dfa_states[last_index - 1].count = 1; 
bzero((void *)buffer, MAX_LEN); 

strcpy(buffer,(char *) &closure_table[0]); 
strcpy((char *)&dfa_states[last_index++].states, buffer); 

int Sm = 1, ind = 1; 
int start_index = 1; 

// Filling up the DFA table with transition values till new states can be entered in DFA table 
while (ind != -1) { 
	dfa_states[start_index].count = 1; 
	Sm = 0; 
	for (i = 0; i < symbols; i++) { 

	trans(buffer, i, closure_table, states, NFA_TABLE, T_buf); 

	// storing the new DFA state in buffer 
	strcpy((char *)&DFA_TABLE[zz][i], T_buf); 

	// parameter to control new states 
	Sm = Sm + new_states(dfa_states, T_buf); 
	} 
	ind = indexing(dfa_states); 
	if (ind != -1) 
	strcpy(buffer,(char *) &dfa_states[++start_index].states); 
	zz++; 
} 
// display the DFA TABLE 
Display_DFA(last_index, dfa_states, DFA_TABLE); 

return 0; 
} 