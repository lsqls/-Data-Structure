//¶ÑÕ» 
#include <iostream>
#include <malloc.h>
#define maxsize 100
using namespace std;
struct node
{
	int data[maxsize];
	int top;
};
typedef node*  stack;
void push(stack L,int item)
{
	if(L->top==maxsize-1)
	cout<<"Õ»Âú";
	else
	 L->data[++(L->top)]=item;
 } 
 void pop(stack L)
 {
 	if (L->top<0)
 	cout<<"Õ»¿Õ";
	 else 
	  {
	  cout<<"delete data["<<L->top<<']'<<'\n';
	  (L->top)--;
		}	
	  
 }

int main()
{	node ex;
ex.top=-1;
	for(int i=0;i<50;i++)
		push(&ex,i+i*i+100);
	for(int i=0;i<50;i++)
		cout<<ex.data[i];
	cout<<endl;
	for(int i=0;i<50;i++)
		pop(&ex);
	return 0; 
}


