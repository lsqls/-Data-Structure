#include <iostream>
#include <iomanip>
#include <cstring> 
#define N 10
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
	void print(int i,int m, char leaf[]);
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
		cout << HCodeTable[i].data<< ' '<<HCodeTable[i].code << endl;
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
void Huffman::print(int i, int m,char leaf[])
{
	if (HTree[i].lc == -1)
		cout << setfill(' ') << setw(m + 1) << leaf[i] << setfill('-') << setw(N - m) << '\n';
	else
	{
		cout << setfill(' ') << setw(m + 1) << HTree[i].weight << setfill('-') << setw(N - m) << '\n';
		print(HTree[i].lc, m + 1,leaf);
		print(HTree[i].rc, m + 1,leaf);
	}
}
void init(int a[],char leaf[],char str[],int nNum[],int &n)
{
	cout << "ÊäÈëÒª±àÂëµÄ×Ö·û´®:";
	int ch = cin.get();
	int i = 0;
	while (ch != '\n')
	{
		nNum[ch]++;
		str[i++] = ch;
		ch = cin.get();
	}
	str[i] = '\0';
	n = 0;
	for (int i = 0; i < 256; i++)
	{
		if (nNum[i] > 0)
		{
			leaf[n] = (char)i;
			a[n] = nNum[i];
			n++;
		}
	}
}
int main()
{
	int nNum[256] = { 0 };
	char str[1024];
	char leaf[256];
	int a[256];
	int n;
	char s[10000] = "";
	init(a, leaf, str, nNum, n);
	Huffman A;
	A.CreateTree(a,n);
	cout << "¹þ·òÂüÊ÷\n";
	A.print(2 * n - 2, 1, leaf);
	cout << "±àÂë±í\n";
	A.CreateCodeTable(leaf,n);
	A.Encode(s, str, n);
	cout << "±àÂë½á¹ûÎª:"<<s<< endl;;
	A.Decode(s, str, n);
	cout << "½âÂë½á¹û:" << str << endl;
	cout << "Ñ¹ËõÂÊ:" << float(strlen(s)) / float(strlen(str) * 8) * 100 << '%' << endl;
}
