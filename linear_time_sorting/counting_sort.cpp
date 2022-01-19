#include<stdio.h>
#include<iostream>

using namespace std;

void Counting_Sort(int arr[] , int arr_length)
{
    int maximum = arr[0];
    for(int i=1 ; i<arr_length ; i++)
    {
        if(arr[i] > maximum)
            maximum = arr[i];
    }
    //cout<<maximum;

    int minimum = arr[0];
    for(int i=1 ; i<arr_length ; i++)
    {
        if(arr[i] < minimum)
            minimum = arr[i];
    }
    //cout<<minimum;

    int temp_arr_length = maximum - minimum + 1;
    int temp_arr[temp_arr_length];
    int sorted_arr[arr_length + 1];

    for(int j=0 ; j<temp_arr_length ; j++)
    {
        temp_arr[j] = 0;
    }

    for(int k=0 ; k<arr_length ; k++)
    {
        temp_arr[arr[k] - minimum]++;
    }

    for(int l=1 ; l<temp_arr_length ; l++)
    {
        temp_arr[l] = temp_arr[l] + temp_arr[l-1];
    }

    for(int m=arr_length-1 ; m>=0 ; m--)
    {
        sorted_arr[temp_arr[arr[m] - minimum]] = arr[m];
        temp_arr[arr[m] - minimum]--;
    }

    for(int out=1 ; out<arr_length+1 ; out++)
        cout<<sorted_arr[out]<<" ";
    cout<<"\n";
}

int main()
{
    int n;
    cin>>n;
    int the_arr[n];
    for(int in=0 ; in<n ; in++)
    {
        int temp;
        cin>>temp;
        the_arr[in] = temp;
    }

    Counting_Sort(the_arr,n);
}
