#include<stdio.h>
#include<conio.h>

int main()
{
	int a[10][10],i,j,b[10][10],c[10][10];
	float v,b1,b2,b3,b4,temp,a1,a2,a3,a4,a5,a6;
	printf("Enter the 3 X 3 Matrix - \n");
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			scanf("%d",&a[i][j]);
	
	if(a[0][0] >= a[1][0] && a[0][1] >= a[1][1] && a[0][2] >= a[1][2] && a[0][0] >= a[2][0] && a[0][1] >= a[2][1] && a[0][2] >= a[2][2] && a[1][0] >= a[2][0] && a[1][1] >= a[2][1] && a[1][2] >= a[2][2])
	{
		b[0][0]=a[0][0];
		b[0][1]=a[0][1];
		b[0][2]=a[0][2];
		b[1][0]=a[1][0];
		b[1][1]=a[1][1];
		b[1][2]=a[1][2];
	}
	else if(a[0][0] >= a[1][0] && a[0][1] >= a[1][1] && a[0][2] >= a[1][2] && a[0][0] >= a[2][0] && a[0][1] >= a[2][1] && a[0][2] >= a[2][2] && a[2][0] >= a[1][0] && a[2][1] >= a[1][1] && a[2][2] >= a[1][2])
	{
		b[0][0]=a[0][0];
		b[0][1]=a[0][1];
		b[0][2]=a[0][2];
		b[1][0]=a[2][0];
		b[1][1]=a[2][1];
		b[1][2]=a[2][2];
	}
	else
	{
		b[0][0]=a[1][0];
		b[0][1]=a[1][1];
		b[0][2]=a[1][2];
		b[1][0]=a[2][0];
		b[1][1]=a[2][1];
		b[1][2]=a[2][2];
	}
	
	printf("\nAfter Appling Dominance property Row Wise \n");
	for(i=0;i<2;i++)
	{
		for(j=0;j<3;j++)
			printf("%d ",b[i][j]);
		printf("\n");	
	}
	
	if(b[0][0] >= b[0][1] || b[0][0] >= b[0][2] || b[0][1] >= b[0][2] || b[1][0] >= b[1][1] || b[1][0] >= b[1][2] || b[1][1] >= b[1][2])
	{
		c[0][0]=b[0][1];
		c[0][1]=b[0][2];
		c[1][0]=b[1][1];
		c[1][1]=b[1][2];
	}
	else if(b[0][1] >= b[0][0] || b[0][0] >= b[0][2] || b[0][1] >= b[0][2] || b[1][1] >= b[1][0] || b[1][0] >= b[1][2] || b[1][1] >= b[1][2])
	{
		c[0][0]=b[0][0];
		c[0][1]=b[0][2];
		c[1][0]=b[1][0];
		c[1][1]=b[1][2];
	}
	else
	{
		c[0][0]=b[0][0];
		c[0][1]=b[0][1];
		c[1][0]=b[1][0];
		c[1][1]=b[1][1];
	}
	
	
	printf("\nAfter Appling Dominance property Column Wise \n");
	for(i=0;i<2;i++)
	{
		for(j=0;j<2;j++)
			printf("%d ",c[i][j]);
		printf("\n");	
	}
	
	if (c[0][0]>c[0][1])
		a1 = c[0][0]-c[0][1];
	else
		a1 = c[0][1]-c[0][0];	
	
	if (c[1][0]>c[1][1])
		a2 = c[1][0]-c[1][1];
	else
		a2 = c[1][1]-c[1][0];
		
	if (c[0][0]>c[1][0])
		a3 = c[0][0]-c[1][0];
	else
		a3 = c[1][0]-c[0][0];
		
	if (c[0][1]>c[1][1])
		a4 = c[0][1]-c[1][1];
	else
		a4 = c[1][1]-c[0][0];	
					
	a5 = a1+a2;
	a6 = a3+a4;
		
	b1 = a1/a5;
	b2 = a2/a5;
	b3 = a3/a6;
	b4 = a4/a6;	
	
	temp = b1;
	b1=b2;
	b2=temp;
	
	temp = b3;
	b3=b4;
	b4=temp;
	
	v = c[0][0]*b1*b3 + c[0][1]*b1*b4 + c[1][0]*b2*b3 + c[1][1]*b2*b4;
	
	printf("\nThe value of the Game is : %f",v);
	
	return 0;
					
}
