#include <iostream>
#include <malloc.h>
using namespace std;
typedef struct node* list;
struct node{
	int data;
	list next;
};
int length(list L)
{
	list p=L;
	int j=0;
	while(p)
	p=p->next;
	j++;
	return j;
}
list find(int K,list L) 
{
list  p=L;
int i=1;
while(p!=NULL&&i<K)
{
	p=p->next;
	i++;
}
if(i==K)
	return p;
else
	return NULL;
}
list Find(int x,list L)
{
	list p=L;
	while(p->data!=x&&p!=NULL)
	{
	p=p->next;
	}
	return p;
}
void insert(int x,int i,list pt)
{	int j=0;
	list p,a;
	if(i==1)
	{
	a=(list)malloc(sizeof(node));
	a->data=x;
	a->next=pt;
	}		
	p=find(i-1,p);
	if(p==NULL)
	{
		cout<<"参数错误";
	}
else
{
	a=(list)malloc(sizeof(node));
	a->data=x;
	a->next=p->next;
	p->next=a->next;
}
}
	
void Delete(int i,list pr)
{
list p;
p=find(i-1,pr);
s=p->next;
if(p==NULL)
{
	cout<<"参数错误";
}
else
{
	p->next=s->next;
	free(s);
}

}

}
int main()
{
	return 0;
}

