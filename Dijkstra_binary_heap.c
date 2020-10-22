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
struct minheap
{
    int mindist;
    int vertex;
};
struct minheap* heap;
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
int build_minheap(int *dist,int *previous,int *map)
{
    cnt=1;
    heap[1].mindist=dist[source];
    heap[1].vertex=source;
    map[heap[1].vertex]=1;
    cnt++;
    for(int i=1;i<=nodes;i++)
    {
      if(i==source){previous[i]=1;continue;}
      else if(i!=source)previous[i]=-1;
      heap[cnt].mindist=dist[i];
      heap[cnt].vertex=i;
      map[heap[cnt].vertex]=cnt;
      cnt++;
    }
}
int delete_min(int map[])
{
      map[heap[heapsize].vertex]=map[heap[1].vertex];
      heap[1].mindist=heap[heapsize].mindist;
      heap[1].vertex=heap[heapsize].vertex;
      heapsize--;
      /*Compare the first node with it's child nodes*/
      cur=1;
      while(1)
      {
          c1=2*cur;  //left child
          c2=(2*cur)+1; //right child
          small=LLONG_MAX;

          if(c1<=heapsize && heap[c1].mindist<heap[cur].mindist)small=c1;
          if(c2<=heapsize && heap[c2].mindist<heap[cur].mindist)
          {
              if(small!=LLONG_MAX){if(heap[c2].mindist<heap[small].mindist)small=c2;}
              else if(small==LLONG_MAX)small=c2;
          }
          if(small==LLONG_MAX)break;

          swap(&map[heap[small].vertex],&map[heap[cur].vertex]);
          swap(&heap[small].mindist,&heap[cur].mindist);
          swap(&heap[small].vertex,&heap[cur].vertex);
          cur=small;
      }
}
int decrease_key(int map[])
{
     parent=update/2;

     while(heap[update].mindist<heap[parent].mindist && parent>=1 && update>=1)
     {
        swap(&map[heap[parent].vertex],&map[heap[update].vertex]);
        swap(&heap[update].mindist,&heap[parent].mindist);
        swap(&heap[update].vertex,&heap[parent].vertex);

        update=parent;
        parent=update/2;
     }
}
int dijkstra_minheap(int *map ,int *adjac,int* dist,int *previous)
{
    heapsize=cnt-1;
    while(heapsize>0)
    {
      pick=heap[1].vertex;
      delete_min(map);
      /*Deletion in Min. Heap*/

    //Relax the nodes adjacent to picked vertexk
      ptr=graph[pick];
      ok=0,adjacent,edge;
      stop=adjac[pick];
      while(stop>0 && dist[pick]!=LLONG_MAX)
      {
        adjacent=ptr->nodeindex;
        edge=ptr->weight;
        if(map[adjacent]<=heapsize && dist[pick]+edge<dist[adjacent] && dist[pick]!=LLONG_MAX && edge>=0)
        {
             dist[adjacent]=dist[pick]+edge;//relaxation of nodes adjacent to picked vertex
             previous[adjacent]=pick;
             update=map[adjacent];
             heap[update].mindist=dist[pick]+edge;
             decrease_key(map);
        }
        ptr=ptr->adj;
        stop--;
      }
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
    heap=(struct minheap*)malloc((nodes+1)*sizeof(struct minheap));

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
    for(int i=1;i<=nodes;i++){dist[i]=LLONG_MAX; visit[i]=0;}
    visit[source]=1;
    dist[source]=0;

    //Building Minimum Heap
    build_minheap(&dist,&previous,&map);
    //dijkstra
    dijkstra_minheap(&map,&adjac,&dist,&previous);
    //printing path from source to node to destination node 'n'
    print_path(&previous);

    free(graph);
    free(heap);
    free(traverse);
    free(ptr);
    return 0;
}
