#include <stdio.h>
#include <stdlib.h>

int scan(){
    int t=0;
    char c;
    c=getchar();
    while(c<'0' || c>'9')
    c=getchar();
    while(c>='0' && c<='9') {
        t=(t<<3)+(t<<1)+c-'0';
        c=getchar();
    }
    return(t);
}
 
// A structure to represent an adjacency list node
struct AdjListNode
{
    int dest;
    struct AdjListNode* next;
};
 
// A structure to represent an adjacency list
struct AdjList
{
    struct AdjListNode *head;  // pointer to head node of list
};
 
// A structure to represent a graph. A graph is an array of adjacency lists.
// Size of array will be V (number of vertices in graph)
struct Graph
{
    int V;
    struct AdjList* array;
};
 
// A utility function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest)
{
    struct AdjListNode* newNode =(struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    if(!newNode)
        return NULL;
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}
 
// A utility function that creates a graph of V vertices
struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    if(!graph)
        return NULL;
    graph->V = V;
 
    // Create an array of adjacency lists.  Size of array will be V
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
    if(!(graph->array))
        return NULL;

    // Initialize each adjacency list as empty by making head as NULL
    int i;
    for (i = 0; i < V; ++i)
        graph->array[i].head = NULL;
 
    return graph;
}

 
// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest)
{
    // Add an edge from src to dest.  A new node is added to the adjacency
    // list of src.  The node is added at the begining
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
 
    /* Since graph is undirected, add an edge from dest to src also
    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;*/
}
 
// A utility function to print the adjacenncy list representation of graph
void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->V; ++v)
    {
        struct AdjListNode* pCrawl = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (pCrawl)
        {
            printf("-> %d", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}


typedef struct LevelArr_ParentArr
{
    int V;
    int *levelArr;
    //int *parentArr;
}Index;

Index* createIndex(int V)
{
    Index* index = (Index*) malloc(sizeof(Index));
    if(!index)
        return NULL;
    index->V = V;

    // Create an array of level and parent
    index->levelArr = (int*) malloc(V * sizeof(int));
    if(!(index->levelArr))
        return NULL;
    /*index->parentArr = (int*) malloc(V * sizeof(int));
    if(!(index->parentArr))
        return NULL;*/

    // Initialize each element of level array and parent array as -1
    int i;
    for (i = 0; i < V; ++i)
    {
        index->levelArr[i]= -1;
        //index->parentArr[i]= -1;
    }

    return index;
}

typedef struct ArrayQueue
{
    int front,rear;
    int capacity;
    int *array;
}Queue;

Queue* createQueue(int size)
{
    Queue *Q =(Queue*)malloc(sizeof(Queue));
    if(!Q)
        return NULL;
    Q->front=Q->rear=-1;
    Q->capacity=size;
    Q->array=(int*)malloc(sizeof(int)*Q->capacity);
    if(!(Q->array))
        return NULL;

    return Q;
}

int isEmptyQueue(Queue* Q)
{
    //if codn true i.e empty then 1 is returned else 0
    return(Q->front==-1);
}

int isFullQueue(Queue* Q)
{
    return((Q->rear+1)%Q->capacity==Q->front);
}

void EnQueue(Queue* Q, int data)
{
    if(isFullQueue(Q))
        printf("Queue overflow\n");
    else
    {
        Q->rear=(Q->rear+1) % Q->capacity;
        Q->array[Q->rear]=data;
        if(Q->front==-1)
            Q->front=Q->rear;
    }
}

int DeQueue(Queue* Q)
{
    int data=0;
    if(isEmptyQueue(Q))
    {
        printf("Queue empty\n");
        return 0;
    }
    else
    {
        data=Q->array[Q->front];
        if(Q->front==Q->rear)
            Q->front=Q->rear=-1;
        else
            Q->front=(Q->front+1) % Q->capacity;
    }
    return data;
}

int BFS(struct Graph* graph,int i) 
{
    int j=0,k,min_hop;
    // BFS starting from vertex i
    // create queue of size=no. of vertices V
    Queue* Q = createQueue(graph->V);

    // Create an array of level and parent of size=no. of vertices V
    Index* index = createIndex(graph->V);

    //Start the exploration at i, level[i] set to 0
    index->levelArr[i] = 0;
    EnQueue(Q,i);

    //Explore each vertex in Q, increment level for each new vertex
    while (!(isEmptyQueue(Q)))
    {
        j = DeQueue(Q);
        min_hop=index->levelArr[j];
        //for each (j,k) in E
        struct AdjListNode* pCrawl = graph->array[j].head;
        while (pCrawl)
        {
            k=pCrawl->dest;
            if (index->levelArr[k] == -1)
            {
                index->levelArr[k] = 1+index->levelArr[j];
                //index->parentArr[k] = j;
                EnQueue(Q,k);
                /*if((index->levelArr[k])>min_hop)
                {
                    min_hop=index->levelArr[k];
                }*/
                if((index->levelArr[(graph->V)-1])>0)
                {
                    return(index->levelArr[(graph->V)-1]);
                    //return (min_hop);
                }
            }
            pCrawl = pCrawl->next; 
        }   
    }
    return 0;
}



int main()
{
    // create the graph 
    int m ,n, i=0, j=0,temp=0;
    while(1)
    {
        m=scan();
        n=scan();
        if(1<=m  && m<=250 && 1<=n && n<=250)
            break;
    }
    int V = m*n;
    int right_arr[V], down_arr[V];
   
    for(i=0;i<V;++i)
        right_arr[i]=scan();
    for(i=0;i<V;++i)
        down_arr[i]=scan();

    struct Graph* graph = createGraph(V);

    for(i=1;i<=V;++i)
    {
        if(i%n)
        {
            for(j=i+1;j<=i+right_arr[i-1];++j)
            {
                addEdge(graph, i-1, j-1);
                if(!(j%n))
                    break;
            }
        }
    }

    temp=m-1;
    int count=0;
    for(i=1;i<=(V-n);++i)
    {
        for(j=i+n;j<=i+n*down_arr[i-1];j=j+n)
        {
            if(!(i%n))
                ++count;
            //printf("%d,%d,%d\n",i-1,j-1,temp);
            addEdge(graph, i-1, j-1);
            if(j>=(i+n*temp))
                break;
            if(count==1)
                --temp;
        }
        count=0;
    }
    int src=0,min_hop;
    min_hop=BFS(graph,src);
    //printGraph(graph);
    printf("%d\n",min_hop);

    return 0;
}
