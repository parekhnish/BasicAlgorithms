#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge;

struct Vertex
{
	int data;
	vector<Edge*> e;
	bool visited;

	Vertex(int d)
	{
		data = d;
		e = vector<Edge*>();
		visited = false;
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

void perfDFS(Vertex* v)
{
	v->visited = true;
	cout<<v->data<<endl;
	
	for(int i=0; i<v->e.size(); i++)
	{
		if(v->e[i]->dest->visited == false)
		{
			perfDFS(v->e[i]->dest);
		}
	}
}

void DFS(vector<Vertex*>* v)
{
	for(int i=0; i<(*v).size(); i++)
	{
		if((*v)[i]->visited == false)
		{
			perfDFS((*v)[i]);
		}
	}
}

void perfBFS(queue<Vertex*> q)
{
	Vertex* v;
	while(!(q.empty()))
	{
		v = q.front();
		q.pop();
		v->visited = true;
		cout<<v->data<<endl;

		for(int i=0; i<v->e.size(); i++)
		{
			if(v->e[i]->dest->visited == false)
			{
				q.push(v->e[i]->dest);
				v->e[i]->dest->visited = true;
			}
		}
	}
}

void BFS(vector<Vertex*>* v)
{
	for(int i=0; i<(*v).size(); i++)
	{
		if((*v)[i]->visited == false)
		{
			queue<Vertex*> q = queue<Vertex*>();
			q.push((*v)[i]);
			perfBFS(q);
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

	DFS(&v);
	// BFS(&v);

}