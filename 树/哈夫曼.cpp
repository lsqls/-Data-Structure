#include <iostream>
#include <string.h>
using namespace std;
struct HNode
{
	int weight;
	int lc;
	int rc;
	int par;
};
struct HCode
{
	char data;
	char code[100];
};
class Huffman
{
private:
	HNode * HTree;
	HCode * HCodeTable;
	void selectmin(int &x, int &y, int start, int end);
public:
	void CreateTree(int a[], int n);
	void CreateCodeTable(char b[], int n);
	void Encode(char *s, char *d, int n);
	void Decode(char *s, char *d, int n);
	~Huffman() {};
	
};
void Huffman::selectmin(int &x, int &y, int start, int end)
{	
	int m = start;
	while (HTree[m++].par != -1);
	x = m - 1;
	while (HTree[m++].par != -1);
	y = m - 1;
	if (HTree[y].weight < HTree[x].weight)
	{	
		int temp = x;
		x = y;
		y = temp;
	}
	for (int i = m; i < end; i++)
	{
		if ((HTree[i].weight < HTree[x].weight)&&HTree[i].par==-1)
		{
			x = i;
			y = x;
		}
	}
}

void Huffman::CreateTree(int a[], int n)
{
	HTree = new HNode[2 * n - 1];
	for (int i =0 ; i < n; i++)
	{
		HTree[i].weight = a[i];
		HTree[i].lc = -1;
		HTree[i].rc = -1;
		HTree[i].par = -1;
	}
	int x, y;
	for (int i = n; i < 2 * n - 1; i++)
	{
		selectmin(x, y, 0, i);
		HTree[x].par = HTree[y].par = i;
		HTree[i].weight = HTree[x].weight + HTree[y].weight;
		HTree[i].lc = x;
		HTree[i].rc = y;
		HTree[i].par = -1;
	}
}
void Reverse(char * str)
{
	int m = 0;
	while (str[m++] != '\0');
	m = m - 2;
	for (int i = 0; i < m - i; i++)
	{
		char temp = str[i];
		str[i] = str[m -i];
		str[m - i] = temp;
	}
}
void Huffman::CreateCodeTable(char b[], int n)
{
	HCodeTable = new HCode[n];
	for (int i = 0; i < n; i++)
	{
		HCodeTable[i].data = b[i];
		int child = -1;
		int parent = HTree[i].par;
		int k = 0;
		while (parent != -1)
		{
			if (child == HTree[i].lc)
				HCodeTable[i].code[k] = '0';
			else
				HCodeTable[i].code[k] = '1';
			k++;
			child = parent;
			parent = HTree[child].par;
		}
		HCodeTable[i].code[k] = '\0';
		Reverse(HCodeTable[i].code);
	}
}
void Huffman::Encode(char *s, char *d, int n)
{
	while (*d != '\0')
	{
		for (int i = 0; i < n; i++)
			if (HCodeTable[i].data == *d)
			{
				strcat_s(s, strlen(HCodeTable[i].code), d);
			}
		d++;
	}
}
void Huffman::Decode(char *s, char *d, int n)
{
	while (*s!= '\0')
	{
		int parent = 2 * n - 2;
		while (HTree[parent].lc!= -1)
		{
			if (*s == '0')
				parent = HTree[parent].lc;
			else
				parent = HTree[parent].rc;
			s++;
		}
		*d = HCodeTable[parent].data;
		d++;
	}
}
int main()
{
	int weight[4] = { 2,3,6,9 };
	char b[4] = { 'Z','C','B','A' };
	Huffman A;
	A.CreateTree(weight, 4);
	A.CreateCodeTable(b, 4);
	char d[100] = "ACCZBBBAAACBBZABAAAA";
	char s[100] = "";
	A.Encode(s, d, 4);
	cout << d;
	A.Decode(s, d, 4);
}