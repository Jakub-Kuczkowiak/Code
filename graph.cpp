#include <bits/stdc++.h>
using namespace std;

// SECTION: TREES

// Closest Common Predecessor
// Runs in O(n) to prepere and O(logn) for each request
// Can be used to find: weigth of path connectiong two verticies,
//						minimum/maximum weight of edge on path beetween two vericies -> can be used to find weight 
//						of MST containing specified edge,

namespace ccp
{

const int N = 100042;
const int H = 42;
vector<pair<int,int>> nbh[N]; 	// description of graph: edge = (destination, weight), V = {1,2,3,...,N-1};
int parent[N][H]; 				// parent[v][j] = w <=> w is vertex on path from root to v with dist(v,w) = 2^j;
								// H = 42 is big enough for long long, H = 21 should be just fine for contests
								// Remember to check graph size!!!
int lvl[N]; 					// lvl[v] = dist(v,root) + 1;
long long f[N][H]; 				// f[v][j] = value of our function on path from v to parent[v][j];

void dfs(int v)
{
	lvl[v] = lvl[parent[v][0]] + 1;
	for (auto w : nbh[v])
	{
		if (w.first != parent[v][0])
		{
			parent[w.first][0] = v;
			f[w.first][0] = w.second; 	// usually just weight of edge (v,w);
			dfs(w.first);
		}
	}
}

void init(int root)
{
	lvl[0] = 0;
	parent[root][0] = 0;
	dfs(root);

	for (int j=1; j<H; j++)
	{
		for (int i=1; i<N; i++)
		{
			parent[i][j] = parent[parent[i][j-1]][j-1];
			f[i][j] = f[i][j-1] + f[parent[i][j-1]][j-1]; // change for your function!!! 
		}
	}
}

long long eval(int u, int v)
{
	long long res = 0LL;
	if (lvl[v] < lvl[u])
		swap(v,u); 
	int j = H-1;
	while (lvl[v] > lvl[u])
	{
		if (parent[v][j] != 0 && lvl[parent[v][j]] >= lvl[u])
		{
			res += f[v][j];
			v = parent[v][j];
		}
		j--;
	}
	// Now levels are equal
	if (u == v)
		return res;

	j = H-1;
	while (parent[v][0] != parent[u][0])
	{
		if (parent[v][j] != parent[u][j])
		{
			res += f[v][j] + f[u][j];
			v = parent[v][j];
			u = parent[u][j];
		}
		j--;
	}
	res += f[v][0] + f[u][0];
	return res;
}

} // namespace ccp

// SECTION: ALL

// Union find
// Runs in O(mlog*m) amortized
// Can be used to find: 	connected components
//							MST (in O(mlogm) due to sorting of edges)

namespace uf
{

const int N = 100042;
int parent[N];
int cnt[N];

int ff(int x)
{
	vector<int> path;
	while (parent[x] != x)
	{
		path.push_back(x);
		x = parent[x];
	}
	for (int y : path)
		parent[y] = x;
	return x;
}

void uu(int x, int y)
{
	x = ff(x);
	y = ff(y);
	if (x == y)
		return;
	if (cnt[x] > cnt[y])
	{
		cnt[x] += cnt[y];
		parent[y] = x;
	}
	else
	{
		cnt[y] += cnt[x];
		parent[x] = y;
	}
}

} // namespace uf


int main()
{
	int n;
	cin >> n;
	for (int i=0; i<n-1; i++)
	{
		int a,b,c;
		cin >> a >> b >> c;
		nbh[a].push_back({b,c});
		nbh[b].push_back({a,c});
	}
	init(2);

	int q;
	cin >> q;
	while (q--)
	{
		int a,b;
		cin >> a >> b;
		cout << "Dist(a,b) = " << eval(a,b) << "\n";
	}
}