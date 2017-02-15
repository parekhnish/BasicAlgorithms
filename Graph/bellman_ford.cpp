#include <iostream>
#include <vector>
#include <climits>
#include <list>

using namespace std;

struct Edge;

struct Vertex
{
	int val;
	int dist;
	Vertex* prev_vert;
	list<Edge*> e;

	Vertex(int v)
	{
		val = v;
	}
};

struct Edge
{
	Vertex* source;
	Vertex* dest;
	int weight;

	Edge(Vertex* s, Vertex* d, int w)
	{
		source = s;
		dest = d;
		weight = w;
	}

	void relaxEdge()
	{
		if (dest->dist > (source->dist + weight))
		{
			dest->dist = source->dist + weight;
			dest->prev_vert = source;
		}
	}
};

Vertex* makeVertex(int temp_d)
{
	Vertex* temp_v = new Vertex(temp_d);
	return temp_v;
}

Edge* makeEdge(Vertex* s, Vertex* d, int w)
{
	Edge* temp_e = new Edge(s,d,w);
	return temp_e;
}

void initialiseSourceGraph(vector<Vertex*>* V, int src)
{
	int num_v = (*V).size();

	for(int i=0; i<num_v; i++)
	{
		(*V)[i]->dist = INT_MAX;
		(*V)[i]->prev_vert = NULL;
	}

	(*V)[src]->dist = 0;
}


void printShortestPath(Vertex* d)
{
	if(d == NULL)
	{
		return;
	}

	printShortestPath(d->prev_vert);
	cout<<d->val<<" ";
}


int main()
{
	int num_v , num_e;

	cin>>num_v;
	vector<Vertex*> V = vector<Vertex*>();

	int temp_d;
	for(int i=0; i<num_v; i++)
	{
		cin>>temp_d;
		V.push_back(makeVertex(temp_d));
	}

	cin>>num_e;

	vector<Edge*> E = vector<Edge*>();
	int s, d, w;
	Edge* temp_e;

	for(int i=0; i<num_e; i++)
	{
		cin>>s>>d>>w;
		temp_e = makeEdge(V[s],V[d],w);
		E.push_back(temp_e);

		V[s]->e.push_back(temp_e);
	}

	int ovr_src;
	cin>>ovr_src;
	initialiseSourceGraph(&V, ovr_src);

	for(int i=0; i<num_e; i++)
	{
		for(int j=0; j<num_v; j++)
		{
			for(list<Edge*>::iterator it = V[j]->e.begin(); it != V[j]->e.end(); it++)
			{
				(*it)->relaxEdge();
			}
		}
	}

	for(int i=0; i<num_e; i++)
	{
		if(E[i]->dest->dist > (E[i]->source->dist + E[i]->weight))
		{
			cout<<"NO SOLUTION!";
			return 0;
		}
	}

	for(int i=0; i<num_v; i++)
	{
		cout<<"SP from "<<ovr_src<<" to "<<V[i]->val<<":\t\t";
		printShortestPath(V[i]);
		cout<<endl;
	}

	return 0;

}