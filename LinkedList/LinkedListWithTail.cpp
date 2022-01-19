#include<stdio.h>
#include<stdlib.h>


#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

class ListNode
{
public:
    int item;
    ListNode * next;
};

class LinkedListWithTail
{
public:
    ListNode * list;
    ListNode * tail;
    int length;

public:
    LinkedListWithTail()
    {
        list = 0;  //initially set to NULL
        tail = 0;
        length=0;
    }

    int getLength()
    {
        return length;
    }

    //add required codes to set up tail pointer
    int insertItem(int item) //insert at the beginning
    {
        ListNode * newNode ;
        newNode = new ListNode() ;
        newNode->item = item ;
        if(list==NULL)
            tail = newNode;
        newNode->next = list ; //point to previous first node
        list = newNode ; //set list to point to newnode as this is now the first node
        length++;
        return SUCCESS_VALUE ;
    }

    //add required codes to set up tail pointer
    int deleteItem(int item)
    {
        ListNode *temp, *prev ;
        temp = list ; //start at the beginning
        prev = NULL;
        while (temp != 0)
        {
            if (temp->item == item) break ;
            prev = temp;
            temp = temp->next ; //move to next node
        }
        if (temp == 0) return NULL_VALUE ;//item not found to delete
        if (tail == temp)
            tail = prev;
        if (temp == list) //delete the first node
        {
            list = list->next ;
            delete temp ;
            length--;
        }
        else
        {
            prev->next = temp->next ;
            delete temp;
            length--;
        }
        return SUCCESS_VALUE ;
    }

    //add required codes to set up tail pointer
    ListNode * searchItem(int item)
    {
        ListNode * temp ;
        temp = list ; //start at the beginning
        while (temp != 0)
        {
            if (temp->item == item) return temp ;
            temp = temp->next ; //move to next node
        }
        return 0 ; //0 means invalid pointer in C, also called NULL value in C
    }

    void printList()
    {
        ListNode * temp;
        temp = list;
        while(temp!=0)
        {
            printf("%d->", temp->item);
            temp = temp->next;
        }
        printf("\n");
        printf("Length: %d\n",getLength());
    }

    //------------write code for the functions below-----------
    int insertLast(int item)
    {
        ListNode* newNode = new ListNode();
        newNode->item = item;
        if(tail != NULL)
        {
            tail->next = newNode;
            tail = newNode;
            newNode->next = NULL;
            length++;
            return SUCCESS_VALUE;
        }
        /*tail = newNode;
        list = newNode;
        newNode->next = NULL;*/
        return NULL_VALUE;

    }

    ListNode * getItemAt(int pos)
    {
         if(pos==length)
            return tail;
         if(pos<length)
         {
             ListNode* temp;
             temp = list;
             for(int i = 1;i<pos;i++)
                temp = temp->next;
             return temp;
         }
         return NULL;

    }

    int deleteLast()
    {
        if(tail!=NULL){
                ListNode* temp = list;
                ListNode* prev = NULL;
                while(temp != tail)
                {
                     prev = temp;
                     temp = temp->next;
                }
        tail = prev;
        if(prev!=NULL){
            prev->next = NULL;
        }
        if(prev==NULL)
        {
            list = NULL;
        }
        int lastNumber = temp->item;
        delete temp;

        length--;
        return lastNumber;
        }
        return NULL_VALUE;

    }
};

/*int main(void)
{
    LinkedListWithTail ll;

    while(1)
    {
        printf("1. Insert new item. 2. Delete item. 3. Search item. \n");
        printf("4. Insert item at last. 5. Delete last item. \n");
        printf("6. Get an item from a position. 7. Print. 8. Exit \n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            ll.insertItem(item);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            ll.deleteItem(item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            ListNode * res = ll.searchItem(item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==7)
        {
            ll.printList();
        }
        else if(ch==8)
        {
            break;
        }
        else if(ch==4)
        {
            int item;
            scanf("%d",&item);
            ll.insertLast(item);
        }
        else if(ch==5)
        {
            ll.deleteLast();
            printf("Deleted\n");
        }
        else if(ch==6)
        {
            int pos;
            scanf("%d",&pos);
            ListNode* temp = ll.getItemAt(pos);
            if(temp!=NULL)
                printf("%d\n",temp->item);
            else
                printf("Not found \n");
        }
    }

}*/
