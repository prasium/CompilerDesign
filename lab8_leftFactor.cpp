#include<bits/stdc++.h>

using namespace std;

//Find Longest Common Prefix
string commonPrefixUtil(string str1, string str2) 
{ 
    string result; 
    int n1 = str1.length(), n2 = str2.length(); 
    for (int i=0, j=0; i<=n1-1&&j<=n2-1; i++,j++) 
    { 
        if (str1[i] != str2[j]) 
            break; 
        result.push_back(str1[i]); 
    } 
    return (result); 
} 

string commonPrefix (vector<string> arr, int n) 
{ 
    string prefix =  arr[0]; 
    for (int i=1; i<=n-1; i++) 
        prefix = commonPrefixUtil(prefix, arr[i]); 
    return (prefix); 
} 

int main()
{
    int n;
    char NT;
    cout<<"Enter Non-Terminal:";
    cin>>NT;
    cout<<"Enter Number of Productions of "<<NT<<":";
    cin>>n;
    vector<string> prod(n);
    string production;
    production.append(1,NT);
    production+="-> ";
    for(int i=0;i<n;i++)
    {
        cout<<"Production "<<i+1<<":";
        cin>>prod[i];
        production+=prod[i];
        if(i+1<n)
        production+="| ";
    }
    cout<<"Production is :\n"<<production;
    cout<<"\nLeft Factored Production is :\n";
    map <char,vector<string>> mp;    
    for(int i=0;i<n;i++)
    {
        mp[prod[i][0]].push_back(prod[i]);
    }

    char c='A';
    for(auto i=mp.begin();i!=mp.end();i++)
    {
        cout<<NT<<"-> ";
        string compre = commonPrefix(i->second,i->second.size());
        if(i->second.size()==1)
        cout<<compre;
        else
        {
        cout<<compre<<c<<"\'";
        cout<<"\n"<<c<<"\' -> ";
        }
        for(int j=0;j<i->second.size();j++)
        {
            string temp=i->second[j].substr(compre.size());
            if(temp.empty())
            cout<<"#";
            else
            cout<<temp;
               if(j+1<(i->second.size()))
                    cout<<"|";
        }
        cout<<"\n";    
        c++;
    }
    cout<<"# represents Epsilon";
    return 0;

}