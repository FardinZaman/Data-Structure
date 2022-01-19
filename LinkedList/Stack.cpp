#include<stdio.h>
#include<stdlib.h>
#include"LinkedList.cpp"


#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

class Stack
{
    LinkedList ll;
public:
    Stack()
    {
        ll.length = 0;
        ll.list = NULL;
    }
    void push(int item)
    {
        ll.insertItem(item);
    }
    int pop()
    {
        return ll.deleteFirst();
    }
};

int main()
{
    Stack st;

    while(1)
    {
        printf("1. Push. 2. Pop. 3. Exit. \n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            st.push(item);

        }
        else if(ch==2)
        {
            int item=st.pop();
            printf("%d\n",item);
        }
        else if(ch==3)
        {
            break;
        }
    }

}
