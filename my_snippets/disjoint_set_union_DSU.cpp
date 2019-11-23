// The best way I've seen to 
// code this kind of DSU, is style of bmerry : (C++)

// Algorithm Gym :: Data structures by DarthKnight // CF

//initially are parents are set to -1

// for each root v, 
// par[v] equals the negative of number of tools in that box.

int root(int v){return par[v] < 0 ? v : (par[v] = root(par[v]));}

void merge(int x,int y){	//	x and y are some tools (vertices)
	if((x = root(x)) == (y = root(y))  return ;
	if(par[y] < par[x])	// balancing the height of the tree
		swap(x, y);
	par[x] += par[y];
	par[y] = x;
}