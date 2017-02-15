#include <iostream>
#include <vector>

using namespace std;

int bsearch(vector<int>, int);

int main()
{
	int n = 50;
	int query = 49;

	vector<int> a(n);

	for(int i=0; i<n; i++)
	{
		a[i] = i;
	}

	
	cout<<bsearch(a,query);


}


int bsearch(vector<int> a,int query)
{
	int len = a.size();

	int r = len-1;
	int l = 0;
	int m;

	while(l <= r)
	{
		m = (l+r)/2;

		if(query == a[m])
		{
			return(m);
		}
		else
		{
			if(query < a[m])
			{
				r = m-1;
			}
			else
			{
				l = m+1;
			}
		}
	}

	return(-1);
}