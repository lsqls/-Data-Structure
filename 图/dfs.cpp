#include <iostream>
#define vNum 4
using namespace std;
void dfs(int arc[][vNum])
{
	int stack[128];
	bool visited[128]={false};	
	bool link;
	int top=-1;
	stack[++top]=1;
	while(top!=-1)
	{	
		link=false;
		for(int j=0;j<vNum;++j)
			{
				if(arc[stack[top]][j]==1&&visited[j]==false)
					{
						visited[j]=true;
						stack[++top]=j;
						cout<<j<<' ';
						link=true;
						break;
					}
			}
		if(!link)
		{
			top--;
		}
	}	
}
int main()
{
	int arc[vNum][vNum]=
	{
		0,1,0,0,
		1,0,0,1,
		0,0,0,1,
		0,1,1,1
	};
	dfs(arc);
	return 0;
}

