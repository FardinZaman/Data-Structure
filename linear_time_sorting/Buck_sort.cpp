#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

double* Buck_Sort(double arr[] , int arr_size)
{
    vector<double> carrier[5];

    /*for(int i=0 ; i<arr_size ; i++)
        carrier[i] = NULL;*/

    for(int j=0 ; j<arr_size ; j++)
    {
        int index = 5*arr[j];
        carrier[index].push_back(arr[j]);
    }

    for(int k=0 ; k<5 ; k++)
    {
        sort(carrier[k].begin(),carrier[k].end());
    }

    double* sorted = new double[arr_size];
    int now = 0;
    for(int l=0 ; l<5 ; l++)
    {
        if(!carrier[l].empty())
        {
            for(int m=0 ; m<carrier[l].size() ; m++)
            {
                sorted[now] = carrier[l].at(m);
                now++;
            }
        }
    }

    return sorted;
}

void execution_Buck_Sort(double arr[] , int arr_size)
{

    double minimum_now = arr[0];
    for(int i=1 ; i<arr_size ; i++)
    {
        if(arr[i] < minimum_now)
            minimum_now = arr[i];
    }

    double arr_minus_minimum[arr_size];
    for(int l=0 ; l<arr_size ; l++)
    {
        arr_minus_minimum[l] = arr[l] - minimum_now;
    }

    double maximum = arr_minus_minimum[0];
    for(int k=1 ; k<arr_size ; k++)
    {
        if(arr_minus_minimum[k] > maximum)
            maximum = arr_minus_minimum[k];
    }

    //cout<<maximum<<endl;
    double amm_divided_by_max[arr_size];
    for(int j=0 ; j<arr_size ; j++)
    {
        amm_divided_by_max[j] = arr_minus_minimum[j]/(maximum*2 + 1);
            //cout<<arr_divided_by_max[j]<<endl;
    }
    //cout<<minimum<<endl;



    double* sorted = new double[arr_size];
    sorted = Buck_Sort(amm_divided_by_max , arr_size);

    double sorted_multi_max[arr_size];
    for(int m=0 ; m<arr_size ; m++)
    {
        sorted_multi_max[m] = sorted[m] * (maximum*2 + 1);
    }

    double sorted_finally[arr_size];
    for(int n=0 ; n<arr_size ; n++)
    {
        sorted_finally[n] = sorted_multi_max[n] + minimum_now;
    }

    for(int o=0 ; o<arr_size ; o++)
    {
        cout<<sorted_finally[o]<<" ";
    }
    cout<<endl;
}


int main()
{
    int n;
    cin>>n;
    double arr[n];
    for(int now=0 ; now<n ; now++)
    {
        double temp;
        cin>>temp;
        arr[now] = temp;
    }

    execution_Buck_Sort(arr , n);
}
