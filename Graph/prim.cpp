#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <climits>

using namespace std;

struct UndEdge;

struct Vertex
{
	int data;
	list<UndEdge*> e;

	UndEdge* sel_edge;
	int key;
	bool inQueue;
	int queuePos;

	Vertex(int d)
	{
		data = d;
		e = list<UndEdge*>();
		key = INT_MAX;
		sel_edge = NULL;
	};
};

struct UndEdge
{
	int weight;
	
	Vertex* v1;
	Vertex* v2;

	UndEdge(Vertex* vert1, Vertex* vert2, int w)
	{
		weight = w;
		v1 = vert1;
		v2 = vert2;
	};

	bool operator < (const UndEdge* e) const
	{
		return (weight < e->weight);
	};
};

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

		if(((2*pos+1) < len) && (arr[min]->key > arr[2*pos+1]->key))
		{
			min = 2*pos+1;
		}
		if(((2*pos+2) < len) && (arr[min]->key > arr[2*pos+2]->key))
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
			if(arr[pos]->key < arr[(pos-1)/2]->key)
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

		ret->inQueue = false;
		return ret;
	};

	Heap(vector<Vertex*>* a)
	{
		arr = (*a);
		len = arr.size();

		for(int i=0; i<len; i++)
		{
			arr[i]->inQueue = true;
			arr[i]->queuePos = i;
		}

		for(int i=(len-2)/2; i >= 0; i--)
		{
			percolateDown(i);
		}
	};
};



UndEdge* makeUndEdge(Vertex* v1, Vertex* v2, int w)
{
	UndEdge* temp_e = new UndEdge(v1,v2,w);
	return temp_e;
}

Vertex* makeVertex(int d)
{
	Vertex* v = new Vertex(d);
	return v;
}




void printEdges(vector<UndEdge*>* E)
{
	for(int i=0; i<(*E).size(); i++)
	{
		cout<<(*E)[i]->v1->data<<' '<<(*E)[i]->v2->data<<endl;
	}
}


vector<UndEdge*>* prim(vector<Vertex*>* V)
{
	(*V)[0]->key = 0;

	Heap Q = Heap(V);

	Vertex* curr;
	Vertex* nb;
	while(Q.len != 0)
	{
		curr = Q.pop();
		
		for(list<UndEdge*>::iterator it = curr->e.begin(); it != curr->e.end(); it++)
		{
			if((*it)->v1 != curr)
			{
				nb = (*it)->v1;
			}
			else
			{
				nb = (*it)->v2;
			}

			if((nb->inQueue == true) && (*it)->weight < nb->key)
			{
				nb->sel_edge = (*it);
				nb->key = (*it)->weight;
				Q.percolateUp(nb->queuePos);
			}
		}
	}

	vector<UndEdge*>* mst = new vector<UndEdge*>();

	for(int i=0; i<(*V).size(); i++)
	{
		if((*V)[i]->sel_edge != NULL)
		{
			(*mst).push_back((*V)[i]->sel_edge);
		}
	}

	return mst;

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

	vector<UndEdge*> E = vector<UndEdge*>();
	int temp_v1, temp_v2, w;
	UndEdge* temp_e;

	for(int i=0; i<num_e; i++)
	{
		cin>>temp_v1>>temp_v2>>w;
		temp_e = makeUndEdge(V[temp_v1],V[temp_v2],w);
		E.push_back(temp_e);

		V[temp_v1]->e.push_back(temp_e);
		V[temp_v2]->e.push_back(temp_e);
	}

	vector<UndEdge*>* mst = prim(&V);

	printEdges(mst);

}