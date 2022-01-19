#include<stdio.h>
#include<iostream>

#define INFINITY 9999999999

using namespace std;

int matrix_chain(int p[],int p_size)
{
    int m[p_size][p_size];

    int n = p_size - 1;

    int i,j,chain_length,k;

    int cost = 0;

    for(int now=1 ; now<=n ; now++)
    {
        m[now][now] = 0;
    }

    for(chain_length=2 ; chain_length<=n ; chain_length++)
    {
        int temp = n-chain_length+1;
        for(i=1 ; i<=temp ; i++)
        {
            j = i+chain_length-1;
            m[i][j] = INFINITY;
            for(k=i ; k<=j-1 ; k++)
            {
                cost = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if(cost < m[i][j])
                    m[i][j] = cost;
            }
        }
    }

    return m[1][n];
}

int main()
{
    int number,then;
    cin>>number;
    int arr[number];
    for(int b=0 ; b<number ; b++)
    {
        cin>>then;
        arr[b] = then;
    }

    printf("%d",matrix_chain(arr,number));
}
