#include <iostream>
#include <cmath>
using namespace std;
template <class T>
class list
{
private:
	T *p;;
	int len;
	int size;
public:
	list();
	list(const T a[],int n);
	void print();
	int get_len();
	T get(int i);
	int locate(T x);
	void insert(int i,T x);
	void __delete(int i);
	void josephus(int k);
	~list();
};
template <class T>
list<T>::list()
{
	p=NULL;
	len=0;
	size=0;
}
template <class T>
list<T>::list(const T a[],int n)
{	p=NULL;
	len=0;
	size=0;
	size=n+10;
	p=new T[size];
	for(int i=0;i<n;++i)
	{	p[i]=a[i];
		len++;
	}
}
template <class T>
void list<T>::print()
{	cout<<'{';
	for(int i=0;i<len;++i)
		cout<<p[i]<<',';
	cout<<'}'<<endl;
}
template <class T>
int list<T>::get_len()
{
	return len;
}
template <class T>
T list <T>::get(int i)
{
	if(i<1||i>len)
		throw "输入的位置非法";
	else
		return p[i-1];
}
template <class T>
int list<T>::locate(T x)
{
	int i=0;
	while(p[i]!=x&&i<len)
		i++;
	if(i<len)
		return i+1;
	else 
		throw "要查找的值不在链表里";
}
template <class T>
void list<T>::insert(int i,T x)
{
	if(i<1||i>len+1)
		throw "输入的位置非法";
	else
	{
		if(len>=size)
		{	size+=10;
			T *p1=new T[size];
			for(int j=0;j<i-1;++j)
				p1[j]=p[j];
			p1[i-1]=x;
			for(int j=i;j<len;++j)
				p1[j]=p[j-1];
			delete [] p;
			p=p1;
		}
		else
		{
			for(int j=len;j>=i;--j)
				p[j]=p[j-1];
			p[i-1]=x;
		}
		len++;
	}
}
template <class T>
void list<T>::__delete(int i)
{
	if(i<1||i>len)
		throw "输入的位置非法";
	else 
		{
			for(int j=i-1;j<len;j++)
				p[j]=p[j+1];
			len--;
		}
}
template <class T>
list <T>::~list()
{
	delete [] p;
}
template <class T>
void list <T>::josephus(int k)
{	
	int lo=1;
	while(len>0)
	{
		lo=lo+k%len-1;
		if(lo>len||lo==0)
			lo=abs(lo-len);
		cout<<p[lo-1]<<' ';
		__delete(lo);
	}
}
void josephus(int n,int k)
{
	int *a=new int[n];
	for(int i=0;i<n;i++)
		a[i]=i+1;
	list <int> b(a,n);
	b.josephus(k);
}
int main()
{
	josephus(10,3);
	return 0;
}
