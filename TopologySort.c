int checkForZero(int indegree[],int vertices){
    for(int i=0;i<vertices;i++){
        if(indegree[i]==0)return i;
    }
    return -1;
}

int checkForPositiveInteger(int indegree[],int vertices){
    for(int i=0;i<vertices;i++){
        if(indegree[i]>=1)return 1;
    }
    return -1;
}

int topologySort(int vertices,int A[][vertices],int indegree[]){

    int flag;
    int count;
    int index=-1;


    while(1){
        index=checkForZero(indegree,vertices);
        if((index>=0)){
            for(int i=0;i<vertices;i++){
                if(A[index][i])indegree[i]--;
            }
            indegree[index]=-1;
        }else {
            if(checkForPositiveInteger(indegree,vertices))return -1;
            else return 1;
        }
    }
}