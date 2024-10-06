#include<stdio.h>
#include<stdlib.h>

int checkForCycle(int vertices,int A[][vertices],int visited[],int start,int prev){
    if(visited[start]==1)return 1;

    visited[start]=1;

    for(int i=0;i<vertices;i++){
        if(A[start][i]==1 && i!=prev){
            if(checkForCycle(vertices,A,visited,i,start)) return 1;
        }
    }
    return 0;
}

int main(){

    int vertices;
    scanf("%d",&vertices);
    int A[vertices][vertices];

    int visited[vertices];

    for(int i=0;i<vertices;i++){
        for(int j=0;j<vertices;j++)scanf("%d",&A[i][j]);
        visited[i]=0;
    }

    int flag=0;
    for(int i=0;i<vertices;i++){
        if(visited[i]!=1){
            flag=checkForCycle(vertices,A,visited,i,-1);
            if(flag)break;
        }
    }

    if(flag)printf("cycle is present\n");
    else printf("cycle is not there\n");

    return 0;
}