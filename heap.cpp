#include<stdio.h>
#include<iostream>

using namespace std;

class Max_Heap
{
    int heap_size;
    int* heap_arr;

public:
    Max_Heap()  {heap_size = 0;heap_arr = NULL;}
    void take_values(int arr[] , int length);
    int get_largest()  {return heap_arr[0];}
    int get_left_index(int index) {return index*2 +1;}
    int get_right_index(int index)  {return index*2 + 2;}
    int get_parent(int index)  {return (index-1)/2;}
    int get_size()  {return this->heap_size;}
    bool is_empty()  {return (heap_size==0);}
    void Build_Max_Heap();
    void Max_Heapify(int index);
    void just_insert(int number);
    void insert_key(int number);
    void delete_max();
    int extract_max();
    void replace_root(int number);
    void merge_heap(Max_Heap* first , Max_Heap* second);
    void meld_heap(Max_Heap* first , Max_Heap* second);
    void insert_and_sift_up(int number);
    void delete_item(int number);
    void display();
};

void Max_Heap::delete_item(int number)
{
    int index;
    for(index=0 ; index<this->heap_size ; index++)
    {
        if(this->heap_arr[index] == number)
            break;
    }
    int n = this->heap_size - 1;
    this->heap_arr[index] = this->heap_arr[n];

    this->heap_size--;

    int* temp = new int[this->heap_size];
    for(int i=0 ; i<this->heap_size ; i++)
    {
       temp[i] = this->heap_arr[i];
    }

    delete[] this->heap_arr;
    this->heap_arr = temp;
}

void Max_Heap::insert_and_sift_up(int number)
{
    this->just_insert(number);
    int child = this->heap_size - 1;
    int parent = get_parent(child);

    while(this->heap_arr[child] > this->heap_arr[parent])
    {
        int temp;
        temp = this->heap_arr[child];
        this->heap_arr[child] = this->heap_arr[parent];
        this->heap_arr[parent] = temp;

        child = parent;
        parent = get_parent(child);
    }
}

void Max_Heap::merge_heap(Max_Heap* first , Max_Heap* second)
{
    this->heap_size = first->heap_size + second->heap_size;
    int temp[this->heap_size];
    int i;
    for(i=0 ; i<first->heap_size ; i++)
        temp[i] = first->heap_arr[i];

    for(int j=0 ; j<second->heap_size ; j++)
    {
        temp[i] = second->heap_arr[j];
        i++;
    }

    this->take_values(temp,this->heap_size);
}

void Max_Heap::meld_heap(Max_Heap* first , Max_Heap* second)
{
    this->merge_heap(first , second);

    first->heap_arr = NULL;
    delete[] first;
    second->heap_arr = NULL;
    delete[] second;
}

void Max_Heap::replace_root(int number)
{
    this->delete_max();
    this->insert_key(number);
}

int Max_Heap::extract_max()
{
    int root = this->heap_arr[0];
    this->delete_max();
    return root;
}

void Max_Heap::delete_max()
{
    int* temp = new int[heap_size-1];
    temp[0] = this->heap_arr[heap_size-1];
    for(int i=1 ; i<this->heap_size-1 ; i++)
        temp[i] = this->heap_arr[i];

    delete[] this->heap_arr;
    this->heap_arr = temp;

    this->heap_size--;

    this->Max_Heapify(0);
}

void Max_Heap::just_insert(int number)
{
    int* temp = new int[this->heap_size+1];
    for(int i=0 ; i<this->heap_size ; i++)
        temp[i] = this->heap_arr[i];
    temp[heap_size] = number;
    delete[] this->heap_arr;
    this->heap_arr = temp;
    this->heap_size++;
}

void Max_Heap::insert_key(int number)
{
    this->just_insert(number);

    this->Build_Max_Heap();
}

void Max_Heap::take_values(int arr[] , int length)
{
    this->heap_size = length;
    this->heap_arr = new int[length];

    for(int i=0 ; i<length ; i++)
        heap_arr[i] = arr[i];

    this->Build_Max_Heap();
}

void Max_Heap::Build_Max_Heap()
{
    int n = this->heap_size-1;
    for(int i=n/2 ; i>=0 ; i--)
    {
        this->Max_Heapify(i);
    }
}

void Max_Heap::Max_Heapify(int index)
{
    int left = this->get_left_index(index);
    int right = this->get_right_index(index);

    int maximum = 0;

    if(left<=this->heap_size-1 && this->heap_arr[left]>this->heap_arr[index])
        maximum = left;
    else
        maximum = index;

    if(right<=this->heap_size-1 && this->heap_arr[right]>this->heap_arr[maximum])
        maximum = right;

    if(maximum != index)
    {
        int temp;
        temp = this->heap_arr[index];
        this->heap_arr[index] = this->heap_arr[maximum];
        this->heap_arr[maximum] = temp;

        this->Max_Heapify(maximum);
    }
}

void Max_Heap::display()
{
    for(int i=0 ; i<this->heap_size ; i++)
        cout<<this->heap_arr[i]<<" ";

    cout<<"\n"<<endl;
}

int main()
{
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    int b[10] = {11,12,13,14,15,16,17,18,19,20};
    Max_Heap* m1 = new Max_Heap();
    m1->take_values(a,10);
    m1->display();

    Max_Heap* m2 = new Max_Heap();
    Max_Heap m3;
    m2->take_values(b,10);
    m2->display();
    m3.meld_heap(m1,m2);
    m3.display();


    m3.delete_item(10);
    m3.display();
}
