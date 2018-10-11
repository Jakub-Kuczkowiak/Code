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

// Dijkstra
// Runs in O(mlogm)
// Shortest paths from all to one (s). NO negative weights allowed!

namespace dijkstra
{

const int N = 100042;
long long dist[N];
vector<pair<int,int>> nbh[N]; 
priority_queue<pair<long long,int>> Q;	// <-dist, v>

void run(int s)
{
	for (int i=0; i<N; i++) dist[i] = -1;
	Q.push({-0,s});
	while (!Q.empty())
	{
		long long d = -Q.top().first;
		int v = Q.top().second;
		Q.pop();
		if (dist[v] != -1)
			continue;
		dist[v] = d;
		for (auto ww : nbh[v])
		{
			if (dist[ww.first] != -1)
				continue;
			Q.push({-d-ww.second,ww.first});
		}
	}
}

} // namespace dijkstra

// Bellman-Ford
// Runs in O(nm)
// Shortest paths from all to one (s). 	Negative weights allowed, no negative cycles reachable from s. 
//										It also detect negative cycle reachable from s.

namespace bellman_ford
{

const int N = 100042;
const long long INF = 1LL<<60;
long long dist[N];
vector<pair<int,int>> nbh[N]; 

bool run(int s, int n)				// V = {0,1,2,..., n-1} , returns true if there is negative cycle
{
	for (int i=0; i<N; i++) dist[i] = INF;
	dist[s] = 0;
	for (int turn = 0; turn < n-1; turn++)
	{
		for (int i=0; i<n; i++)
		{
			for (auto ww : nbh[i])
			{
				if (dist[i] + ww.second < dist[ww.first])
					dist[ww.first] = dist[i] + ww.second;
			}
		}
	}
	// Check for negative cycle:
	for (int i=0; i<n; i++)
	{
		for (auto ww : nbh[i])
		{
			if (dist[i] + ww.second < dist[ww.first])
				return true;
		}
	}
	return false;
}

} // namespace bellman_ford

// Floyd-Warshall
// Runs in O(n^3)
// Shortest paths between all pairs. Negative weights allowed, NO negative cycles!

namespace floyd_warshall
{

const int N = 1042;
const long long INF = 1LL<<60;
long long dist[N][N];
int pred[N][N]; 				// prev[v][w] = u <=> shortest path from v to w ends with edge (u,w);
vector<pair<int,int>> nbh[N]; 

void run(int n)					// V = {0,1,2,..., n-1}
{
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
		{
			dist[i][j] = INF;
			pred[i][j] = -1;
		}
		dist[i][i] = 0;
	}
	for (int i=0; i<n; i++)
	{
		for (auto ww : nbh[i])
		{
			dist[i][ww.first] = ww.second;
			pred[i][ww.first] = i;
		}
	}

	for (int u=0; u<n; u++)
	{
		for (int v=0; v<n; v++)
		{
			for (int w=0; w<n; w++)
			{
				if (dist[v][w] > dist[v][u] + dist[u][w])
				{
					dist[v][w] = dist[v][u] + dist[u][w];
					pred[v][w] = pred[u][w];
				}
			}
		}
	}
}


} // namespace floyd_warshall

using namespace floyd_warshall;

int main()
{
	int n,m;
	cin >> n >> m;
	for (int i=0; i<m; i++)
	{
		int a,b,c;
		cin >> a >> b >> c;
		nbh[a].push_back({b,c});
		//nbh[b].push_back({a,c});
	}
	run(n);

	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
		{
			cout << "dist(" << i << "," << j << ") = " << dist[i][j] << "\n";
		}
	}
}