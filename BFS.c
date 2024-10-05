#include<stdio.h>
#include<stdlib.h>

struct Node{
    int val;
    struct Node*next;
};
typedef struct Node node;

struct Queue{
    node*front;
    node*rear;
};
typedef struct Queue Queue;


Queue* initialise(){
    Queue*q=(Queue*)malloc(sizeof(Queue));
    q->front=NULL;
    q->rear=NULL;
    return q;
}

node*CreateNode(int val){

    node*newnode=(node*)malloc(sizeof(node));
    newnode->next=NULL;
    newnode->val=val;
    return newnode;

}
int isEmpty(Queue*q){
    if(q->front==NULL)return 1;
    return 0;
}

void EnQueue(Queue*q,int val){
    node*newnode=CreateNode(val);
    if(q->front==NULL){
        q->front=q->rear=newnode;
        return;
    }
    q->rear->next=newnode;
    q->rear=q->rear->next;
}

int DeQueue(Queue*q){

    if(isEmpty(q)){
        printf("Queue is Empty\n");
        return -1;
    }

    node*temp=q->front;
    int tempVal=temp->val;
    q->front=q->front->next;

    if(q->front==NULL)q->rear=NULL;

    free(temp);

    return tempVal;
}

void BFS(int size,int A[][size],int start){

    int visited[size];
    for(int i=0;i<size;i++)visited[i]=0;

    Queue*q=initialise();

    EnQueue(q,start);
    visited[start]=1;
    
    while(!isEmpty(q)){

        int temp=DeQueue(q);
        printf("%d ",temp);

        for(int i=0;i<size;i++){
            
            if(A[temp][i]==1 && visited[i]!=1){
                visited[i]=1;
                EnQueue(q,i);
            }
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
    int start;
    scanf("%d",&start);
    BFS(size,A,start);
    return 0;
}