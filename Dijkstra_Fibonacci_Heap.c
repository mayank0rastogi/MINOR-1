#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include<math.h>
#define int long long int


struct adjacencylist
{
   int nodeindex;
   int weight;
  struct adjacencylist* adj;
};

struct fibo
{
  struct fibo* left;
  struct fibo* right;
  struct fibo* child;
  struct fibo* parent;
  int index;
  int key;
  int mark;
  int degree;
};

struct fibo *ptr,*min=NULL,*traverse,*make_parent,*make_child,*swap,*chalo,*temp,*pntr,*map[100005];
struct fibo *found;

int n,maxrank;
int initialnodes;

int adjac[100005],previous[100005],dist[100005];


struct adjacencylist *graph[100002],*iterate;
int nodes,edges,distance,a,b,update,parent,pick,cur,ok=0,adjacent,edge,c1,c2,small,stop,source,heapsize;
int index,answer_exist,prev,cnt;
struct adjacencylist *pointer;


int swapp(int *a,int *b){ int temp=*a; *a=*b; *b=temp;}
int minimum(int a, int b){ if(a<=b)return a; else return b;}

int add_edge(int a,int b,int distance)
{
    iterate=(struct adjacencylist*)malloc(sizeof(struct adjacencylist));
    iterate->adj=graph[a];
    iterate->nodeindex=b;
    iterate->weight=distance;
    graph[a]=iterate;
}
int consolidate()
{
      maxrank=log(nodes)/log(2);
      struct fibo *arr[maxrank+1];
      for(int i=0;i<=maxrank;i++)arr[i]=NULL;
      int visit[initialnodes+1];
      for(int i=1;i<=initialnodes;i++)visit[i]=0;
      make_parent=min;
      struct fibo* stop=min;
      do
      {
        int deg=make_parent->degree;

        while(arr[deg]!=NULL && deg<=maxrank)
        {
            make_child=arr[deg];

          if(make_parent->key > arr[deg]->key)
          {
             swap=make_child;
             make_child=make_parent;
             make_parent=swap;
          }

          if(make_child==min){min=make_parent;}

          //make child

          (make_child->left)->right=make_child->right;
          (make_child->right)->left=make_child->left;

          if(make_parent->right==make_parent){min=make_parent;}

          make_child->right=make_child;
          make_child->left=make_child;
          make_child->parent=make_parent;

          if(make_parent->child==NULL)make_parent->child=make_child;

           make_child->left=(make_parent->child)->left;
           make_child->right=make_parent->child;

           (((make_parent->child)->left)->right)=make_child;
          (make_parent->child)->left=make_child;

          if(make_child->key < (make_parent->child)->key)make_parent->child=make_child;

          //after child has been made

          if(make_parent->right==make_parent){min=make_parent;}

           arr[deg]=NULL;
          (make_parent->degree)++;
          deg++;

        }
        arr[deg]=make_parent;
        visit[make_parent->index]++;
        make_parent=make_parent->right;

      }while(visit[make_parent->index]==0);

      //Finding Minimum element

     for(int i=0;i<=maxrank;i++)
     {
         if(arr[i]!=NULL)
         {
             if(min==NULL)min=arr[i];
             else
             {
                 if(arr[i]->key < min->key)min=arr[i];
             }
         }
     }



}

int extract_min()
{
     temp=min;

     if(temp->child!=NULL)
     {
        traverse=temp->child;
        do
        {
          pntr=traverse->right;
          (min->left)->right=traverse;
          traverse->left=min->left;
          traverse->right=min;
          min->left=traverse;
          if(traverse->key < min->key)min=traverse;
          traverse->parent=NULL;
          traverse=pntr;
        }while(pntr!=temp->child);
     }

     (temp->left)->right=temp->right;
     (temp->right)->left=temp->left;
      min=min->right;
      consolidate();
      n--;
      return min->key;
}

int build_fibonacciheap(int i,int disti)
{
       ptr=(struct fibo*)malloc(sizeof(struct fibo));

        ptr->parent=NULL;
        ptr->child=NULL;
        ptr->left=ptr;
        ptr->right=ptr;

        ptr->key=disti;
        ptr->index=i;
        ptr->mark=0;
        ptr->degree=0;
        map[i]=ptr;


        if(min==NULL)min=ptr;
        else
        {
            (min->left)->right = ptr;
            ptr->left=min->left;
            ptr->right=min;
            min->left=ptr;

            if(ptr->key < min->key)min=ptr;
        }
}
void cut(struct fibo* found,struct fibo* temp)
{
    if(found==found->right)temp->child=NULL;
    if(temp->child==found && temp->child!=NULL)
    {
      temp->child=found->right;
    }

   (found->left)->right=found->right;
   (found->right)->left=found->left;
   found->left=found;
   found->right=found;
  found->parent=NULL;

  (min->left)->right=found;
  found->right=min;
  found->left=min->left;
  min->left=found;

  found->mark=0;
  (temp->degree)--;
}
void cascade_cut(struct fibo* temp)
{
  traverse=temp->parent;
  if(traverse!=NULL)
  {
      if(traverse->mark==0)traverse->mark=1;
      else
      {
          cut(temp,traverse);
          cascade_cut(traverse);
      }
  }
}
void decrease_key(int index,int dec)
{
   found=map[index];
   temp=found->parent;

   found->key=dec;

   if(temp!=NULL && found->key<temp->key)
   {
       cut(found,temp);
       cascade_cut(temp);
   }

   if(found->key < min->key )min=found;
}
int dijkstra_fibonacciheap()
{
    heapsize=nodes;
    while(heapsize>0)
    {
      pick=min->index;
      /*Deletion in Min. Heap*/
      map[min->index]=NULL;
      extract_min();
      heapsize--;

    //Relax the nodes adjacent to picked vertexk
      pointer=graph[pick];
      ok=0,adjacent,edge;
      stop=adjac[pick];

      while(stop>0 && dist[pick]!=LLONG_MAX)
      {
        adjacent=pointer->nodeindex;
        edge=pointer->weight;

        if(dist[pick]+edge<dist[adjacent] && dist[pick]!=LLONG_MAX && edge>=0 && map[adjacent]!=NULL)
        {
             dist[adjacent]=dist[pick]+edge;//relaxation of nodes adjacent to picked vertex
             previous[adjacent]=pick;
             decrease_key(adjacent,dist[pick]+edge);
        }
        pointer=pointer->adj;
        stop--;
      }
    }
}

int print_path()
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
    for(int i=index;i>=1;i--)printf("%lld ",shortestpath[i]);
    printf("\n");
}

main()
{
    scanf("%lld%lld",&nodes,&edges); //nodes and edges
    initialnodes=nodes;
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
    int visit[nodes+1];
    for(int i=1;i<=nodes;i++){previous[i]=-1;dist[i]=LLONG_MAX; visit[i]=0;}
    visit[source]=1;
    dist[source]=0;

    //Building Minimum Heap
    for(int i=1;i<=nodes;i++)
    {

       build_fibonacciheap(i,dist[i]);
    }
    //dijkstra
    dijkstra_fibonacciheap();
    //printing path from source to node to destination node 'n'
    print_path();

    free(graph);
    free(traverse);
    free(ptr);
    return 0;
}
