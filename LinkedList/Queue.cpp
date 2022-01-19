#include<stdio.h>
#include<stdlib.h>
#include"LinkedListWithTail.cpp"


#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

class Queue
{
    LinkedListWithTail ll;
public:
    Queue()
    {
        ll.length = 0;
        ll.list = NULL;
        ll.tail = NULL;
    }

    void enqueue(int item)
    {
        ll.insertItem(item);
    }

    int dequeue()
    {
        return ll.deleteLast();
    }
};

int main(void)
{
    Queue qu;

    while(1)
    {
        printf("1. Enque. 2. Deque. 3. Exit. \n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            qu.enqueue(item);
        }
        else if(ch==2)
        {
            int item=qu.dequeue();
            printf("%d\n",item);
        }
        else if(ch==3)
        {
            break;
        }
    }

}

