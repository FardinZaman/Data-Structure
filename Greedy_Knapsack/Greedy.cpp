#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define NULL_VALUE -999999

using namespace std;


class Stack
{
    int top;
    int length;
    int* list;
    int stack_max_size;
public:
    Stack()
    {
        top = 0;
        length = 0;
        stack_max_size = 2;
        list = new int[stack_max_size];
    }

    void push(int item)
    {
        if(length == stack_max_size)
        {
            int* temp_list;
            stack_max_size = stack_max_size*2;
            temp_list = new int[stack_max_size];

            for(int i=0 ; i<length ; i++)
            {
                temp_list[i] = list[i];
            }
            delete[] list;
            list = temp_list;
        }
        top = length;
        list[length] = item;
        length++;
    }

    int pop()
    {
        if(length == 0)
            return NULL_VALUE;
        int now = list[top];
        top--;
        length--;
        return now;
    }

    bool empty()
    {
        if(length==0)
            return true;
        return false;
    }

};

class Nodes
{
    char alphabet;
    int frequency;
public:
    Stack S;
    Nodes* left_node;
    Nodes* right_node;

    Nodes()  {left_node = NULL;right_node = NULL;alphabet = NULL; frequency = 0;}
    void set_items(char c,int i)  {alphabet = c;frequency = i;}
    void set_only_freq(int i)  {alphabet = NULL; frequency = i;}
    int get_frequency() {return this->frequency;}
    char get_alphabet()  {return this->alphabet;}
};

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    Nodes * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    //~Queue();
    void enqueue(Nodes item); //insert item in the queue
    Nodes dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
    Nodes Extract_Min();
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new Nodes[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(Nodes item)
{
	if (length == queueMaxSize)
	{
		Nodes * tempData ;
		//allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new Nodes[queueMaxSize] ;
		int i, j;
		j = 0;
		for( i = rear; i < length ; i++ )
		{
			tempData[j++] = data[i] ; //copy items from rear
		}
		for( i = 0; i < rear ; i++ )
		{
			tempData[j++] = data[i] ; //copy items before rear
		}
		rear = 0 ;
		front = length ;
		delete[] data ; //free the memory allocated before
		data = tempData ; //make list to point to new memory
	}

	data[front] = item ; //store new item
	front = (front + 1) % queueMaxSize ;
	length++ ;
}


bool Queue::empty()
{
	if(length == 0) return true ;
	else return false ;
}


Nodes Queue::dequeue()
{
    Nodes null;
	if(length == 0) return null;
	Nodes item = data[rear] ;
	rear = (rear + 1) % queueMaxSize ;
	length-- ;
	return item ;
}

Nodes Queue::Extract_Min()
{
    int minimum,index=0;
    minimum = data[0].get_frequency();
    //cout<<data[0].get_alphabet();
    for(int i=1 ; i<length ; i++)
    {
        if(data[i].get_frequency() < minimum)
        {
            minimum = data[i].get_frequency();
            index = i;
        }
    }
    Nodes item;
    item = data[index];
    Nodes* tempData;
    tempData = new Nodes[length];
    int k, j;
    j = 0;
    for( k = 0; k < index ; k++ )
    {
        tempData[j++] = data[k] ; //copy items from rear
    }
    for(int l=index+1 ; l<length; l++)
    {
        tempData[j++] = data[l];
    }
    length--;
    front--;
    rear = 0;
    delete[] data;
    data = tempData;

    return item;
}

/*Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}*/

/*int use_stack(Nodes* head,int value)
{
    //cout<<head->get_alphabet();
    //cout<<head->left_node->get_alphabet();
    if(head->get_alphabet() != NULL)
    {
        if(value == 0)
            head->S.push(0);
        else
            head->S.push(1);

        return 1;
    }
    else
    {
        //cout<<head->left_node->get_alphabet();
        int a = use_stack(head->left_node,0);
        cout<<a;
        int b = use_stack(head->right_node,1);
        cout<<b;

        return 0;
    }
}*/

void print_code(Nodes* head,int array_got[],int length)
{
    cout<<head->right_node->left_node->get_frequency();
    if(head->left_node)
    {
        array_got[length] = 0;
        cout<<"1"<<endl;
        //length++;
        print_code(head->left_node,array_got,length+1);
    }
    if(head->right_node)
    {
        array_got[length] = 1;
        //cout<<"2"<<endl;
        //length++;
        print_code(head->right_node,array_got,length+1);

    }
    if(head->left_node == NULL && head->right_node == NULL)
    {
        cout<<head->get_alphabet()<<" ";
        for(int i=0 ; i<length ; i++)
        {
            cout<<array_got[i];
        }
    }
}

int* array_to_be_sent = new int[100];
int length = 0;

void Huffman(Nodes* main_set,int number)
{
    Queue Q;
    //cout<<main_set[0].get_alphabet();
    for(int i=0 ; i<number ; i++)
    {
        Nodes temp = main_set[i];
        //cout<<main_set[i].get_alphabet();
        Q.enqueue(temp);
    }

    Nodes* left;
    Nodes* right;
    Nodes sum;
    left = new Nodes();
    right = new Nodes();


    for(int j=1 ; j<number ; j++)
    {
        /*Nodes* left;
        Nodes* right;
        Nodes sum;
        left = new Nodes();
        right = new Nodes();*/

        Nodes left_temp = Q.Extract_Min();
        //cout<<left_temp.get_alphabet();
        Nodes right_temp = Q.Extract_Min();
        //cout<<right_temp.get_alphabet();

        left->set_items(left_temp.get_alphabet(),left_temp.get_frequency());
        right->set_items(right_temp.get_alphabet(),right_temp.get_frequency());

        sum.set_only_freq(left->get_frequency() + right->get_frequency());
        sum.left_node = left;
        sum.right_node = right;
        //cout<<sum.right_node->get_alphabet();
        //cout<<sum.right_node->left_node->get_frequency();
        Q.enqueue(sum);
    }
    cout<<sum.right_node->left_node->get_frequency();
    Nodes* root = new Nodes();
    Nodes root_temp = sum;
    cout<<root_temp.right_node->right_node->get_frequency();
    root->set_items(root_temp.get_alphabet(),root_temp.get_frequency());
    root->left_node = root_temp.left_node;
    root->right_node = root_temp.right_node;

    //cout<<root->right_node->right_node->get_alphabet();

    print_code(root,array_to_be_sent,length);
    //int nothing = use_stack(root,0);
}

int main()
{
    int n;
    scanf("%d",&n);
    getchar();
    Nodes* the_set;
    the_set = new Nodes[n];
    for(int i=0 ; i<n ; i++)
    {
        char alph;
        int freq ;
        scanf("%c",&alph);
        getchar();
        scanf("%d",&freq);
        getchar();
        the_set[i].set_items(alph,freq);
        //the_set[i].left_node = NULL;
        //the_set[i].right_node = NULL;
    }
    //printf("%d",the_set[1].get_frequency());
    Huffman(the_set,n);
    //printf("%d",the_set[1].get_frequency());
}
