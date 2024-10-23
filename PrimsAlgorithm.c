#include<stdio.h>
#include<stdlib.h>

struct node{
    int u;
    int v;
    int weight;
};

typedef struct node node;

struct PriorityQueue{
    node*heap;
    int position;
};

typedef struct PriorityQueue Queue;

Queue*createPriorityQueue(int vertices){
    Queue*pq=(Queue*)malloc(sizeof(Queue));
    pq->heap=(node*)malloc(3*vertices*sizeof(node));
    pq->position=-1;
    return pq;
}



void swap(node*x,node*y){
    node temp=*x;
    *x=*y;
    *y=temp;
}
void heapify_down(Queue*pq,int index){
    int smallest=index;
    int left=2*index+1;
    int right=2*index+2;

    if(left<=pq->position && pq->heap[left].weight < pq->heap[smallest].weight)smallest=left;
    if(right<=pq->position && pq->heap[right].weight < pq->heap[smallest].weight)smallest=right;

    if(index!=smallest){
        swap(&pq->heap[index],&pq->heap[smallest]);
        heapify_down(pq,smallest);
    }
}

void heapify_up(Queue*pq,int index){
    while(index>0 && pq->heap[index].weight < pq->heap[(index-1)/2].weight){
        swap(&pq->heap[index],&pq->heap[(index-1)/2]);
        index=(index-1)/2;
    }
}

node ExtractMin(Queue*pq){
    node temp=pq->heap[0];
    swap(&pq->heap[0],&pq->heap[pq->position]);
    pq->position--;
    heapify_down(pq,0);
    return temp;
}

void Prims_algorithm(int vertices,int A[][vertices],int source,int flag){
    int visited[vertices];
    for(int i=0;i<vertices;i++)visited[i]=0;
    Queue*pq=createPriorityQueue(vertices);
    pq->position++;
    pq->heap[0].u=-1;
    pq->heap[0].v=source;
    pq->heap[0].weight=0;
    int sum=0;

    while(pq->position!=-1){
        node temp=ExtractMin(pq);
        if(!visited[temp.v]){
            visited[temp.v]=1;
            if(temp.u!=-1 && flag){
                printf("%d %d (%d) ",temp.u,temp.v,temp.weight);
            }else{
                sum+=temp.weight;
            }
            for(int i=0;i<vertices;i++){
                if(A[temp.v][i] && !visited[i]){
                    pq->position++;
                    pq->heap[pq->position].u=temp.v;
                    pq->heap[pq->position].v=i;
                    pq->heap[pq->position].weight=A[temp.v][i];
                    heapify_up(pq,pq->position);
                }
            }
        }
    }
    if(flag==0)printf("%d\n",sum);

}

// s followed by an integer(source) will give the shortest path from source to any vertices.
// b will give the shortest distance from the source to any vetices.
// e to terminate the program.

int main(){
    int vertices;
    scanf("%d",&vertices);

    int A[vertices][vertices];

    for(int i=0;i<vertices;i++){
        for(int j=0;j<vertices;j++)scanf("%d",&A[i][j]);
    }

    int source;
    char ch='i';
    do{
        scanf("%c",&ch);
        switch(ch){
            case 's':
            scanf("%d",&source);
            Prims_algorithm(vertices,A,source,1);
            printf("\n");
            break;

            case 'b':
            Prims_algorithm(vertices,A,source,0);
            break;
        }
    }while(ch!='e');
    return 0;

}