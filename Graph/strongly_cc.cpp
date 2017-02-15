#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

struct Edge;

struct Vertex
{
	int data;
	list<Edge*> e;
	bool visited;
	int entry_time,exit_time;

	Vertex(int d)
	{
		data = d;
		e = list<Edge*>();
		visited = false;
		entry_time = 0;
		exit_time = 0;
	};
};

struct Edge
{
	int weight;
	Vertex* dest;

	Edge(Vertex* v, int w)
	{
		weight = w;
		dest = v;
	};
};

struct sortVertexByExitTimeDescending
{
	inline bool operator() (const Vertex* v1, const Vertex* v2)
	{
		return (v1->exit_time > v2->exit_time);
	}
};

void perfDFS(Vertex* v, int* curr_time, bool* toPrint)
{
	v->visited = true;
	v->entry_time = *curr_time;
	*curr_time++;

	if(*toPrint)
	{
		cout<<v->data<<endl;
	}
	
	for(list<Edge*>::iterator it=v->e.begin(); it!=v->e.end(); it++)
	{
		if((*it)->dest->visited == false)
		{
			perfDFS((*it)->dest, curr_time, toPrint);
		}
	}

	if(*toPrint)
	{
		v->exit_time = *curr_time;
		*curr_time++;
	}
}

void DFS(vector<Vertex*>* v, int* curr_time, bool* toPrint)
{
	for(int i=0; i<(*v).size(); i++)
	{
		if((*v)[i]->visited == false)
		{
			perfDFS((*v)[i] , curr_time, toPrint);
			if(*toPrint)
			{
				cout<<endl;
			}
		}

	}
}

void resetVertices(vector<Vertex*>* v)
{
	for(int i=0; i<(*v).size(); i++)
	{
		(*v)[i]->visited = false;
	}
}

void transposeGraph(vector<Vertex*>* v)
{
	int num_v = (*v).size();

	vector<int> orig_sizes = vector<int>(num_v);

	for(int i=0; i<num_v; i++)
	{
		orig_sizes[i] = (*v)[i]->e.size();
	}

	Vertex* source;
	Vertex* dest;
	int w;

	for(int i=0; i<num_v; i++)
	{
		source = (*v)[i];
		while(orig_sizes[i]--)
		{
			dest = source->e.front()->dest;
			w = source->e.front()->weight;

			source->e.pop_front();

			Edge* temp_e = new Edge(source,w);
			dest->e.push_back(temp_e);
		}
	}
}

int main()
{
	int num_v , num_e;

	cin>>num_v;

	vector<Vertex*> v = vector<Vertex*>();

	int temp_d;
	for(int i=0; i<num_v; i++)
	{
		cin>>temp_d;
		Vertex* temp_v = new Vertex(temp_d);
		v.push_back(temp_v);
	}

	cin>>num_e;

	int temp_w,temp_s;
	for(int i=0; i<num_e; i++)
	{
		cin>>temp_s>>temp_d>>temp_w;
		Edge* temp_e = new Edge(v[temp_d] , temp_w);
		v[temp_s]->e.push_back(temp_e);
	}

	int curr_time = 0;
	bool toPrint = false;

	DFS(&v, &curr_time, &toPrint);

	resetVertices(&v);
	transposeGraph(&v);

	sort(v.begin() , v.end() , sortVertexByExitTimeDescending());


	toPrint = true;
	curr_time = 0;

	DFS(&v, &curr_time, &toPrint);	

}