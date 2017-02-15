#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

struct Vertex
{
	int val;

	Vertex(int v)
	{
		val = v;
	}
};



vector< vector<int> > floydWarshall(vector< vector<int> >* E)
{
	int num_v = (*E).size();

	vector< vector<int> > prev_mat = (*E);

	for(int k=0; k<num_v; k++)
	{
		vector< vector<int> > new_mat = vector< vector<int> >(num_v, vector<int>(num_v,10000));
		for(int i=0; i<num_v; i++)
		{
			for(int j=0; j<num_v; j++)
			{
				new_mat[i][j] = min(prev_mat[i][j] , (prev_mat[i][k] + prev_mat[k][j]));
			}
		}

		prev_mat = new_mat;
	}

	return prev_mat;
}

void printDistMat(vector< vector<int> >* D_mat)
{
	for(int i=0; i<(*D_mat).size(); i++)
	{
		for(int j=0; j<(*D_mat).size(); j++)
		{
			if((*D_mat)[i][j] != 10000)
			{
				cout<<(*D_mat)[i][j];
			}
			cout<<"\t";
		}
		cout<<endl;
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
		V.push_back(new Vertex(temp_d));
	}

	cin>>num_e;

	int s,d,w;
	vector< vector<int> >E = vector< vector<int> >(num_v, vector<int>(num_v,10000));
	for(int i=0; i<num_e; i++)
	{
		cin>>s>>d>>w;
		E[s][d] = w;
	}

	for(int i=0; i<num_v; i++)
	{
		E[i][i] = 0;
	}

	vector< vector<int> > dist_mat = floydWarshall(&E);

	printDistMat(&dist_mat);
}