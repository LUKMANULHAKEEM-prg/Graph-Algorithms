// initially the parent initialised as -1
// the colour array is the same as the visited array that we usually use in DFS. Instead of giving 1, we assign 1 or 2, which represent two different colour.

bool Bipartite(int vertices,int A[][vertices],int color[],int source,int parent){
    if(color[source]){
        if(color[source]==color[parent])return false;
        return true;
    }

    color[source]= (parent == -1 || color[parent]==1) ? 2 : 1;

    for(int i=0;i<vertices;i++){
        if(A[source][i] && parent!=i){
            if(!Bipartite(vertices,A,color,i,source))return false;
        }
    }

    return true;
}


// Code for Bipartite using adjacency List.

/*bool Bipartite(graph*g,int color[],int source,int parent){
    if(color[source]){
        if(color[source]==color[parent])return false;
        return true;
    }

    color[source] = (parent == -1 || color[parent]==1) ? 2 : 1;

    node*temp=g->List[source];
    while(temp){
        if(!Bipartite(g,color,temp->val,source))return false;
        temp=temp->next;
    }

    return true;

}*/
