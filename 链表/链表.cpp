#include <iostream> 
using namespace std;
template <class T>
struct node
{
	T data;
	node <T> *next;
};
template <class T>
class list
{
private:
	node <T> *header;//header pointer
public:
	list();
	list(T a[],int n,int loc=0);
	list(list &A);
	void print();
	int len();
	node <T> *  get(int i);
	int  locate(T x);
	void insert(int i,T x);
	void __delete(int i);
	~list();
};
template <class T>
list <T>::list()
{
	header=new node <T>;
	header->next=NULL;
}
template <class T>
list <T>::list(T a[],int n,int loc)//0 头插法  1尾插法  
{	header=new node <T>;
	header->next=NULL;
	if (loc==0)
		for(int i=n-1;i>=0;--i)
		{	
			node <T> *p=new node <T>;
			p->data=a[i];
			p->next=header->next;
			header->next=p;
		}
	if (loc==1) 
	{	node <T> *q=header;
	 	for(int i=0;i<n;i++)
		{	
			node <T> *p=new node <T>;
			p->data=a[i];
			q->next=p;
			q=p;
			q->next=NULL;
		} 
	}
}
template <class T>
list <T>::list(list &A)
{
	header=new node <T>;
	header->next=NULL;
	for(int i=A.len();i>=1;--i)
	{
		node <T> *p=new node <T>;
		p->data=A.get(i)->data;
		p->next=header->next;
		header->next=p;
	}
	
}
template <class T>
void list <T>::print()
{
	node <T> *p=header->next;
	cout<<'{';
	while(p!=NULL)
	{
		cout<<p->data<<',';
		p=p->next;
	}
	cout<<'}'<<endl;
}
template <class T>
int list <T>::len()
{
	node <T> *p=header;
	int len=0;
	while(p->next!=NULL)
	{
		len++;
		p=p->next;
	}
	return len;
}
template <class T>
list <T>::~list()
{
	node <T> *p=header;
	while(p)
	{	
		header=p;
		p=p->next;
		delete header;
	}
}
template <class T>
node <T> * list <T>::get(int i)
{	
	if(i<1)
		throw "输入位置非法";
	else
	{
		node <T> *p=header;
		int n=0;
		while(n!=i&&p)
			{
				p=p->next;
				n++;
			}
		return p;
	}
}
template <class T>
int  list <T>::locate(T x)
{
	node <T> *p=header;
	int i=0;
	while(p->data!=x)
		{
			p=p->next;
			i++;
		}
	if(p==NULL)
		cout<<"查找的值不存在";
	else
		return i;
}
template <class T>
void list <T>::insert(int i,T x)
{	node <T> *p=header;
	if(i!=1) p=get(i-1);
	if(p)
	{
		node <T> *s=new node <T>;
		s->data=x;
		s->next=p->next;
		p->next=s;
	}
	else 
		throw "输入位置非法";
}
template <class T>
void list <T>::__delete(int i)
{
	node <T> *p=header;
	if(i!=1) p=get(i-1);
	if(!p&&!p->next) throw "位置非法";
	node <T> *s=p->next;
	p->next=s->next;
	delete s;
}	
int main()
{	int a[4]={1,2,3,4};
	list <int> b(a,4,0);
	b.print();
	cout<<b.get(2)<<endl;
	cout<<b.locate(3)<<endl;
	cout<<b.len()<<endl;
	b.insert(5,78);
	b.__delete(1);
	b.print();
	cout<<b.len()<<endl;
	list <int> d(a,4,1);
	d.print();
	cout<<d.get(2)<<endl;
	cout<<d.locate(2)<<endl;
	cout<<d.len()<<endl;
	d.insert(5,78);
	d.__delete(1);
	d.print();
	cout<<d.len()<<endl;
	list <int> c(d);
	c.print();
	cout<<c.get(2)<<endl;
	cout<<c.locate(3)<<endl;
	cout<<c.len()<<endl;
	c.insert(5,78);
	c.__delete(1);
	c.print();
	return 0;
}
