#include<stdio.h>
#include<iostream>

using namespace std;

class object
{
    int id;
    int weight;
    int value;
    int value_by_weight;

public:
    object()  {id=0; weight=0; value=0; value_by_weight=0;}
    void set_values(int i,int w,int v,int v_b_w)  {id=i; weight=w; value=v; value_by_weight=v_b_w;}
    int get_val_by_wgt()  {return value_by_weight;}
    int get_weight()  {return weight;}
    int get_value()  {return value;}
    int get_id()  {return id;}
};

int main()
{
    int number,capacity,val,wgt;
    cin>>number;
    cin>>capacity;

    object* the_set;
    the_set = new object[number];

    for(int i=0 ; i<number ; i++)
    {
        cin>>wgt;
        cin>>val;
        the_set[i].set_values(i,wgt,val,(val/wgt));
    }

    object* the_sorted_set;
    the_sorted_set = new object[number];
    the_sorted_set = the_set;

    for(int l=0 ; l<number ; l++)
    {
        for(int k=0 ; k<number-1 ; k++)
        {
            if(the_sorted_set[k].get_val_by_wgt() < the_sorted_set[k+1].get_val_by_wgt())
            {
                object temp = the_sorted_set[k];
                the_sorted_set[k] = the_sorted_set[k+1];
                the_sorted_set[k+1] = temp;
            }
        }
    }

    int sum = 0;
    int j;

    for(j=0 ; j<number ; j++)
    {
        if(the_sorted_set[j].get_weight() < capacity)
        {
            cout<<the_sorted_set[j].get_id() + 1<<" ";
            cout<<the_sorted_set[j].get_weight()<<" ";
            cout<<the_sorted_set[j].get_value()<<" ";
            sum = sum + the_sorted_set[j].get_value();
            capacity = capacity - the_sorted_set[j].get_weight();
            printf("\n");
        }
        else
        {
            cout<<the_sorted_set[j].get_id() + 1<<" ";
            cout<<capacity<<" ";
            cout<<the_sorted_set[j].get_val_by_wgt()*capacity<<" ";
            sum = sum + the_sorted_set[j].get_val_by_wgt()*capacity;
            printf("\n");

            break;
        }

    }

    printf("\n");
    cout<<sum<<endl;
}
