#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
int cost,i,j,msizerow,msizecol,matrix[10][10];
int r=0,c=0,p;
int supply[10],demand[10];
int value[10][10],rpos,cpos,rpre,cpre;
void firstiteration();

main()
{
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            value[i][j]=0;
        }
    }
    printf("\n Enter the size of the matrix(rows)=");
    scanf("%d",&msizerow);
    printf("\n Enter the size of the matrix(column)=");
    scanf("%d",&msizecol);
    printf("\n Enter the cost matrix=");
    for(r=0;r<msizerow;r++)
    {
        for(c=0;c<msizecol;c++)
        {
            printf("\n Enter %d row %d column=",r+1,c+1);
            scanf("%d",&matrix[r][c]);
        }
    }
  printf("\n Enter the supply=\n");
  for(r=0;r<msizerow;r++)
  {
        printf("%d =",r+1);
        scanf("%d",&supply[r]);
  }
  printf("\n Enter the Demand=\n");
  for(c=0;c<msizecol;c++)
  {
        printf("%d =",c+1);
        scanf("%d",&demand[c]);
  }
  firstiteration();
  getch();
 }
 void firstiteration()
 {
    c=0;r=0;cost=0;
    do{
        if(demand[c]!=0)
        {
            if(demand[c]<supply[r])
            {
                value[r][c]=demand[c];
                supply[r]-=demand[c];
                demand[c]=0;
                if(c==msizecol-1)
                    c=0;
                else
                    c++;
            }
            else
            {
                if(demand[c]==supply[r])
                {
                    value[r][c]=supply[r];
                    demand[c]=0;
                    supply[r]=0;
                    if(c==msizecol-1)
                        c=0;
                    else
                        c++;
                    if(r==msizerow-1)
                        r=0;
                    else
                        r++;
                }
                else
                {
                    value[r][c]=supply[r];
                    demand[c]-=supply[r];
                    if(r==msizerow-1)
                        r=0;
                    else
                        r++;
                }
            }
        }
        else
        {
            if(c==msizecol-1)
                c=0;
            else
                c++;
        }
    }
        while(demand[msizecol-1]!=0);
        printf("\n");
        for(r=0;r<msizerow;r++)
        {
            for(c=0;c<msizecol;c++)
            {
                //printf("\n Value[%d][%d]=%d",r+1,c+1,value[r][c]);
            }
        }


         printf("\n The Transportation Problem \n");
      for(r=0;r<msizerow;r++)
         {
            for(c=0;c<msizecol;c++)
            {
                printf("\t%d",matrix[r][c]);
                //cost+=matrix[r][c]*value[r][c];
            }
         printf("\n");
        }





         printf("\n The Initial Matrix \n");
      for(r=0;r<msizerow;r++)
         {
            for(c=0;c<msizecol;c++)
            {
                printf("\t%d",value[r][c]);
                //cost+=matrix[r][c]*value[r][c];
            }
         printf("\n");
        }
        for(r=0;r<msizerow;r++)
         {
            for(c=0;c<msizecol;c++)
            {
                cost+=matrix[r][c]*value[r][c];
            }
        }
      printf("\n Cost=%d",cost);
 }
