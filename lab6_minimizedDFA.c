// C PROGRAM TO MINIMIZE DFA USING EQUIVALENCE METHOD
#include <stdio.h>
#include <string.h>
 
 // MAX VALUES FOR STATES AND SYMBOLS
#define STATES  50
#define SYMBOLS 20
 
 // Global variables
int N_symbols;  
int N_DFA_states;   
char DFA_finals[5];   
int DFAtab[STATES][SYMBOLS];
 
char StateName[STATES][STATES+1];   //state-name table 
int minDFA_states;    // number of optimized DFA states 
int OptDFA[STATES][SYMBOLS];
char NEW_finals[STATES+1];
 
// Print the DFA table
void displaydfa_table(int tab[][SYMBOLS], int nstates,int nsymbols, char *finals)
{
    int i, j;
    printf("     | ");
    for (i = 0; i < nsymbols; i++) 
    printf("  %c  ", '0'+i);
 
    printf("\n--------");
    for (i = 0; i < nsymbols; i++) 
    printf("-----");
    printf("\n");
 
    for (i = 0; i < nstates; i++) {
        printf("  %c  | ", 'A'+i);  
        for (j = 0; j < nsymbols; j++)
            printf("  %c  ", tab[i][j]);   
        printf("\n");
    }
    printf("Final states = %s\n", finals);
}
 

void inputDFA_tab()
{
int state,symbol;
printf("Enter number of States : ");
scanf("%d",&state);
printf("Enter number of Symbols : ");
scanf("%d",&symbol);
  printf("Enter INPUT in DFA TABLE FORMAT (States(i),Symbols(j)) format -\n ");
    printf("(If no output state mapping on a symbol just enter '-' )\n");
    int i,j;
   for (i=0;i<state;i++)
    {
        printf("State %c :-\n",(char)(65+i));
        printf("Symbol %d till %d:",0,symbol-1);           
        for(j=0;j<symbol;j++)
        { 
             char s[5];
             scanf("%s",s);
             strcpy((char *)&DFAtab[i][j], s); 
        }
    }
	printf("\nEnter final states :");
    scanf("%s",DFA_finals );
	N_DFA_states = state;
    N_symbols = symbol;
}
 

// Fetch next-state string for current-state string
void get_next_state(char *nextstates, char *cur_states,
    int dfa[STATES][SYMBOLS], int symbol)
{
    int i, ch;
    for (i = 0; i < strlen(cur_states); i++)
        *nextstates++ = dfa[cur_states[i]-'A'][symbol];
    *nextstates = '\0';
}
 

//  fetch index of the equivalence states for state 'ch'.

char equiv_class_ndx(char ch, char stnt[][STATES+1], int n)
{
    int i;
 
    for (i = 0; i < n; i++)
        if (strchr(stnt[i], ch)) return i+'0';
    return -1;  /* next state is NOT defined */
}
 
char is_one_nextstate(char *s)
{
    char equiv_class;   /* first equiv. class */
 
    while (*s == '@') s++;
    equiv_class = *s++; /* index of equiv. class */
 
    while (*s) {
        if (*s != '@' && *s != equiv_class) return 0;
        s++;
    }
 
    return equiv_class; 
}
 
int state_index(char *state, char stnt[][STATES+1], int n, int *pn,int cur)   
{
    int i;
    char state_flags[STATES+1]; // next state info
 
    if (!*state) return -1; // no next state  return
 
    for (i = 0; i < strlen(state); i++)
        state_flags[i] = equiv_class_ndx(state[i], stnt, n);
    state_flags[i] = '\0';
 
    printf("   %d:[%s]\t=> [%s] (%s)\n",
        cur, stnt[cur], state, state_flags);
    if (i=is_one_nextstate(state_flags))
        return i-'0';   
    else {
        strcpy(stnt[*pn], state_flags); 
        return (*pn)++;
    }
}
 

//    Separate DFA states into finals and non-finals
int init_equiv_class(char statename[][STATES+1], int n, char *finals)
{
    int i, j;
 
    if (strlen(finals) == n) {  /* all states are final states */
        strcpy(statename[0], finals);
        return 1;
    }
 
    strcpy(statename[1], finals);   /* final state group */
 
    for (i=j=0; i < n; i++) {
        if (i == *finals-'A') {
            finals++;
        } else statename[0][j++] = i+'A';
    }
    statename[0][j] = '\0';
 
    return 2;
}
 
//    Get minimized DFA 'newdfa' for equivalent class.
int get_optimized_DFA(char stnt[][STATES+1], int n,
    int dfa[][SYMBOLS], int n_sym, int newdfa[][SYMBOLS])
{
    int n2=n;       /* 'n' + <num. of state-division info> */
    int i, j;
    char nextstate[STATES+1];
 
    for (i = 0; i < n; i++) {    /* for each pseudo-DFA state */
        for (j = 0; j < n_sym; j++) {    /* for each input symbol */
            get_next_state(nextstate, stnt[i], dfa, j);
            newdfa[i][j] = state_index(nextstate, stnt, n, &n2, i)+'A';
        }
    }
 
    return n2;
}
 
/*
    char 'ch' is appended at the end of 's'.
*/
void chr_append(char *s, char ch)
{
    int n=strlen(s);
 
    *(s+n) = ch;
    *(s+n+1) = '\0';
}
 
void sort(char stnt[][STATES+1], int n)
{
    int i, j;
    char temp[STATES+1];
 
    for (i = 0; i < n-1; i++)
        for (j = i+1; j < n; j++)
            if (stnt[i][0] > stnt[j][0]) {
                strcpy(temp, stnt[i]);
                strcpy(stnt[i], stnt[j]);
                strcpy(stnt[j], temp);
            }
}
 
// split into final non final states
int split_equiv_class(char stnt[][STATES+1],
    int i1, // index of 'i1'-th equiv. class 
    int i2, // index of equiv. vector for 'i1'-th class 
    int n,  // no of entries in 'stnt' 
    int n_dfa)  // no of source DFA entries 
{
    char *old=stnt[i1], *vec=stnt[i2];
    int i, n2, flag=0;
    char newstates[STATES][STATES+1];   /* max. 'n' subclasses */
 
    for (i=0; i < STATES; i++) newstates[i][0] = '\0';
 
    for (i=0; vec[i]; i++)
        chr_append(newstates[vec[i]-'0'], old[i]);
 
    for (i=0, n2=n; i < n_dfa; i++) {
        if (newstates[i][0]) {
            if (!flag) {    
                // stnt[i1] = s1 
                strcpy(stnt[i1], newstates[i]);
                flag = 1;   // overwrite parent class 
            } else  // newstate is appended in 'stnt' 
                strcpy(stnt[n2++], newstates[i]);
        }
    }
 
    sort(stnt, n2); // sort the classes
 
    return n2;  // no of new states
}
 
// new segmented equiv class
int set_new_equiv_class(char stnt[][STATES+1], int n,
    int newdfa[][SYMBOLS], int n_sym, int n_dfa)
{
    int i, j, k;
 
    for (i = 0; i < n; i++) {
        for (j = 0; j < n_sym; j++) {
            k = newdfa[i][j]-'A';  // index of eq vector
            if (k >= n)  
                return split_equiv_class(stnt, i, k, n, n_dfa);
        }
    }
 
    return n;
}
 
void print_equiv_classes(char stnt[][STATES+1], int n)
{
    int i;
 
    printf("\nEquivalent class partitions  :-\n");
    for (i = 0; i < n; i++)
        printf(" %d:{%s}", i, stnt[i]);
    printf("\n");
}
 
// minimization of states of DFA
int minimizeDFA( int dfa[][SYMBOLS], int n_dfa, int n_sym, char *finals, char stnt[][STATES+1], int newdfa[][SYMBOLS]) 
{
    char nextstate[STATES+1];
    int n; // new DFA States
    int n2;
 
    n = init_equiv_class(stnt, n_dfa, finals);
    int k=0;
    while (1) {
        printf("k=%d",k++);
        print_equiv_classes(stnt, n);
        n2 = get_optimized_DFA(stnt, n, dfa, n_sym, newdfa);
        if (n != n2)
            n = set_new_equiv_class(stnt, n, newdfa, n_sym, n_dfa);
        else break; 
    }
 
    return n; 
}
 
int is_subset(char *s, char *t)
{
    int i;
 
    for (i = 0; *t; i++)
        if (!strchr(s, *t++)) return 0;
    return 1;
}
 
// Final states of minimized DFA
void minDFAfinal(char *newfinals,char *oldfinals, char stnt[][STATES+1],int n)  
{
    int i; 
    for (i = 0; i < n; i++)
        if (is_subset(oldfinals, stnt[i])) *newfinals++ = i+'A';
    *newfinals++ = '\0';
}
 
int main()
{
    // Take input of DFA table
    inputDFA_tab();
    // Display DFA 
    printf("\nDFA State Transition Table :-\n");
    displaydfa_table(DFAtab, N_DFA_states, N_symbols, DFA_finals);
    
    // Minimize DFA Table
    minDFA_states = minimizeDFA(DFAtab, N_DFA_states,N_symbols, DFA_finals, StateName, OptDFA);
    
    // New Final States of Minimized DFA 
    minDFAfinal(NEW_finals, DFA_finals, StateName, minDFA_states);
    
    // Print Minimized DFA Table
    printf("\nMinimized DFA State Transition Table :-\n");
    displaydfa_table(OptDFA, minDFA_states, N_symbols, NEW_finals);

    return 0;
}