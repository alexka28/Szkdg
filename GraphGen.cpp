#include "GraphGen.h"
bool Graph::queryGraph(int v, int f, bool *ret)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
    {
        visited[i] = false;
    }

     DFSUtil(v, visited, f, ret);

return *ret;
}

bool Graph::DFSUtil(int v, bool visited[], int f, bool *ret)
{
    // Mark the current node as visited and print it
    visited[v] = true;

    // Recur for all the vertices
    // adjacent to this vertex
    std::list<int>::iterator i;
    for(i = adj[v].begin(); i != adj[v].end(); ++i)
    {
        if(*i == f)
        {
            *ret = true;

        }
        if(!visited[*i])
        {
            DFSUtil(*i, visited, f, ret);
        }

    }
    //return false;
}

Graph::Graph(int V)
{
    this->V = V;
    adj = new std::list<int>[V];
}

// method to add an undirected edge
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);
}





/*#include<iostream>
#include<stdlib.h>

using namespace std;


struct node
{
	int data;
	struct node *link;
};

//list of vertexes connected to the given vertex.
struct vertexlist
{
	struct node *vlisthead;
};


struct Graph
{
	int v;
	struct vertexlist *vl;
};


struct Graph* CreateGraph(int n)
{
	int i;
	struct Graph *vlist = new Graph;
	vlist->v = n;


	vlist->vl = new vertexlist[n+1];


	for(i = 0; i < n+1; i++)
	{
		vlist->vl[i].vlisthead = NULL;
	}

	return vlist;
}

struct node* NewNode(int value)
{
	struct node *newnode = new node;
	newnode->data = value;
	newnode->link = NULL;

	return newnode;
}


void InsertNode(Graph *G, int v1, int v2)
{
	node *newnode1 = NewNode(v1);
	node *newnode2 = NewNode(v2);
	node *temp = new node;

	// one side connect bc undirected
	if(G->vl[v2].vlisthead == NULL)
	{

		G->vl[v2].vlisthead = newnode1;
	}
	else
	{

		newnode1->link = G->vl[v2].vlisthead;
		G->vl[v2].vlisthead = newnode1;
	}
	// and the other side connect
	if(G->vl[v1].vlisthead == NULL)
	{

		G->vl[v1].vlisthead = newnode2;
	}
	else
	{

		newnode2->link = G->vl[v1].vlisthead;
		G->vl[v1].vlisthead = newnode2;
	}
}

void GenerateRandomly(Graph *G, int v, int e){



int i;
	for(i = 0; i < e; i++)
	{


int edge1 = rand()%v+1;
int edge2 = rand()%v+1;
		InsertNode(G, edge1, edge2);
	}
}
int main()
{
	int i, v, e;


	cout<<"Enter the number of vertexes of the graph: ";
	cin>>v;
	struct Graph *G = CreateGraph(v);
	cout<<"\nEnter the number of edges of the graph: ";
	cin>>e;

GenerateRandomly(G, v, e);


	//print out
	cout<<"\n\nThe incidence list representation for the given graph: ";
	for(i = 0; i < v; i++)
	{
		cout<<"\n\tV("<<i+1<<") -> {  ";
		while(G->vl[i+1].vlisthead != NULL)
		{
			cout<<G->vl[i+1].vlisthead->data<<"  ";
			G->vl[i+1].vlisthead = G->vl[i+1].vlisthead->link;
		}
		cout<<"}";

}


}
*/
