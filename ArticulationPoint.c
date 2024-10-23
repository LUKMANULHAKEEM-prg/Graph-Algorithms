#include<stdio.h>
#include<stdlib.h>

void dfs(int i,int parent,int visited[],int discover[],int low[],int mark[],int*timer,int vertices,int A[][vertices]){
    visited[i]=1;
    discover[i]=low[i]=(*timer);
    (*timer)++;
    int count=0;

    for(int j=0;j<vertices;j++){
        if(i==j)continue;
        if(A[i][j]){
            count++;
            if(!visited[j]){
                dfs(j,i,visited,discover,low,mark,timer,vertices,A);
                if(low[i] > low[j])low[i]=low[j];
                if(discover[i] >= low[j] && parent!=-1)mark[i]=1;
            }else{
                if(discover[j] < low[i])low[i]=discover[j];
            }
        }
    }

    if(count>1 && parent==-1){
        mark[i]=1;
    }
}

void articulation(int vertices,int A[][vertices]){
    int low[vertices];
    int discover[vertices];
    int visited[vertices];
    int mark[vertices];
    for(int i=0;i<vertices;i++){
        visited[i]=0;
        low[i]=0;
        discover[i]=0;
        mark[i]=0;
    }

    int timer=0;
    for(int i=0;i<vertices;i++){
        if(!visited[i]){
            dfs(i,-1,visited,discover,low,mark,&timer,vertices,A);
        }
    }
    int count=0;
    for(int i=0;i<vertices;i++)if(mark[i]==1)count++;
    printf("%d\n",count);
}
int main(){
    int vertices;
    scanf("%d",&vertices);

    int A[vertices][vertices];
    for(int i=0;i<vertices;i++){
        for(int j=0;j<vertices;j++)scanf("%d",&A[i][j]);
    }

    articulation(vertices,A);
    return 0;
}