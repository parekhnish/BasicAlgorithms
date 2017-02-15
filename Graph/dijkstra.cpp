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
	int queuePos;

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

struct Heap
{
	vector<Vertex*> arr;
	int len;

	void swap(int a, int b)
	{
		Vertex* temp = arr[a];
		arr[a] = arr[b];
		arr[b] = temp;

		arr[a]->queuePos = a;
		arr[b]->queuePos = b;
	};

	void percolateDown(int pos)
	{
		int min = pos;

		if(((2*pos+1) < len) && (arr[min]->dist > arr[2*pos+1]->dist))
		{
			min = 2*pos+1;
		}
		if(((2*pos+2) < len) && (arr[min]->dist > arr[2*pos+2]->dist))
		{
			min = 2*pos+2;
		}

		if(min != pos)
		{
			swap(min,pos);
			percolateDown(min);
		}
	};

	void percolateUp(int pos)
	{
		if(pos > 0)
		{
			if(arr[pos]->dist < arr[(pos-1)/2]->dist)
			{
				swap(pos,(pos-1)/2);
				percolateUp((pos-1)/2);
			}
		}
	};

	Vertex* pop()
	{
		if(len == 0)
			return NULL;

		Vertex* ret = arr[0];

		swap(0,len-1);

		arr.erase(arr.begin()+len-1);
		len--;

		percolateDown(0);

		// ret->inQueue = false;
		return ret;
	};

	Heap(vector<Vertex*>* a)
	{
		arr = (*a);
		len = arr.size();

		for(int i=0; i<len; i++)
		{
			// arr[i]->inQueue = true;
			arr[i]->queuePos = i;
		}

		for(int i=(len-2)/2; i >= 0; i--)
		{
			percolateDown(i);
		}
	};
};


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


void dijkstra(vector<Vertex*>* V)
{
	Heap Q = Heap(V);

	Vertex* curr;
	Vertex* nb;
	while(Q.len != 0)
	{
		curr = Q.pop();
		for(list<Edge*>::iterator it = curr->e.begin(); it != curr->e.end(); it++)
		{
			nb = (*it)->dest;
			(*it)->relaxEdge();
			Q.percolateUp(nb->queuePos);
		}
	}

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

	dijkstra(&V);

	for(int i=0; i<num_v; i++)
	{
		cout<<"SP from "<<ovr_src<<" to "<<V[i]->val<<":\t\t";
		printShortestPath(V[i]);
		cout<<endl;
	}

	return 0;

}