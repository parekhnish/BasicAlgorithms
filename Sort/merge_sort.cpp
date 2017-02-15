#include <iostream>
#include <cstdlib>
#include <vector>
#include <time.h>

using namespace std;

void mergeSort(vector<int>* a, int l, int r);
void merge(vector<int>* a, int l, int m, int r);
void printVector(vector<int>* a, int l, int r);

int main()
{
	srand(time(NULL));

	int n = 14;

	vector<int> a(n);

	for(int i=0; i<n; i++)
	{
		a[i] = rand()%10;
	}

	cout<<"INITIAL ARRAY: \t";
	printVector(&a,0,n-1);

	mergeSort(&a,0,n-1);

	cout<<"FINAL ARRAY: \t";
	printVector(&a,0,n-1);
}


void mergeSort(vector<int>* a, int l, int r)
{
	if(r <= l)
	{
		return;
	}

	int m = (l+r)/2;

	mergeSort(a,l,m);
	mergeSort(a,m+1,r);

	merge(a,l,m,r);

	return;
}

void merge(vector<int>* a, int l, int m, int r)
{
	int x = l;
	int y = m+1;

	vector<int> temp(r-l+1);
	int index = 0;

	while(x<=m && y<=r)
	{
		if((*a)[x] < (*a)[y])
		{
			temp[index] = (*a)[x];
			x++;
		}
		else
		{
			temp[index] = (*a)[y];
			y++;
		}

		index++;
	}

	while(x <= m)
	{
		temp[index] = (*a)[x];
		index++;
		x++;
	}
	while(y <= r)
	{
		temp[index] = (*a)[y];
		y++;
		index++;
	}

	index = 0;
	for(int i=l; i<=r; i++)
	{
		(*a)[i] = temp[index];
		index++;
	}
}

void printVector(vector<int>* a,int l, int r)
{
	for(int i=l; i<=r; i++)
	{
		cout<<(*a)[i]<<" "; 
	}
	cout<<'\n';
}