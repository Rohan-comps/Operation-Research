#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<iomanip>
#include<stdlib.h>
#define MAX 50
using namespace std;

enum boolean{FALSE,TRUE};
class lcmethod{
    int data[MAX][MAX];
    int requered[MAX];
    int capacity[MAX];
    int allocation[MAX][MAX];
    int no_of_rows,no_of_columns,no_of_allocation;
    public:
        lcmethod(){
            for(int i=0;i<MAX;i++){
                capacity[i]=0;
                requered[i]=0;
                for(int j=0;j<MAX;j++){
                    data[i][j]=0;
                    allocation[i][j]=0;
                }
            }
            no_of_rows=no_of_columns=no_of_allocation=0;
        }
        void setColumn(int no){no_of_columns=no;};
        void setRow(int no){no_of_rows=no;}
        void getData();
        void getCapacity();
        void getRequiredValue();
        void makeAllocation();
        boolean checkValue(int [],int);
        int getMinVal(int [][MAX]);
        int getTotalMinVal(int [][MAX],int);
        void getMinValsPos(int,int [][MAX],int[][2],int [][2]);
        void display();
};
void lcmethod::getMinValsPos(int value,int temp_data[][MAX],int ans[][2],int pos[][2]){
    int k=0;
    for(int i=0;i<no_of_rows;i++)
        for(int j=0;j<no_of_columns;j++)
            if(temp_data[i][j]==value){
                ans[k][0]=i;
                ans[k][1]=j;
                pos[k][0]=requered[j];
                pos[k++][1]=capacity[i];
            }
}
int lcmethod::getTotalMinVal(int temp_data[][MAX],int value){
    int no=0;
    for(int i=0;i<no_of_rows;i++)
        for(int j=0;j<no_of_columns;j++)
            if(temp_data[i][j]==value)
                no++;
    return no;
}
int lcmethod::getMinVal(int temp_data[][MAX]){
    int min=temp_data[0][0];

    for(int i=0;i<no_of_rows;i++)
        for(int j=0;j<no_of_columns;j++)
            if(temp_data[i][j]<min)
                min=temp_data[i][j];

    return min;
}
boolean lcmethod::checkValue(int arr[],int no){
    for(int i=0;i<no;i++)
        if(arr[i]!=0)
            return FALSE;
    return TRUE;
}
void arrayCopy(int start,int end,int array1[],int start1,int array2[]){
    for(int i=start,j=start1;i<end;i++,j++)
        array2[j]=array1[i];
}
int getTotal(int array[],int no){
    int sum=0;
    for(int i=0;i<no;i++)
        sum+=array[i];
    return sum;
}
void copy2DArray(int startRow,int startCol,int endRow,int endCol,int array[][MAX],int start1Row,int start1Col,int ans[][MAX]){
    for(int i=startRow,k=start1Row;i<endRow;i++,k++)
        for(int j=startCol,l=start1Col;j<endCol;j++,l++)
            ans[k][l]=array[i][j];
}
int getMaxVal(int array[MAX],int no){
    int max=0;
    for(int i=0;i<no;i++)
        if(array[i]>max)
            max=array[i];
    return max;
}
int getMaxValPos(int array[MAX],int no,int value){
    for(int i=0;i<no;i++)
        if(value==array[i])
            return i;
    return -1;
}
void lcmethod::makeAllocation(){
    int i=0,j=0,min,total_min;
    int temp_requered[MAX]={0};
    int temp_capacity[MAX]={0};
    int temp_data[MAX][MAX]={0};
    int position[MAX][2]={0};
    int dataPos[MAX][2]={0};
    int sum_of_cap,sum_of_req;
    sum_of_cap=getTotal(capacity,no_of_rows);
    sum_of_req=getTotal(requered,no_of_columns);
    if(sum_of_cap!=sum_of_req){
        if(sum_of_cap>sum_of_req){
            for(j=0;j<no_of_rows;j++)
                data[j][no_of_columns]=0;
            requered[no_of_columns]=sum_of_cap-sum_of_req;
            no_of_columns++;
        }
        else{
            for(j=0;j<no_of_columns;j++)
                data[no_of_rows][j]=0;
            capacity[no_of_rows]=sum_of_req-sum_of_cap;
            no_of_rows++;
        }
    }
    i=j=0;
    arrayCopy(0,no_of_rows,capacity,0,temp_capacity);
    arrayCopy(0,no_of_columns,requered,0,temp_requered);
    copy2DArray(0,0,no_of_rows,no_of_columns,data,0,0,temp_data);
    while(!checkValue(temp_capacity,no_of_rows) || !checkValue(temp_requered,no_of_columns)){
        min=getMinVal(temp_data);
        total_min=getTotalMinVal(temp_data,min);
        getMinValsPos(min,temp_data,position,dataPos);
        int minPosValue[MAX]={0};
        for(i=0;i<no_of_rows;i++){
            if(dataPos[i][0]<dataPos[i][1])
                minPosValue[i]=dataPos[i][0];
            else
                minPosValue[i]=dataPos[i][1];
        }
        int max=getMaxVal(minPosValue,total_min);
        int maxvalPos=getMaxValPos(minPosValue,total_min,max);
        i=position[maxvalPos][0];
        j=position[maxvalPos][1];
        if(temp_capacity[i]>temp_requered[j]){
            allocation[i][j]=temp_requered[j];
            for(int k=0;k<no_of_rows;k++)
                temp_data[k][j]=9999;
            temp_capacity[i]-=temp_requered[j];
            temp_requered[j]=0;
        }
        else if(temp_capacity[i]<temp_requered[j]){
            allocation[i][j]=temp_capacity[i];
            for(int k=0;k<no_of_columns;k++)
                temp_data[i][k]=9999;
            temp_requered[j]-=temp_capacity[i];
            temp_capacity[i]=0;
        }
        else{
            int k;
            allocation[i][j]=temp_capacity[i];
            for(k=0;k<no_of_rows;k++)
                temp_data[k][j]=9999;
            for(k=0;k<no_of_columns;k++)
                temp_data[i][k]=9999;
            temp_requered[j]=temp_capacity[i]=0;
        }
        no_of_allocation++;
    }
}
void lcmethod::getCapacity(){
    cout<<"Enter Supply Values : \n";
    for(int i=0;i<no_of_rows;i++){
        cout<<"s"<<i+1<<" : ";
        cin>>capacity[i];
    }
}
void lcmethod::getRequiredValue(){
    cout<<"Enter Demand Values : \n";
    for(int i=0;i<no_of_columns;i++){
        cout<<"d"<<i+1<<" : ";
        cin>>requered[i];

    }
}
void lcmethod::display(){
    int i;
    cout<<"\ngiven data :\n";
    cout<<setw(9);
    for(i=0;i<no_of_columns;i++)
        cout<<"D"<<i+1<<setw(4);
    cout<<setw(5)<<"cap"<<endl<<setw(0);
    for(i=0;i<no_of_rows;i++){
        cout<<setw(3)<<"S"<<i+1;
        for(int j=0;j<no_of_columns;j++)
            cout<<setw(5)<<data[i][j];
        cout<<setw(5)<<capacity[i]<<endl;
    }
    cout<<setw(4)<<"req";
    for(i=0;i<no_of_columns;i++)
        cout<<setw(5)<<requered[i];

    cout<<"\n\n after allocation :\n";
    for(i=0;i<no_of_rows;i++){
        for(int j=0;j<no_of_columns;j++){
            if(allocation[i][j]!=0)
                cout<<setw(5)<<data[i][j]<<"*"<<setw(2)<<allocation[i][j];
            else
                cout<<setw(8)<<data[i][j];
        }
        cout<<endl;
    }
    int k=0,sum=0;
    for(i=0;i<no_of_rows;i++){
        for(int j=0;j<no_of_columns;j++){
            if(allocation[i][j]!=0){
                cout<<"("<<data[i][j]<<" * "<<allocation[i][j]<<")";
                if(k<no_of_allocation-1){
                    cout<<"+";
                    k++;
                }
                sum+=data[i][j]*allocation[i][j];
            }
        }
    }
    cout<<"\nanswer : "<<sum;
}
void lcmethod::getData(){
    cout<<"enter source to destination data:"<<endl;
    for(int i=0;i<no_of_rows;i++){
        cout<<"enter "<<i<<"th row : ";
        for(int j=0;j<no_of_columns;j++){
            cin>>data[i][j];
        }
    }
}
main()
{
    lcmethod lcm;
    int r,c;
    cout<<"Enter no of Rows : ";
    cin>>r;
    cout<<"Enter no of columns : ";
    cin>>c;
    lcm.setColumn(c);
    lcm.setRow(r);
    lcm.getData();
    lcm.getCapacity();
    lcm.getRequiredValue();
    lcm.makeAllocation();
    lcm.display();
    getch();
}
