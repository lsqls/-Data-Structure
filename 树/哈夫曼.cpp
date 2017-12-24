#include <iostream>
#include <cstring> 
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
	int min(int m,int n);
public:
	void CreateTree(int a[], int n);
	void CreateCodeTable(char b[], int n);
	void Encode(char *s, char *d, int n);
	void Decode(char *s, char *d, int n);
	~Huffman() { delete[] HTree; delete[] HCodeTable; };
};
int Huffman::min(int n, int m)
{
	int i = n;
	int min = -1;
	while (HTree[i].par != -1 )
			i++;
	min = i;
	for(;i<m;i++)
		if (HTree[min].weight > HTree[i].weight&& HTree[i].par==-1)
			min = i;
	HTree[min].par = -2;
	return min;
	
}
void Huffman::selectmin(int &x, int &y, int start, int end)
{	
	x = min(start, end);
	y = min(start, end);
}

void Huffman::CreateTree(int a[], int n)
{
	HTree = new HNode[2 * n - 1];
	for (int i =0 ; i < n; i++)
	{
		HTree[i].weight = a[i];
		HTree[i].lc =HTree[i].par =HTree[i].rc = -1;
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
		int child = i;
		int parent = HTree[i].par;
		int k = 0;
		while (parent != -1)
		{
			if (child == HTree[parent].lc)
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
char * strcat(char *dst, char *src)
{
	char *start = dst;
	int len_dst = strlen(dst);
	dst += len_dst;
	while (*dst++ = *src++);
	return start;
}
void Huffman::Encode(char *s, char *d, int n)
{
	while (*d != '\0')
	{
		for (int i = 0; i < n; i++)
			if (HCodeTable[i].data == *d)
			{
				strcat(s, HCodeTable[i].code);
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
	cout << s;
	cout << endl;
	A.Decode(s, d, 4);
	cout << d;
}
