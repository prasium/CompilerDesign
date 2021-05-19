//PROGRAM TO COMPUTER FIRST AND FOLLOW OF A GRAMMAR 

#include<bits/stdc++.h>

using namespace std;

//Global Variables 
vector<string> G[1000]; // For storing NT productions
set<char> first[1000]; // For Storing First
set<char> follow[1000]; // For Storing Follow
bool visit[1000];

//First Function
void calFirst(int beg)
{
    // If the NT is visited
    if(visit[beg]==true)
    return;

    for(int i=0;i<G[beg].size();i++)
    {
        if(G[beg][i]=="#")
        {
            // if it is epsilon
            first[beg].insert('#');
        }
        else if(!isupper(G[beg][i][0])){
            // if it is a terminal
            first[beg].insert(G[beg][i][0]);
        }
        else{
            //  if it is a non-terminal
            bool flag;
            int k;       
            for(k=0;k<G[beg][i].length();k++)
            {
                char next = G[beg][i][k];
                // If not a non terminal in each production
                 if(!isupper(next)){
                  first[beg].insert(next);
                  break;
                }
                //If the NT is not visited 
            if(!visit[next-'A'])
                calFirst(next-'A');
                flag=0;
            // Expanding the NT and calculating the First of that production
            for(auto it= first[next-'A'].begin(); it!=first[next-'A'].end();it++)
            {
                if((*it)=='#')
                {
                    flag=1;
                }
                else {
                    first[beg].insert(*it);
                }
            }

            if(!flag)
            break;
            }

            if(k==G[beg][i].length())
            {
                first[beg].insert('#');
            }
        }
    }
    //Mark visited
    visit[beg]=1;
}

//Follow Function
void calFollow(int beg)
{
    // Starting Production has $ in Follow always  
    if(beg==0){
        follow[beg].insert('$');
    }

    for(int i=0;i<G[beg].size();i++){
            int j;
        for( j=0;j<G[beg][i].size()-1;j++){
            char ch=G[beg][i][j];
            if(isupper(ch)){
                bool f=false;
                int k;
                for(k=j+1;k<G[beg][i].size();k++){
                char next=G[beg][i][k];
                // If Follow is a terminal then add it
                if(!isupper(next)){
                    follow[ch-'A'].insert(next);
                    break;
                }
                else{
                        f=false;
                  // If Follow is a Non Terminal then get first of the Non Terminal 
                    for(auto itr=first[next-'A'].begin();itr!=first[next-'A'].end();itr++){
                        if((*itr)=='#'){
                            f=true;
                        }
                        else follow[ch-'A'].insert(*itr);
                    }
                    if(!f)break;
                }
                }
                if(k==G[beg][i].size()){
                    for(auto itr=follow[beg].begin();itr!=follow[beg].end();itr++){
                        follow[ch-'A'].insert(*itr);
                    }
                }
            }
        }

        char ch=G[beg][i][j];
        if(isupper(ch)){
            for(auto itr=follow[beg].begin();itr!=follow[beg].end();itr++){
                follow[ch-'A'].insert(*itr);
            }
        }
    }

}

int main()
{
    //Initializing variables
    memset(visit,0,sizeof(visit));
    string grammar="";
    int NT;
    cout<<"Enter the number of non terminals : \n";
    cin>>NT;
    cout<<"In this Program the Starting Production is 'A' and Non Terminals are named in the increasing order, use space when there are multiple productions.\n";
    //Taking Input
    char c='A';
    for(int i=0;i<NT;i++)
    {
        int j;
        cout<<"Production for Non-Termninal "<<(char)(i+'A')<<":\n"; 
        grammar= grammar+c+" -> ";
        cout<<"Enter number of productions : ";
        cin>>j;
        cout<<"Enter production (# for epsilon) :";
        for(int k=0;k<j;k++)
        {
            string s;
            cin>>s;
            grammar+=s;
            if(k+1<j)
            grammar+="|";
            G[i].push_back(s);
        }
        grammar+="\n";
        c++;
    }
    //Calculating First of all Non Terminals
    for(int i=0;i<NT;i++)
    {
        calFirst(i);
    }

    //Display Grammar
    cout<<"Grammar: "<<'\n'<<grammar;


    //Display First of Non Terminals 
    cout<<"\n\n----- FIRST TABLE -----\n";
    for(int i=0;i<NT;i++){
            cout<<'\t'<<char(i+'A')<<"-> { ";
            int size = first[i].size();
            for(auto itr=first[i].begin();itr!=first[i].end();itr++)
            {
                cout<<(*itr);
                if(size>1)
                cout<<",";
                size--;
            }
            cout<<" }";
        cout<<"\n";
    }

    //Calculating Follow for all Non Terminals
     for(int i=0;i<NT;i++)
    {
        calFollow(i);
    }

    //Display Follow Table
    cout<<"\n\n----- FOLLOW TABLE -----\n";
    for(int i=0;i<NT;i++){
            cout<<'\t'<<char(i+'A')<<"-> { ";
            int size = follow[i].size();
            for(auto itr=follow[i].begin();itr!=follow[i].end();itr++)
            {
                cout<<(*itr);
                if(size>1)
                cout<<",";
                size--;
            }
            cout<<" }";
        cout<<"\n";
    }


    return 0;
}