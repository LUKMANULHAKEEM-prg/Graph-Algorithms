#include<stdio.h>
#include<stdlib.h>

void dfs(int i,int parent,int visited[],int discover[],int low[],int vertices,int A[][vertices],int*timer,int*count){

    visited[i]=1;
    low[i]=discover[i]=(*timer);
    (*timer)++;

    for(int j=0;j<vertices;j++){
        if(j==parent)continue;
        if(A[i][j] && !visited[j]){
            dfs(j,i,visited,discover,low,vertices,A,timer,count);
            if(low[j] < low[i])low[i]=low[j];

            if(discover[i] < low[j])(*count)++;
        }else if(A[i][j]){
            if(low[j ]< low[i])low[i]=low[j];
        }
    }
}

int Tarjan(int vertices,int A[][vertices]){
    int time=0;
    int low[vertices];
    int discover[vertices];
    int visited[vertices];
    for(int i=0;i<vertices;i++){
        visited[i]=0;
        low[i]=0;
        discover[i]=0;
    }

    int count=0;

    for(int i=0;i<vertices;i++){
        if(visited[i]==0){
            dfs(i,-1,visited,discover,low,vertices,A,&time,&count);
        }
    }

    printf("%d\n",count);
    return 0;
}

int main(){
    int vertices;
    scanf("%d",&vertices);

    int A[vertices][vertices];
    for(int i=0;i<vertices;i++){
        for(int j=0;j<vertices;j++)scanf("%d",&A[i][j]);
    }

    Tarjan(vertices,A);
    return 0;
}