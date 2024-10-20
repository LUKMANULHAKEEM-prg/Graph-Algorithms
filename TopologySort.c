int checkForZero(int indegree[], int vertices)
{
    for (int i = 0; i < vertices; i++)
    {
        if (indegree[i] == 0)
            return i;
    }
    return -1;
}

bool checkForPositiveInteger(int indegree[], int vertices)
{
    for (int i = 0; i < vertices; i++)
    {
        if (indegree[i] >= 1)
            return true;
    }
    return false;
}

bool topologySort(int vertices, int A[][vertices], int indegree[])
{

    int flag;
    int count;
    int index = -1;

    while (1)
    {

        index = checkForZero(indegree, vertices);

        if ((index >= 0))
        {
            for (int i = 0; i < vertices; i++)
            {
                if (A[index][i])
                    indegree[i]--;
            }
            printf("%d ", index);
            indegree[index] = -1;
        }
        else
        {
            if (checkForPositiveInteger(indegree, vertices))
            {
                printf("Cycle is Present\n");
                return false;
            }
            else
            {
                printf("\n");
                return true;
            }
        }
    }
}