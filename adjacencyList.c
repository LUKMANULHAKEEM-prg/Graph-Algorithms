#include<stdio.h>
#include<stdlib.h>

struct Node{
    int val;
    struct Node*next;
};
typedef struct Node node;

struct Graph{
    int numVertices;
    node**adjacencyList;
};

typedef struct Graph Graph;

node*CreateNode(int val){
    node*newnode=(node*)malloc(sizeof(node));
    newnode->next=NULL;
    newnode->val=val;
    return newnode;
}

Graph*initialseGraph(int vertices){
    Graph*g=(Graph*)malloc(sizeof(Graph));
    g->numVertices=vertices;
    g->adjacencyList=(node**)malloc(vertices*sizeof(node));
    for(int i=0;i<vertices;i++)g->adjacencyList[i]=NULL;
    return g;
}

void insert(Graph*g,int source,int dest){

    node*newnode1=CreateNode(dest);
    newnode1->next=g->adjacencyList[source];
    g->adjacencyList[source]=newnode1;

    node*newnode2=CreateNode(source);
    newnode2->next=g->adjacencyList[dest];
    g->adjacencyList[dest]=newnode2;

}

void printGraph(Graph*g){
    for(int i=0;i<g->numVertices;i++){
        node*temp=g->adjacencyList[i];
        while(temp){
            printf("%d ",temp->val);
            temp=temp->next;
        }
    }
}

int main(){
    int vertices;
    scanf("%d",&vertices);
    Graph*g=initialseGraph(vertices);

    char ch='i';
    int source;
    int dest;

    do{
        scanf(" %c",&ch);
        switch(ch){

            case 'i':
            scanf("%d",&source);
            scanf("%d",&dest);
            insert(g,source,dest);
            break;

            case 'p':printGraph(g);
            break;

        }
    }while(ch!='e');
    return 0;
}