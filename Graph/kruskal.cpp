#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

struct UndEdge;

struct Vertex
{
	int data;
	list<UndEdge*> e;

	Vertex* parent;
	int rank;

	Vertex(int d)
	{
		data = d;
		e = list<UndEdge*>();
		rank = 0;
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

struct sortEdges
{
	inline bool operator() (const UndEdge* e1, const UndEdge* e2)
	{
		return (e1->weight < e2->weight);
	}
};

UndEdge* makeUndEdge(Vertex* v1, Vertex* v2, int w)
{
	UndEdge* temp_e = new UndEdge(v1,v2,w);
	return temp_e;
}

Vertex* makeVertex(int d)
{
	Vertex* v = new Vertex(d);
	v->parent = v;

	return v;
}

Vertex* findSet(Vertex* v)
{
	if(v->parent != v)
	{
		v->parent = findSet(v->parent);
	}
	return v->parent;
}

void linkSets(Vertex* v1, Vertex* v2)
{
	if(v1->rank > v2->rank)
	{
		v2->parent = v1;
	}
	else
	{
		v1->parent = v2;

		if(v1->rank == v2->rank)
		{
			v2->rank++;
		}
	}
}

void unionSets(Vertex* v1, Vertex* v2)
{
	linkSets(findSet(v1) , findSet(v2));
}


void printEdges(vector<UndEdge*>* E)
{
	for(int i=0; i<(*E).size(); i++)
	{
		cout<<(*E)[i]->v1->data<<' '<<(*E)[i]->v2->data<<endl;
	}
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

	sort(E.begin(),E.end(),sortEdges());

	Vertex* v1;
	Vertex* v2;
	vector<UndEdge*> mst = vector<UndEdge*>();

	for(int i=0; i<E.size(); i++)
	{
		temp_e = E[i];
		v1 = temp_e->v1;
		v2 = temp_e->v2;
		// cout<<v1->data<<' '<<v2->data<<endl;
		if(findSet(v1) != findSet(v2))
		{
			mst.push_back(temp_e);
			unionSets(v1,v2);
		}
	}

	printEdges(&mst);

}