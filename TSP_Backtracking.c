#include <stdio.h>
#define int long long int

int nodes,edges,distance,a,b,path_cost;
int graph[10][10];
int swap(int *a,int *b){ int temp=*a; *a=*b; *b=temp;}


void TSP_Backtracking(int* shortest,int start,int end,int* adjac,int* final_path)
{
   if (start == end)
   {
      int sum=0,find,node1,node2;
      node1=shortest[1];
      sum+=graph[1][node1];
      for(int i=1;i<nodes-1;i++)
      {
         node1=shortest[i];
         node2=shortest[i+1];
         sum+=graph[node1][node2];
      }
      node1=shortest[nodes-1];
      sum+=graph[node1][1];

      if(path_cost>sum)
      {
          path_cost=sum;
          for(int i=1;i<=nodes-1;i++)final_path[i]=shortest[i];
      }

   }
   else
   {
       for (int i=start;i<=end;i++)
       {
          swap(&shortest[start], &shortest[i]);
          TSP_Backtracking(shortest, start+1, end,adjac,final_path);
          swap(&shortest[start], &shortest[i]);
       }
   }
}

int print_path(int* final_path)
{

  printf("Cost of going through this path:%lld\n",path_cost);
 printf("1 ");
 for(int i=1;i<=nodes-1;i++)printf("%lld ",final_path[i]);
 printf("1\n");

}

int main()
{
    scanf("%lld%lld",&nodes,&edges); //nodes and edges
    int adjac[nodes+1],previous[nodes+1],map[nodes+1];;
    memset(adjac,0,sizeof(adjac));

    for(int i=0;i<=nodes;i++)
    {
        for(int j=0;j<=nodes;j++)
        {
            graph[i][j]=-1;
        }
    }

    //graph input in linked list begins
    for(int i=0;i<edges;i++)
    {
     scanf("%lld%lld%lld",&a,&b,&distance);
     adjac[a]++;
     adjac[b]++;
     if(graph[a][b]>distance)
     {
        graph[a][b]=distance;
        graph[b][a]=distance;
     }
     else
     {
     graph[a][b]=distance;
     graph[b][a]=distance;
     }
    }
    int shortest[nodes+1];
    for(int i=2;i<=nodes;i++)shortest[i-1]=i;
    path_cost=1e18;
    int final_path[nodes+2];
    TSP_Backtracking(&shortest,1,nodes-1,&adjac,&final_path);
    print_path(&final_path);

    return 0;
}
