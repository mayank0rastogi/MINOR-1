#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#define int long long int

struct adjacencylist
{
   int nodeindex;
   int weight;
  struct adjacencylist* adj;
};

struct adjacencylist *graph[100002],*traverse;
int nodes,edges,distance,a,b,update,parent,pick,cur,ok=0,adjacent,edge,c1,c2,small,stop,source,heapsize;
int index,answer_exist,prev,cnt;
struct adjacencylist *ptr;


int swap(int *a,int *b){ int temp=*a; *a=*b; *b=temp;}
int minimum(int a, int b){ if(a<=b)return a; else return b;}

int add_edge(int a,int b,int distance)
{
    traverse=(struct adjacencylist*)malloc(sizeof(struct adjacencylist));
    traverse->adj=graph[a];
    traverse->nodeindex=b;
    traverse->weight=distance;
    graph[a]=traverse;
}

int dijkstra_minheap(int *adjac,int* dist,int *previous,int* visit)
{
    int till=nodes;

    while(till>0)
    {
      int mini=1e18,pick,ok=0;
      for(int i=1;i<=nodes;i++)
      {
          if(mini>dist[i] && visit[i]==0)
          {
              mini=dist[i];
              pick=i;
              ok=1;
          }
      }
      if(ok==0)break;

    //Relax the nodes adjacent to picked vertexk
      visit[pick]=1;
      ptr=graph[pick];
      ok=0,adjacent,edge;
      stop=adjac[pick];
      while(stop>0 && dist[pick]!=LLONG_MAX)
      {
        adjacent=ptr->nodeindex;
        edge=ptr->weight;
        if(visit[adjacent]==0 && dist[pick]+edge<dist[adjacent] && dist[pick]!=LLONG_MAX && edge>=0)
        {
             dist[adjacent]=dist[pick]+edge;//relaxation of nodes adjacent to picked vertex
             previous[adjacent]=pick;
        }
        ptr=ptr->adj;
        stop--;
      }
      till--;
    }
}

int print_path(int *previous)
{
    int shortestpath[nodes+1];
    index=1,answer_exist=1,prev=nodes;
    shortestpath[index]=nodes;
    index++;
    while(1)
    {
      prev=previous[prev];
      if(prev==-1){answer_exist=0;break;}
      shortestpath[index]=prev;
      if(prev==1){break;}
      index++;
    }
    if(answer_exist==0){printf("-1\n");return 0;}
    for(int i=index;i>0;i--) printf("%lld ",shortestpath[i]);
    printf("\n");
}

int main()
{
    scanf("%lld%lld",&nodes,&edges); //nodes and edges
    int adjac[nodes+1],previous[nodes+1],map[nodes+1];;
    memset(adjac,0,sizeof(adjac));

    //graph input in linked list begins
    for(int i=0;i<edges;i++)
    {
     scanf("%lld%lld%lld",&a,&b,&distance);
     adjac[a]++;
     add_edge(a,b,distance);
     add_edge(b,a,distance);
     adjac[b]++;
    }
    //Djkstra algorithm
    source=1;
    int visit[nodes+1],dist[nodes+1];
    for(int i=1;i<=nodes;i++){dist[i]=LLONG_MAX; visit[i]=0;previous[i]=-1;}
    dist[source]=0;

    //dijkstra
    dijkstra_minheap(&adjac,&dist,&previous,&visit);
    //printing path from source to node to destination node 'n'
    print_path(&previous);
    return 0;
}
