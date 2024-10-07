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

int CheckForBipartite(Graph*g,int start,int color[],int currentColor){
    if(color[start]){
        if(color[start]!=currentColor)return 0;
        else return 1;
    }

    color[start]=currentColor;
    node*temp=g->adjacencyList[start];
    while(temp){
        int flag=0;
        if(currentColor==1){
            flag=CheckForBipartite(g,temp->val,color,2);
        }
        else{
            flag=CheckForBipartite(g,temp->val,color,1);
        }
        if(flag==0)return 0; 
        temp=temp->next;
    }
    return 1;
}

int main(){
    int vertices;
    scanf("%d",&vertices);
    Graph*g=initialseGraph(vertices);

    char ch='i';
    int source;
    int dest;
    int flag=1;
    int color[vertices];

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

            case 'b':

            for(int i=0;i<vertices;i++)color[i]=0;

            for(int i=0;i<vertices;i++){
                if(color[i]==0){
                    flag=CheckForBipartite(g,i,color,1);
                    if(!flag)break;
                }
            }

            if(flag)printf("bipartite\n");
            else printf("not bipartite\n");
            break;
        }
    }while(ch!='e');
    return 0;
}