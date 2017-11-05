#include <iostream> 
#include <cmath>
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
	node <T> * getheader(){return header;};
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
struct term
    {
          float coef;   //系数
          int expn;    //指数
      };

class Polynomial:public list <term>
{
public:
	Polynomial(term *p,int n):list(p,n,0){}
	void print();
	void add(Polynomial &A);
	double cal(double x);
};
double Polynomial::cal(double x)
{
	double sum=0;
	node <term> *p=getheader()->next;
	while(p!=NULL)
	{
		sum+=p->data.coef*(pow(x,double(p->data.coef)));
		p=p->next;
	}
	return sum;
}
void Polynomial::print()
{
	node <term> *p=getheader()->next;
	int i=1;
	while(p!=NULL)
	{
		cout<<"第"<<i<<"项"<<"系数:"<<p->data.coef<<',';
		cout<<"指数:"<<p->data.expn<<",\n";
		p=p->next;
		i++;
	}
}
void Polynomial::add(Polynomial &A)
{
	 node <term> *p_prior=getheader();
	 node <term> *p=p_prior->next;
	 node <term> *q=A.getheader();
	 while(p&&q)
		{ if(p->data.expn<q->data.expn)
		 {
			 p_prior=p;
			 p=p->next;
		 }
		 else if (p->data.expn>q->data.expn)
		 {
			 p_prior->next=q;
			 p_prior=q;
			 q=q->next;
			 p_prior->next=p;
		 }
		 else
		 {
			 p->data.coef+=p->data.coef;
			 if(p->data.coef==0)
			 {
				 p_prior->next=p->next;
				 delete p;
				 p=p_prior->next;
			 }
			 else
			 {
				 p_prior=p;
				 p=p_prior->next;
			 }
			 node <term> * temp=q;
			 q=q->next;
			 delete temp;
		 }
}
if (q) p_prior=q;
}
Polynomial NewPolynomial()
{
	int n;
	cout<<"输入项数";
	cin>>n;
	struct term *p=new term[n];
	for(int i=0;i<n;i++)
	{
		cout<<"请输入第"<<i+1<<"项的系数与指数,二者以空格间隔开";
		cin>>p[i].coef>>p[i].expn;
	}
	Polynomial new_polynomial(p,n);
	return new_polynomial;
}
int main()
{
	Polynomial A=NewPolynomial();
	Polynomial B=NewPolynomial();
	cout<<A.cal(3);
	A.add(B);
	A.print();
	return 0;
}
