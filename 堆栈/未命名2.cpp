#include <iostream>//链式结构实现堆栈 
#include <malloc.h>
using namespace std;
typedef struct snode* stack; 
struct snode{
	int data;
	stack next;
};
int main()
{
	return 0;
}
stack create()
{
	stack s;
	s=(stack)malloc(sizeof(struct snode));
	s->next=NULL;
	return s;
}
int isempty(stack s)
{
	return (s->next==NULL);
}
void push(int item,stack s) 
{
	stack p;
	p=(stack)malloc(sizeof(snode));
	p->data=item;
	p->next=s->next;
	s->next=p;
}
int pop(stack s)
{
	stack p;
	int itop;
	if(isempty(s))
	{
		cout<<"堆栈空";
	}
	else
	{
		p=s->next;
		s->next=p->next;
		itop=p->data;
		free(p);
		return itop;
	}
}

