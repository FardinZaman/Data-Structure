#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GRAY 2
#define BLACK 3

using namespace std;

int time = 0;

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
	if (length == queueMaxSize)
	{
		int * tempData ;
		//allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new int[queueMaxSize] ;
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


int Queue::dequeue()
{
	if(length == 0) return NULL_VALUE ;
	int item = data[rear] ;
	rear = (rear + 1) % queueMaxSize ;
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************

//****************Dynamic ArrayList class based************************
class ArrayList
{
	int * list;
	int length ;
	int listMaxSize ;
	int listInitSize ;
public:
	ArrayList() ;
	~ArrayList() ;
	int searchItem(int item) ;
    void insertItem(int item) ;
	void removeItem(int item) ;
	void removeItemAt(int position);
	int getItem(int position) ;
	int getLength();
	bool empty();
	void printList();
} ;


ArrayList::ArrayList()
{
	listInitSize = 2 ;
	listMaxSize = listInitSize ;
	list = new int[listMaxSize] ;
	length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
	int * tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;
		tempList = new int[listMaxSize] ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length] = newitem ; //store new item
	length++ ;
}

int ArrayList::searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
	if ( position < 0 || position >= length ) return ; //nothing to remove
	list[position] = list[length-1] ;
	length-- ;
}


void ArrayList::removeItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return ; //nothing to remove
	removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
	if(position < 0 || position >= length) return NULL_VALUE ;
	return list[position] ;
}

int ArrayList::getLength()
{
	return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

//******************ArrayList class ends here*************************


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
//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	ArrayList  * adjList ;
	int* color;
	int* parent;
	int* dist;
	int* discovery_time;
	int* finish_time;
	 //define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation

public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source); //will run bfs in the graph
	void dfs(); //will run dfs in the graph
	void dfs_visit(int vertex);
	void dfs_using_stack(int source);
	void print_dfs_time(int vertex);
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	directed = dir ;//set direction of the graph
	color = NULL;
	parent = NULL;
	dist = NULL;
	//define other variables to be initialized
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;
	if(adjList!=0) delete[] adjList ; //delete previous list
	adjList = new ArrayList[nVertices] ;
}

void Graph::addEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    this->nEdges++ ;
	adjList[u].insertItem(v) ;
	if(!directed) adjList[v].insertItem(u) ;
}

void Graph::removeEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return;
    this->nEdges--;
    adjList[u].removeItem(v);
    if(directed == false)
        adjList[v].removeItem(u);
}

bool Graph::isEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>= nVertices) return false;
    if(adjList[u].searchItem(v) != NULL_VALUE)
        return true;
    return false;
}

int Graph::getDegree(int u)
{
    if(u<0 || u>=nVertices) return NULL_VALUE;
    int degree = adjList[u].getLength();
    if(adjList[u].searchItem(u) != NULL_VALUE)
        degree++;
    return degree;
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    for(int i=0 ; i<adjList[u].getLength() ; i++)
    {
        if(adjList[v].searchItem(adjList[u].getItem(i)) != NULL_VALUE)
            return true;
    }
    return false;

}

void Graph::bfs(int source)
{
    //complete this function
	color = (int*)malloc(nVertices*sizeof(int));
	parent = (int*)malloc(nVertices*sizeof(int));
	dist = (int*)malloc(nVertices*sizeof(int));    //initialize BFS variables
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;
    }
    Queue q ;
    color[source] = GRAY;
    dist[source] = 0 ;
    parent[source] = NULL;
    q.enqueue(source) ;
    while( !q.empty() )
    {
        int u = q.dequeue();
        for(int i=0 ; i<adjList[u].getLength() ; i++)
        {
            int v = adjList[u].getItem(i);
            if(color[v] == WHITE)
            {
                color[v] = GRAY;
                parent[v] = u;
                dist[v] = dist[u] + 1;
                q.enqueue(v);
            }

        }
        color[u] = BLACK;
        cout<<u<<"->";
    }
    printf("\n");
}

void Graph::dfs_visit(int vertex)
{
    time = time+1;
    discovery_time[vertex] = time;
    color[vertex] = GRAY;

    cout<<vertex<<"->";

    for(int i=0 ; i<adjList[vertex].getLength() ; i++)
    {
        int child = adjList[vertex].getItem(i);
        if(color[child] != WHITE)
        {
             continue;
        }
        parent[child] = vertex;
        dfs_visit(child);
    }

    color[vertex] = BLACK;
    time = time+1;
    finish_time[vertex] = time;

    //cout<<vertex<<"->";
}

void Graph::dfs()
{
    color = (int*)malloc(nVertices*sizeof(int));
	parent = (int*)malloc(nVertices*sizeof(int));
    discovery_time = new int[nVertices];
    finish_time = new int[nVertices];
    for(int i=0 ; i<nVertices ; i++)
    {
        color[i] = WHITE;
        parent[i] = NULL;
    }
    for(int k=0 ; k<nVertices ; k++)
    {
        if(color[k]==WHITE)
        {
            dfs_visit(k);
        }
    }
    printf("\n");
}

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return INFINITY ;
    bfs(u);
    return dist[v];

}

void Graph::dfs_using_stack(int source)
{
	color = (int*)malloc(nVertices*sizeof(int));
	parent = (int*)malloc(nVertices*sizeof(int));
	discovery_time = new int[nVertices];
	finish_time = new int[nVertices];

    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = NULL ;
    }
    Stack s ;
    color[source] = GRAY;
    parent[source] = NULL;
    s.push(source) ;
    while( !s.empty() )
    {
        int u = s.pop();
        time = time + 1;
        discovery_time[u] = time;
        for(int i=0 ; i<adjList[u].getLength() ; i++)
        {
            int v = adjList[u].getItem(i);
            if(color[v] == WHITE)
            {
                color[v] = GRAY;
                parent[v] = u;
                s.push(v);
            }

        }
        color[u] = BLACK;
        time = time + 1;
        finish_time[u] = time;
        cout<<u<<"->";
    }
    printf("\n");
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
}

void Graph::print_dfs_time(int vertex)
{
    cout<<finish_time[vertex]-discovery_time[vertex]<<endl;
}

Graph::~Graph()
{
    if(adjList)  delete[] adjList;
    if(color) delete[] color;
    if(parent) delete[] parent;
    if(dist) delete[] dist;
    if(discovery_time) delete[] discovery_time;
    if(finish_time) delete[] finish_time;

    adjList = NULL;
    color = NULL;
    parent = NULL;
    dist = NULL;
    discovery_time = NULL;
    finish_time = NULL;
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    int n;
    Graph g;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while(1)
    {
        printf("1. Add edge.\n2. Delete edge.\n3. Is edge exist?\n");
        printf("4. Show degree.\n5. Has common adjacent?\n");
        printf("6. Run BFS.\n7. Show distance.\n8. Run DFS.\n9. Run DFS using STACK.\n");
        printf("10. Print graph.\n11. Exit\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.addEdge(u, v);
        }
        else if(ch==2)
        {
            int u,v;
            cin>>u;
            cin>>v;
            g.removeEdge(u,v);
        }
        else if(ch==3)
        {
            int u,v;
            cin>>u;
            cin>>v;
            if(g.isEdge(u,v) == true)  cout<<"Exists"<<endl;
            else cout<<"Does not exist"<<endl;
        }
        else if(ch==4)
        {
            int input;
            cin>>input;
            cout<<g.getDegree(input)<<endl;
        }
        else if(ch==5)
        {
            int u;
            int v;
            cin>>u;
            cin>>v;
            if(g.hasCommonAdjacent(u,v) == true)  cout<<"Has"<<endl;
            else cout<<"Does not have"<<endl;
        }
        else if(ch==6)
        {
            int source;
            cin>>source;
            g.bfs(source);
        }
        else if(ch==7)
        {
            int source,destination;
            cin>>source;
            cin>>destination;
            cout<<g.getDist(source,destination)<<endl;
        }
        else if(ch==10)
        {
            g.printGraph();
        }
        else if(ch==11)
        {
            break;
        }
        else if(ch==8)
        {
            g.dfs();
        }
        else if(ch==9)
        {
            g.dfs_using_stack(0);
        }
        else if(ch==12)
        {
            g.dfs();
            g.print_dfs_time(2);
            g.dfs_using_stack(0);
            g.print_dfs_time(2);
        }
    }

}
