#define len 6
#include <iostream>
using std::cout;
bool diff(int* mcolor,int j)
{
	bool mdiff=true;
 for(int i=j-1;i>=0;i--)
 {
 	if(mcolor[i]==mcolor[j])
	{
	mdiff=false;
	break;
	}	
}
return mdiff;
}
int* draw(int matrix[][len],int point_num)
{	
	int* point_color=new int[point_num];
	for(int i=0;i<point_num;i++)
	{	int color=1;
		for(int j=i;j>=0;j--)
		{
			if(matrix[i][j]&&diff(point_color,j))
				color+=1;
		}
		point_color[i]=color;
	}
	return point_color;
}

int main()
{
	int example[6][6]=
{
0,1,0,1,1,1,
1,0,0,0,1,1,
0,0,0,1,1,1,
1,0,1,0,0,1,
1,1,1,0,0,1,
1,1,1,1,1,0
}; 
int* result=draw(example,6);
for(int i=0;i<6;++i)
	cout<<result[i]<<' ';//颜色用数字表示 
return 0;
}




 

