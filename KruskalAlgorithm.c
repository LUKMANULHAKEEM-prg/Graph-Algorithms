#include<stdio.h>
#include<stdlib.h>

struct node {
    int val;
    int weigth;
    struct node*next;
};

typedef struct node node;
node*createNode(int val,int weight){
    node*newnode=(node*)malloc(sizeof(node));
    newnode->next=NULL;
    newnode->val=val;
    newnode->weigth=0;
    return newnode;
}

struct graph{
    node**list;
    int vertices;
};

typedef struct graph graph;

graph*createGraph(int vertices){
    graph*g=(graph*)malloc(sizeof(graph));
    g->list=(node**)malloc(vertices*sizeof(node*));
    for(int i=0;i<vertices;i++)g->list[i]=NULL;
    g->vertices=vertices;
    return g;
}

void insert(graph*g,int index,int edgeTo){
    if(g->list[index]==NULL){
        g->list[index]=createNode(edgeTo,0);
        return;
    }
    node*temp=g->list[index];
    while(temp->next){
        temp=temp->next;
    }
    temp->next=createNode(edgeTo,0);
    return;
}

void updateWeight(graph*g,int index,int weight){
    node*temp=g->list[index];
    while(temp && temp->weigth!=0){
        temp=temp->next;
    }
    temp->weigth=weight;
    return;
}

void printgraph(graph*g){
    for(int i=0;i<g->vertices;i++){
        node*temp=g->list[i];
        while(temp){
            printf("%d --> %d(%d) ",i,temp->val,temp->weigth);
            temp=temp->next;
        }
        printf("\n");
    }
}

struct edge{
    int u;
    int v;
    int weight;
};
typedef struct edge edge;

struct PriorityQueue{
    edge*heap;
    int position;
    int size;
};

typedef struct PriorityQueue Queue;

Queue*createPriorityQueue(int size){
    Queue*pq=(Queue*)malloc(sizeof(Queue));
    pq->heap=(edge*)malloc(20*size*sizeof(edge));
    pq->position=-1;
    pq->size=size;
    return pq;
}

void swap(edge*x,edge*y){
    edge temp=*x;
    *x=*y;
    *y=temp;
}

void heapify_up(Queue*pq,int index){
    while(index>0 && pq->heap[index].weight < pq->heap[(index-1)/2].weight){
        swap(&pq->heap[index],&pq->heap[(index-1)/2]);
        index=(index-1)/2;
    }
}

void heapify_down(Queue*pq,int index){
    int left=2*index+1;
    int right=2*index+2;
    int smallest=index;

    if(left<=pq->position && pq->heap[left].weight < pq->heap[smallest].weight)smallest=left;
    if(right<=pq->position && pq->heap[right].weight < pq->heap[smallest].weight)smallest=right;

    if(index!=smallest){
        swap(&pq->heap[index],&pq->heap[smallest]);
        heapify_down(pq,smallest);
    }
}

edge ExtractMin(Queue*pq){
    edge temp=pq->heap[0];
    swap(&pq->heap[0],&pq->heap[pq->position]);
    pq->position--;
    heapify_down(pq,0);
    return temp;
}

int find(int parent[],int temp){
    if(parent[temp]==temp)return temp;
    return parent[temp]=find(parent,parent[temp]);
}

void unionofedge(edge temp,int parent[],int rank[],int vertices){

    int up=find(parent,temp.u);
    int vp=find(parent,temp.v);

    if(rank[up] > rank[vp]){
        parent[vp]=up;
    }else if(rank[up] < rank[vp]){
        parent[up]=vp;
    }else{
        if(temp.u > temp.v){
            parent[vp]=up;
            rank[up]++;
        }else{
            parent[up]=vp;
            rank[vp]++;
        }
    }
}

void kruskals_algorithm(graph*g){

    Queue*pq=createPriorityQueue(g->vertices);
    for(int i=0;i<g->vertices;i++){
        node*temp=g->list[i];
        while(temp){
            pq->position++;
            pq->heap[pq->position].u=i;
            pq->heap[pq->position].v=temp->val;
            pq->heap[pq->position].weight=temp->weigth;
            heapify_up(pq,pq->position);
            temp=temp->next;
        }
    }

    //for(int i=0;i<=pq->position;i++)printf("%d ",pq->heap[i].weight);

    int parent[g->vertices];
    int rank[g->vertices];
    int sum=0;
    for(int i=0;i<g->vertices;i++){
        parent[i]=i;
        rank[i]=0;
    }

    while(pq->position!=-1){
        edge temp=ExtractMin(pq);

        int up=find(parent,temp.u);
        int vp=find(parent,temp.v);

        if(up!=vp){
            sum+=temp.weight;
            unionofedge(temp,parent,rank,g->vertices);
        }
    }

    printf("%d\n",sum);
}

int main(){
    int vertices;
    scanf("%d",&vertices);

    int index;
    int edgeTo;
    char ch;

    graph*g=createGraph(vertices);


    for(int i=0;i<vertices;i++){
        scanf("%d",&index);
        scanf("%c",&ch);
        while(ch!='\n'){
            scanf("%d",&edgeTo);
            scanf("%c",&ch);
            insert(g,index,edgeTo);
        }
    }

    for(int i=0;i<vertices;i++){
        scanf("%d",&index);
        scanf("%c",&ch);
        while(ch!='\n'){
            scanf("%d",&edgeTo);
            scanf("%c",&ch);
            updateWeight(g,index,edgeTo);
        }
    }

    //printgraph(g);
    kruskals_algorithm(g);
    return 0;
}