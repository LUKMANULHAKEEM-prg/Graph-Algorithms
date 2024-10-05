#include<stdio.h>
#include<stdlib.h>

void DFS(int size,int A[][size],int start,int visited[]){
    if(visited[start]==0){
        printf("%d ",start);
        visited[start]=1;
        for(int i=0;i<size;i++){
            DFS(size,A,i,visited);
        }
    }
}

int main(){
    int size;
    scanf("%d",&size);

    int A[size][size];
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            scanf("%d",&A[i][j]);
        }
    }

    int visited[size];
    for(int i=0;i<size;i++)visited[i]=0;
    DFS(size,A,0,visited); // "0" is the node that we are starting from.
}