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

int CheckForBipartite(int vertices,int A[][vertices],int start,int color[]){


    Queue*q=initialise();
    EnQueue(q,start);
    color[start]=1;

    while(!isEmpty(q)){

        int temp=DeQueue(q);
        int currColor=color[temp];

        for(int i=0;i<vertices;i++){

            if(A[temp][i]==1){
                if(color[i]==0){

                    EnQueue(q,i);
                    color[i]=(currColor==1) ? 2 : 1;
                    
                }else if(color[i]==currColor)return 0;
                else continue;
            }
        }
    }

    return 1;
}

int main(){

    int vertices;
    scanf("%d",&vertices);

    int A[vertices][vertices];
    int color[vertices];

    for(int i=0;i<vertices;i++){
        for(int j=0;j<vertices;j++){
            scanf("%d",&A[i][j]);
        }
        color[i]=0;
    }
    
    int flag=0;

    for(int i=0;i<vertices;i++){
        if(color[i]==0){
            flag=CheckForBipartite(vertices,A,i,color);
            if(flag==0){
                printf("not bipartite graph\n");
                return 0;
            }
        }
    }

    if(flag)printf("bipartite graph\n");

    return 0;

}