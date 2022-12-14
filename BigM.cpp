#include<iostream>
#define M 1000
#define MAX 100
using namespace std;
long double A[MAX][MAX];

void simpfunc(int m,int n,int p)
{
  	int j,i;
  	for(j = 1; j<=n+p+1; j++)
    {
      	for(i =1; i<=m; i++)
		{
	  		A[m+1][j] = A[m+1][j] - M*A[i][j];
		}
    }
}

void input(int m,int n,int p)
{
  	int i,j,count=1,t=1;
  	char r;
  	double x;
  	cout<<"\nMaximize (Y/N)  :  ";
  	cin>>r;
  	if((r == 'Y')|| (r == 'y'))
    {
      t=-1;
    }
  	for (i=1;i<=m;i++) 
    {
      	cout<<"\nCONSTRAINT "<<i<<"  :  \n";
      	cout<<"\nWhether type \">=\" (Y/N)   :  ";
      	cin>>r;
      	for (j = 1; j<=n; j++) 
		{
			cout<<"Coefficient of x"<<j<<"  :  "; 
			cin>>x;
			A[i][j] = x;
      	}
      	if(r=='y'||r=='Y')
		{
	  		for(j = 1; j<=p; j++)
	    	{
	      		A[i][n+j]=0;
	    	}
	  		A[i][n+count]=-1;
	  		count++;
		}
      	else
		{
	  		for(j = 1; j<=p; j++)
	    	{
	      		A[i][j+n]=0;
	    	}
		}
      	cout<<"Constant  :  "; 
      	cin>>A[i][n+p+1];
    }
  	cout<<"\nInput for the function  :  \n";
  	for (j=1;j<=n;j++) 
    {
    	cout<<"Coefficient of x"<<j<<"  :  "; 
      	cin>>x;
      	A[m+1][j] = x*t;
    }
  	for(j = 1; j<=p; j++)
    {
      	A[i][j+n]=0;
    }
  	A[m+1][n+1]=1;
  	simpfunc(m,n,p);
}
int pivcol(int m,int n,int p)
{
  	int i,pos=1;
  	double min=A[m+1][1];
  	for(i=1;i<=n+p;i++)
    {
      	if(min>A[m+1][i])
		{
	  		min = A[m+1][i];
	  		pos = i;
		}
    }
  	return pos;
}
int pivrow(int m,int n,int p,int pos)
{
  	int i,piv = 1;
  	double min = (A[1][n+p+1]/A[1][pos]);
  	for(i=1;i<=m;i++)
    {
      	if(min>(A[i][n+p+1]/A[i][pos]))
		{
	  		if(A[i][pos]>0)
	    	{
	      		piv = i;
	    	}
		}
    }
  	return piv;
}
int optimise(int m,int n,int p)
{
  	int i,j,pivr,pivc;
  	pivc = pivcol(m,n,p);
  	pivr = pivrow(m,n,p,pivc);
  	for(i=1;i<=m+1;i++)
    {
      	for(j=1;j<=n+p+1;j++)
		{
	  		if((i!=pivr)&&(j!=pivc))
	    	{
	      		A[i][j] = (((A[i][j]*A[pivr][pivc])-(A[i][pivc]*A[pivr][j]))/A[pivr][pivc]);
	    	}
		}
    }
  	for(i=1;i<=m+1;i++)
    {
      	if(pivr!=i)
		{
	  		A[i][pivc] = -A[i][pivc]/A[pivr][pivc];
		}
    }
  	for(j=1;j<=n+p+1;j++)
    {
      	if(pivc!=j)
		{
	  		A[pivr][j] = A[pivr][j]/A[pivr][pivc];
		}
    }   
  	A[pivr][pivc] = 1/A[pivr][pivc];
  	double temp = A[pivr][n+p+2];
  	A[pivr][n+p+2] = A[0][pivc];
  	A[0][pivc] = temp;
}
void result(int m,int n,int p)
{
  	cout<<"\nThe Basic Variables  :  \n";
  	for(int i=1;i<=m;i++)
    {
      	cout<<"\nx"<<A[i][n+p+2]<<"  =  "<<A[i][n+p+1];
    }
  	cout<<"\n\nMax Value  :  "<<A[m+1][n+p+1]<<endl<<endl;
  	if(A[m+1][n+p+1]<0)
  	cout<<"Min Value  :  "<<A[m+1][n+p+1]*(-1);
}

void altsimplex(int m,int n,int p)
{
  	int i,j,z=1;
  	for(j = 1; j<=n+p ; j++)
    {
      	if(A[m+1][j]==0)
		{
	  		z=0;
		}
    }
  	if(z==0)
    {
      	optimise(m,n,p);
      	cout<<"\n\nAlternate Solution   : \n";
      	result(m,n,p);
    }
}
int simplex(int m,int n,int p)
{
  	int j,x,z=0;
  	for(j=1;j<=n+p;j++)
    {
      	if(A[m+1][j]<=0)
		{
	  		z=1;
		}
    }
  	while(z==1)
    {
      	optimise(m,n,p);
      	z=0;
      	for(j=1;j<=n+p;j++)
		{
	  		if(A[m+1][j]<0)
	    	{
	      		z=1;
	    	}
		}
    }
  	result(m,n,p);
  	altsimplex(m,n,p);
  	return 0;
}

int main()
{
  	int i,j,n,m,p;
  	cout<<"Enter the no. of variables of the function  :  ";
  	cin>>n;
  	cout<<"\nEnter the no. of constraints  :  ";
  	cin>>m;
  	cout<<"\nEnter the no. of >= sign  :  ";
  	cin>>p;
  	input(m,n,p);
  	for(i=1;i<=n+p;i++)
    {
      	A[0][i]=i;
    }
  	for(j=1;j<=m;j++)
    {
      	A[j][n+p+2]=i++;
    }
  	simplex(m,n,p);
  	return 0;
}
