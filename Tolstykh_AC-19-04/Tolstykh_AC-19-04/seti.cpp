#include "seti.h"
using namespace std;

vector<vector<int>> rebra;

void seti::topologicalSortUtil(int v, bool visited[], stack<int>& Stack)
{
	visited[v] = true;

	vector<int>::iterator i;
	for (i = rebra[v].begin(); i != rebra[v].end(); ++i)
		if (!visited[*i])
			topologicalSortUtil(*i, visited, Stack);

	Stack.push(v);
}

seti::seti(const vector<vector<int>>& r)
{
	rebra = r;
}

bool dfs(int v, vector<char>& cl, vector<int>& p, int& cycle_st, const vector<vector<int>>& adj) {
	cl[v] = 1;
	for (size_t i = 0; i < adj[v].size(); ++i) {
		int to = adj[v][i];
		if (cl[to] == 0) {
			p[to] = v;
			if (dfs(to, cl, p, cycle_st, adj))
				return true;
		}
		else if (cl[to] == 1) {
			cycle_st = to;
			return true;
		}
	}
	cl[v] = 2;
	return false;
}

void seti::topologicalSort(unordered_map<int, int>& indexVershin)
{
	stack<int> Stack;
	int n = rebra.size();
	bool* visited = new bool[n];
	for (int i = 0; i < n; i++)
		visited[i] = false;

	for (int i = 0; i < n; i++)
		if (visited[i] == false)
			topologicalSortUtil(i, visited, Stack);

	while (Stack.empty() == false)
	{
		cout << "สั " << indexVershin[Stack.top()] << " - ";
		Stack.pop();
	}
	cout << endl;
}

bool seti::HasCicl()
{
	int n = rebra.size();
	vector<char> cl;
	vector<int> p;
	int cycle_st;
	p.assign(n, -1);
	cl.assign(n, 0);
	cycle_st = -1;
	for (int i = 0; i < n; ++i)
		if (dfs(i, cl, p, cycle_st, rebra))
			break;
	if (cycle_st == -1)
		return false;
	else
		return true;
}

