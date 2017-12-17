#include <iostream>
#define maxsize 128
#define MAX 65535
using namespace std;
struct VEdge
{
	int fromv;
	int endv;
	int weight;
};
template <class T>
class MGraph
{
public:
	MGraph(T a[], int n, int e);
	~MGraph() {};
	void printarcs();
	void dfs(int v);
	void bfs(int v);
	void DFS(int v);
	void Prim();
	void Kruskal();
	void Dijkstra(int v);
private:
	T vertex[maxsize];
	int arcs[maxsize][maxsize];
	int vnum, arcnum;
	int mininum(int lowcost[]);
	void PrintPath(int Disk[], int Path[], int n);
	int findmin(int Disk[], bool S[], int n);
};
template <class T>
MGraph <T>::MGraph(T a[],int n,int e)
{
	int j, i, weight;
	vnum = n;
	arcnum = e;
	for (int i = 0; i<n; i ++)
		vertex[i] = a[i];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			arcs[i][j] = -1;
	for (int k = 0; k< e;k++)
	{
		cin >> i >> j >> weight;
		arcs[i][j] =arcs[j][i]= weight;
	}
}
template <class T>
void MGraph<T>::printarcs()
{
	for (int i = 0; i < vnum; i++)
	{
		for (int j = 0; j < vnum; j++)
			cout << arcs[i][j] << ' ';
		cout << endl;
	}
}
bool visited[maxsize] = { false };
template <class T>
void MGraph<T>::dfs(int v)
{	
	cout << vertex[v];
	visited[v] = true;
	for (int i = 0; i < vnum; i++)
		if (arcs[v][i] != -1 && !visited[i])
			dfs(i);
}
template <class T>
void MGraph<T>::bfs(int v)
{
	bool visited[maxsize] = { false };
	int queen[maxsize];
	int f = 0, r = 0;
	cout << vertex[v];
	visited[v] = true;
	queen[++r] = v;
	while (f != r)
	{
		v = queen[++f];
		for (int i = 0; i < vnum; i++)
		{
			if (arcs[v][i] != -1 && !visited[i])
			{	
				cout << vertex[i];
				queen[++r] = i;
				visited[i] = true;
			}
		}
	}
}
template <class T>
int MGraph<T>::mininum(int lowcost[])
{
	int min = MAX;
	int k = 0;
	for (int i = 1; i < vnum; i++)
	{
		if (lowcost[i]>0 && lowcost[i] < min)
		{
			k = i;
			min = lowcost[i];
		}
	}
	return k;
}
template <class T>
void MGraph<T>::Prim()
{
	int adjvex[maxsize];
	int lowcost[maxsize];
	for (int i = 0; i < vnum; i++)
	{
		adjvex[i] = 0;
		lowcost[i] = arcs[0][i];
	}
	lowcost[0] = 0;
	for (int i = 1; i < vnum; i++)
	{
		int k = mininum(lowcost);
		lowcost[k] = 0;
		cout << vertex[adjvex[k]] << "---"<< vertex[k] << endl;
		for (int i = 0; i < vnum; i++)
		{
			if ((lowcost[i]!=0 && arcs[k][i] >0&&arcs[k][i] < lowcost[i])||(arcs[k][i] >0 && lowcost[i]==-1))
			{
				lowcost[i] = arcs[k][i];
				adjvex[i] = k;
			}
		}
	}
}
template <class T>
void MGraph<T>::Kruskal()
{
	VEdge* EdgeList=new VEdge[arcnum];
	int k = 0, i, j;
	for (int i = 0; i < vnum; i++)
		for(int j=i;j<vnum;j++)
			if (arcs[i][j] > 0)
			{
				EdgeList[k].fromv = i;
				EdgeList[k].endv = j;
				EdgeList[k].weight = arcs[i][j];
				k++;
			}
	for (int i = 0; i < arcnum ; i++)
	{
		for (int j = 0 ; j < arcnum-i; j++)
		{
			if (EdgeList[j].weight > EdgeList[j+1].weight)
			{
				VEdge temp = EdgeList[j + 1];
				EdgeList[j +1] = EdgeList[j];
				EdgeList[j] = temp;
			}
		}
	}
	//for (i = 0; i < arcnum - 1; i++)
	//	cout << EdgeList[i].weight << ' ';
	int vset[maxsize];
	for (int i = 0; i < vnum; i++)
		vset[i] = i;
	k = 0; j = 0; i = 0;
	while (k < vnum - 1)
	{
		int m = EdgeList[j].fromv;
		int l = EdgeList[j].endv;
		int sn1 = vset[m];
		int sn2 = vset[l];
		if (sn1 != sn2)
		{
			cout << vertex[m] << "---" << vertex[l] << endl;
			k++	;
			for (int i = 0; i <vnum; i++)
			{
				if (vset[i] == sn2)
					vset[i] = sn1;
			}
		}
			j++;
	}
	
}
template <class T>
int MGraph<T>::findmin(int Disk[], bool S[], int n)
{
	int k = 0, min = MAX;
	for(int i=0;i<n;i++)
	{
		if (!S[i] &&(min > Disk[i]))
		{
			min = Disk[i];
			k = i;
		}
	}
	if (min == -1)
		return -1;
	return k;
}
template <class T>
void MGraph <T>::PrintPath(int Disk[], int Path[], int n)
{
	for (int i = 0; i < n; i++)
	{	
		cout << vertex[i] << ":" << Disk[i] << "\t" << vertex[i];
		int pre = Path[i];
		while (pre != -1)
		{
			cout<<"<<---"<<vertex[pre];
			pre = Path[pre];
		}
		cout << "\n";
	}
}
template <class T>
void MGraph<T>::Dijkstra(int v)
{
	bool S[maxsize] = { false };
	int Disk[maxsize];
	int Path[maxsize];
	for (int i = 0; i < vnum; i++)
	{
		Disk[i] = arcs[v][i];
		if (Disk[i] != -1)
			Path[i] = v;
		else
		{
			Path[i] = -1;
			Disk[i] = MAX;
		}
	}
	S[v] = true;
	Disk[v] = 0;
	for (int i = 0; i < vnum; i++)
	{
		v = findmin(Disk, S, vnum);
		if (v == -1)
			return;
		S[v] = true;
		for (int j = 0; j < vnum; j++)
		{
			int weight;
			if (arcs[v][j] == -1)
				weight = MAX;
			else
				weight = arcs[v][j];
			if (!S[j] && ((Disk[j] > weight + Disk[v])))
				{
					Disk[j] = weight+ Disk[v];
					Path[j] = v;
				}
		}
	}
	PrintPath(Disk, Path, vnum);
}

template <class T>
void MGraph<T>::DFS(int v)
{
	int S[128];
	int top = -1;
	cout << vertex[v];
	bool visited[128] = { false };
	visited[v] = true;
	top++;
	S[top] = v;
	while (top != -1)
	{
		v = S[top];
		bool variable = false;
		for (int j = 0; j < vnum; j++)
		{
			if (arcs[v][j]>0 && !visited[j])
			{
				cout << vertex[j];
				visited[j] = true;
				S[++top] = j;
				variable = true;
				break;
			}
		}
		if (!variable)   top--;
	}

}
int main()
{
	char a[6] = { 'A','B','C','D','E','F'};
	MGraph <char> A(a, 6, 9);
	cout << "链接矩阵：\n";
	A.printarcs();
	cout << "非递归深度优先遍历:";
	A.DFS(0);
	cout << endl;
	cout << "递归深度优先遍历:";
	A.dfs(0);
	cout << endl;
	cout << "广度优先遍历:";
	A.bfs(0);
	cout << endl;
	cout << "Prim算法（最小生成树）\n";
	A.Prim();
	cout << endl;
	cout << "Kruskal算法（最小生成树）\n";
	A.Kruskal();	
	cout << endl;
	cout << "Dijkstra算法（最短路径)\n";
	A.Dijkstra(0);
	return 0;
}