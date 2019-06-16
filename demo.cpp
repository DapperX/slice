#include <iostream>
#include <vector>
#include "slice.hpp"
using namespace std;

int main()
{
	vector<char> a{'a','b','c','d','e','f'};
	slice<vector<char>::iterator> s(a.begin()+1, 3);
	s[2] = 'z';
	for(auto i=s.begin(); i!=s.end(); ++i)
	{
		cout << *i << endl;
	}

	int x[] = {11, 22, 33, 44};
	slice<int*> x_slice(x, 2);
	for(auto k : x_slice)
	{
		cout << k << endl;
	}

	/*
	const slice<int*> y(x, 4);
	y[2] = 1; // Error: assignment of read-only location
	*/
	return 0;
}