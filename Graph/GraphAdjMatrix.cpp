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


//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	int ** matrix ; //adjacency matrix to store the graph
	int* color;
	int* parent;
	int* dist;//define other variables required for bfs such as color, parent, and dist
	int* discovery_time;
	int* finish_time;
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
	void dfs();
	void dfs_visit(int vertex);
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	matrix = 0 ;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;

	//allocate space for the matrix
    matrix = new int*[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0;j<nVertices;j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }

}

void Graph::addEdge(int u, int v)
{
    //write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    matrix[u][v] = 1;
    if(!directed) matrix[v][u] = 1;

}

void Graph::removeEdge(int u, int v)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    matrix[u][v] = 0;
    if(directed == false)
        matrix[v][u] = 0;
}

bool Graph::isEdge(int u, int v)
{
   if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;
   if(matrix[u][v] == 1)
        return true;
   return false;
}

int Graph::getDegree(int u)
{
    int counter = 0;
    for(int i=0 ; i<nVertices ; i++)
    {
        if(matrix[u][i] == 1)
            counter++;
    }
    return counter;
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    for(int i=0 ; i<nVertices ; i++)
        if(matrix[u][i] == 1 && matrix[v][i] == 1)
        return true;
    return false;

}

void Graph::bfs(int source)
{
    //complete this function
    //initialize BFS variables
	color = (int*)malloc(nVertices*sizeof(int));
	parent = (int*)malloc(nVertices*sizeof(int));
	dist = (int*)malloc(nVertices*sizeof(int));
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
        for(int i=0 ; i<nVertices ; i++)
        {
            if(!isEdge(u,i))
            continue;
            if(color[i] == WHITE)
            {
                color[i] = GRAY;
                parent[i] = u;
                dist[i] = dist[u] + 1;
                q.enqueue(i);
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

    for(int i=0 ; i<nVertices ; i++)
    {
        if(!isEdge(vertex,i))
            continue;
        int child = i;
        if(color[child] == WHITE)
        {
             parent[child] = vertex;
             dfs_visit(child);
        }
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
    bfs(u);
    return dist[v];
    return INFINITY ;
}


void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<nVertices;j++)
        {
            if(matrix[i][j]==1)
                printf(" %d", j);
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    if(matrix)
    {
        for(int i=0 ; i<nVertices; i++)
            free(matrix[i]);
    }
    free(matrix);
    if(color) delete[] color;
    if(parent) delete[] parent;
    if(dist) delete[] dist;
    if(discovery_time) delete[] discovery_time;
    if(finish_time) delete[] finish_time;

    matrix = NULL;
    color = NULL;
    parent = NULL;
    dist = NULL;
    discovery_time = NULL;
    finish_time = NULL;    //write your destructor here
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
        printf("6. Run BFS.\n7. Show distance.\n8. Run DFS.\n");
        printf("9. Print graph.\n10. Exit.\n");

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
            int u, v;
            scanf("%d%d", &u, &v);
            g.removeEdge(u,v);
        }
        else if(ch==3)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            if(g.isEdge(u,v) == true)  cout<<"Exists."<<endl;
            else cout<<"Does not exist."<<endl;
        }
        else if(ch==4)
        {
            int u;
            scanf("%d",&u);
            cout<<g.getDegree(u)<<endl;
        }
        else if(ch==5)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            if(g.hasCommonAdjacent(u,v) == true)
                cout<<"Has."<<endl;
            else
                cout<<"Does not have."<<endl;
        }
        else if(ch==6)
        {
            int source;
            cin>>source;
            g.bfs(source);
        }
        else if(ch==7)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            cout<<g.getDist(u,v)<<endl;
        }
        else if(ch==8)
        {
            g.dfs();
        }
        else if(ch==9)
        {
            g.printGraph();
        }
        else if(ch==10)
        {
            break;
        }
    }

}
