#include <iostream>
#include <cstdlib>
#include <vector>
#include <time.h>

using namespace std;

void quickSort(vector<int>* a,int l, int r);
int partition(vector<int>* a, int l, int r);
void printVector(vector<int>* a, int l, int r);

int main()
{
	srand(time(NULL));

	int n = 8;

	vector<int> a(n);

	for(int i=0; i<n; i++)
	{
		a[i] = rand()%10;
	}

	cout<<"INITIAL ARRAY: \t";
	printVector(&a,0,n-1);

	quickSort(&a,0,n-1);

	cout<<"FINAL ARRAY: \t";
	printVector(&a,0,n-1);
}

void quickSort(vector<int>* a, int l, int r)
{
	// cout<<"l = "<<l<<"\tr = "<<r<<'\n';
	if(l >= r)
	{
		// cout<<"Single Element: ";
		return;
	}

	// cout<<"Before:\t";
	// printVector(a,l,r);
	int p = partition(a,l,r);
	// cout<<"After:\t";
	// printVector(a,l,r);

	quickSort(a,l,p-1);
	quickSort(a,p+1,r);
}

int partition(vector<int>* a, int l, int r)
{
	int pivot_pos = (l+r)/2;
	int pivot = (*a)[pivot_pos];
	// cout<<"PIVOT: "<<pivot<<'\n';

	int x = l;
	int y = r-1;
	int temp;

	temp = (*a)[pivot_pos];
	(*a)[pivot_pos] = (*a)[r];
	(*a)[r] = temp;

	while (1)
	{
		while((y>=x)&&((*a)[y] > pivot))
		{
			y--;
		}
		while((x<=y)&&((*a)[x] < pivot))
		{
			x++;
		}
		

		if(x >= y)
		{
			(*a)[r] = (*a)[x];
			(*a)[x] = pivot;
			
			return x;
		}

		temp = (*a)[x];
		(*a)[x] = (*a)[y];
		(*a)[y] = temp;

		x++;
		y--;

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