/* Your code here! */
#include "dsets.h"


void DisjointSets::addelements (int num)
{
	for (int i = 0 ; i < num ; i++)
		array.push_back(-1);
}
int DisjointSets::find (int elem)
{
	if (array[elem] < 0)
		return elem;
	return array[elem] = find(array[elem]); 
}
void DisjointSets::setunion(int a, int b)
{
	int r1 = find(a);
	int r2 = find(b);
	int newsize = array[r1] + array[r2];
	
	if (array[r1] > array[r2]){
		array[r1] = r2;
		array[r2] = newsize;
	}
	else{
		array[r2] = r1;
		array[r1] = newsize;
	}
}
void DisjointSets::clear()
{
	array.clear();
}
bool DisjointSets::isEmpty()
{
	return array.empty();
}

