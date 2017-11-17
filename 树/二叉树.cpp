#include <iostream>
using namespace std;
template <class T>
struct node
{
	T data;
	struct node <T> * lch;
	struct node <T> * rch;
};
template <class T>
class tree
{
private:
	void create(node <T> * &root,T data[],int i,int n);
	void release(node <T> * &root);
	void Data(node <T> * root,T data[],int i,int n);
public:
	node <T> * root;
	tree(T data[],int n);
	tree(tree& B);
	void preorder(node <T> *root);
	void inorder(node <T> *root);
	void postorder(node <T> *root);
	void levelorder(node <T> *root);
	~tree();
};
template <class T>
void tree <T>::create(node <T> * &root,T data[],int i,int n)
{	
	if(i<=n&&data[i])
	{	
		root=new node <T>;
		root->data=data[i];
		create(root->lch,data,2*i,n);
		create(root->rch,data,2*i+1,n);
	}
	else
		root=NULL;
}
template <class T>
void tree <T>::release(node <T> * &root)
{
	if(root!=NULL)
	{
	release(root->lch);
	release(root->rch);
	delete root;
	}
}
template <class T>
void tree <T>::Data(node <T> * root,T data[],int i,int n)
{
	if(root!=NULL)
	{	
		
		data[i]=root->data;
		Data(root->lch,data,2*i,n);
		Data(root->rch,data,2*i+1,n);
	}
	else
		data[i]=0;
}
template <class T>
tree <T>::tree(T data[],int n)
{
	create(root,data,1,n);
}
template <class T>
tree <T>::tree(tree& B)
{
	T data[128];
	Data(B.root,data,1,128);
	create(root,data,1,128);
}
template <class T>
tree <T>::~tree()
{
	release(root);
}
template <class T>
void tree <T>::preorder(node <T> *root)
{
	if(root!=NULL)
	{	
		cout<<root->data<<' ';
		preorder(root->lch);
		preorder(root->rch);
	}
}
template <class T>
void tree <T>::inorder(node <T> *root)
{
	if(root!=NULL)
	{	
		inorder(root->lch);
		cout<<root->data<<' ';
		inorder(root->rch);
	}
}
template <class T>
void tree <T>::postorder(node <T> *root)
{
	if(root!=NULL)
	{	
		postorder(root->lch);
		postorder(root->rch);
		cout<<root->data<<' ';
	}
}
template <class T>
void tree <T>::levelorder(node <T> *root)
{
	node <T> * queen[128];
	int r=0;
	int f=0;
	if(root!=NULL) queen[++r]=root;
	while(r!=f)
	{
		node <T> *p=queen[++f];
		cout<<p->data<<' ';
		if(p->lch)
			queen[++r]=p->lch;
		if(p->rch)
			queen[++r]=p->rch;
	}

}

int main()
{
	char data[128]={0,'a','b','c','d','e','h','i','g','f',0,0,0,0,'k'};
	tree <char> A(data,16);
	A.preorder(A.root);
	cout<<endl;
	A.inorder(A.root);
	cout<<endl;
	A.postorder(A.root);
	cout<<endl;
	A.levelorder(A.root);
	tree <char> B(A);
	cout<<endl;
	B.preorder(B.root);
}

