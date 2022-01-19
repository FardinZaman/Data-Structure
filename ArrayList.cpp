#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>

using namespace std;

#define LIST_INIT_SIZE 2
#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

int listMaxSize;
int * list;
int length;
int opPre;
int opPost;


void initializeList()
{
	listMaxSize = LIST_INIT_SIZE;
	list = (int*)malloc(sizeof(int)*listMaxSize) ;
	length = 0 ;
}

int getLength()
{
    return length;
}

int searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

int insertItem(int newitem)
{
    if(list == NULL)
        initializeList();

	int * tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;
		tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        free(list) ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length] = newitem ; //store new item
	length++ ;
	return SUCCESS_VALUE ;
}

int insertItemAt(int pos,int newItem)
{
    if(pos >= length)
        return NULL_VALUE;

    if(length == listMaxSize)
    {
        int* tempList;
        listMaxSize = listMaxSize*2;
        tempList = (int*)malloc(sizeof(int)*listMaxSize);
        for(int i = 0; i<length; i++)
        {
            tempList[i] = list[i];
        }
        free(list);
        list = tempList;
    }

    /*for(int i = length; i>=pos; i--)
    {
        list[i+1] = list[i];
    }*/

    int temp = list[pos];
    list[pos] = newItem;
    list[length] = temp;
    length++;
    return SUCCESS_VALUE;
}

int shrink()
{
    if(listMaxSize = LIST_INIT_SIZE)
        return NULL_VALUE;

    if(length = (listMaxSize/2))
    {
        int* tempList;
        listMaxSize = listMaxSize/2;
        tempList = (int*)malloc(sizeof(int)*listMaxSize);
        for(int i = 0; i<length; i++)
        {
            tempList[i] = list[i];
        }
        free(list);
        list = tempList;
        return SUCCESS_VALUE;
    }

    return NULL_VALUE;
}

int deleteItemAtOrder(int position)
{
    if (position >= length) return NULL_VALUE;
    for(int i = position; i<length; i++)
        list[i] = list[i+1];
    length--;

    shrink();

    return SUCCESS_VALUE;
}

int deleteItemAt(int position) //version 2, do not preserve order of items
{
	if ( position >= length ) return NULL_VALUE;
	list[position] = list[length-1] ;
	length-- ;

	shrink();

	return SUCCESS_VALUE ;
}


int deleteItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return NULL_VALUE;
	deleteItemAt(position) ;

	return SUCCESS_VALUE ;
}

void deleteItemLast()
{
    int* tempList;
    tempList = (int*)malloc(sizeof(int)*listMaxSize);
    for(int i = 0; i<length-1; i++)
    {
        tempList[i] = list[i];
    }
    free(list);
    list = tempList;
    length--;

    shrink();
}

void deleteAll()
{
    for(int i = 0; i<length; i++)
    {
        list[i] = NULL;
    }
    length = 0;
    listMaxSize = LIST_INIT_SIZE;
}

void clearList()
{
    deleteAll();
    free(list);
}

void printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

int main(void)
{
    initializeList();

    while(1)
    {
        printf("1. Insert new item.\n2. Insert new item at.\n3. Delete item at.\n");
        printf("4. Delete item.\n5. Print.\n6. Clear list.\n7. Exit\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            cout<<"Enter A New Item : "<<endl;
            scanf("%d", &item);
            insertItem(item);
        }
        else if(ch==2)
        {
            int pos;
            int item;
            cout<<"Enter The Position : "<<endl;
            cin>>pos;
            cout<<"Enter The Item : "<<endl;
            cin>>item;
            insertItemAt(pos,item);
        }
        else if(ch==3)
        {
            int pos;
            cout<<"Enter The Position : "<<endl;
            scanf("%d", &pos);
            deleteItemAt(pos);
        }
        else if(ch==4)
        {
            int item;
            cout<<"Enter The Item : "<<endl;
            scanf("%d", &item);
            deleteItem(item);
        }
        else if(ch==5)
        {
            printList();
        }
        else if(ch==7)
        {
            break;
        }
        else if(ch==6){
            clearList();
        }
    }

}

/*   void deleteDouble()
   {
       opPost = list[length-1];
       opPre = list[length-2];
       deleteItemLast();
       deleteItemLast();
   }

int main()
{
   string s;
   getline(cin,s);

   for(int i = 0; i<s.length(); i++)
   {
       if(isdigit(s[i]))
       {
           int temp = (int)(s[i]-48);
           insertItem(temp);
       }
       else{

           if(s[i] == '+')
           {
               deleteDouble();
               insertItem(opPre+opPost);
           }

           if(s[i] == '-')
           {
               deleteDouble();
               insertItem(opPre-opPost);
           }

           if(s[i] == '*')
           {
               deleteDouble();
               insertItem(opPre*opPost);
           }

           if(s[i] == '/')
           {
               deleteDouble();
               insertItem(opPre/opPost);
           }
       }
   }

   cout<<"The evaluated result : "<<list[0]<<endl;
   clearList();

}
*/
