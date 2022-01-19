#include<stdio.h>
#include<cstring>
#include<iostream>

using namespace std;

void print_LCS(char sign_arr[][100],string S,int ai,int je)
{
    if(ai==0 || je==0)
        return;
    if(sign_arr[ai][je] == 'c')
    {
        print_LCS(sign_arr,S,ai-1,je-1);
        //cout<<ai<<je;
        cout<<S[ai-1];
    }

    else if(sign_arr[ai][je] == 'u')
        print_LCS(sign_arr,S,ai-1,je);
    else
        print_LCS(sign_arr,S,ai,je-1);

}

void longest_common_subsequence(string S,string T,int size_S,int size_T)
{
    int m = size_S;
    int n = size_T;
    int LCS[m+1][n+1];

    int i,j;
    char b[m][100];

    for(int k=0 ; k<=m ; k++)
        LCS[k][0] = 0;
    for(int l=0 ; l<=n ; l++)
        LCS[0][l] = 0;
    for(i=1 ; i<=m ; i++)
    {
        for(j=1 ; j<=n ; j++)
        {
            if(S[i-1] == T[j-1])
            {
                LCS[i][j] = LCS[i-1][j-1] + 1;
                b[i][j] = 'c';
            }
            else
            {
                if(LCS[i-1][j] >= LCS[i][j-1])
                {
                    LCS[i][j] = LCS[i-1][j];
                    b[i][j] = 'u';
                }
                else
                {
                    LCS[i][j] = LCS[i][j-1];
                    b[i][j] = 'l';
                }
            }
        }
    }


    print_LCS(b,S,m,n);

    cout<<" "<<endl;
    cout<<LCS[m][n]<<endl;
}

int main()
{
    string a,b;
    cin>>a;
    cin>>b;

    longest_common_subsequence(a,b,a.size(),b.size());
}
