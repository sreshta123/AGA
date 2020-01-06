#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<time.h>
struct node
{
	int data;
	struct node *next;
};
struct list
{
	struct node *head;
	struct node *end;
};
struct graph
{
	int v;
	struct list *array;
};
void greedy(struct graph *,int ,int *,int *,int ,int **,int *);
struct graph* initial(int n)
{
	struct graph* g=(struct graph *)malloc(sizeof(struct graph));
	g->v=n;
	g->array=(struct list *)malloc(n * sizeof(struct list));
	for(int i=0;i<n;i++)
	{
		g->array[i].head=NULL;
		g->array[i].end=NULL;
	}
	return g;
} 
struct node *create(int d)
{
	struct node *new=(struct node *)malloc(sizeof(struct node));
	new->data=d;
	new->next=NULL;
	return new;
}
struct graph * addedge(struct graph *g,int s,int d)
{
	struct node *temp=create(d);
	if(g->array[s].head==NULL)
	{
		g->array[s].head=temp;
		g->array[s].end=temp;
	}
	else
	{
		struct node *temp1 = g->array[s].end;
		temp1->next=temp;
		g->array[s].end=temp;
	} 
        printf("here is %d\n",g->array[s].head->data);
	struct node *temp2=create(s);
	if(g->array[d].head==NULL)
	{
		g->array[d].head=temp2;
		g->array[d].end=temp2;
	}
	else
	{
		struct node *temp3 = g->array[d].end;
		temp3->next=temp2;
		g->array[d].end=temp2;
	}
      return g;
}
//void greedy(struct graph *,int ,int *,int *,int,int **);

void printlist(struct graph *g,int n)
{
  for(int i=0;i<n;i++)
{		
 printf("adjacency list for %d is :",i);
struct node *t=g->array[i].head;

                while(t->next!=NULL)
                {
                    
                  printf("%d->",t->data);
                  t=t->next;
                 }
	printf("%d",t->data);
        printf("\n");          

}
}
void printmatrix(int n,int ** adj)
{
	for(int i=0;i<n;i++)
	{
            // printf("%d ----",i);
		for(int j=0;j<n;j++)
		{
                 	if(adj[i][j]!=1)
			{
				adj[i][j]=0;
			}
			printf("%d\t",adj[i][j]);
		}  
		printf("\n");
	}
}
int ** in(int n,int m)
{
	int **a=NULL;
	a=malloc(n*m*sizeof(int *));
	for(int i=0;i<n;i++)
	{
		a[i]=malloc(m*sizeof(int));
	}
	return a;
}


int main (int argc,char *argv[1])
{
  if (argc < 2)
	{
		printf("Missing Filename\n");
		return(1);
	}
	else
	{

	FILE *fp=fopen(argv[1],"r");       
	int n,m;
   	fscanf(fp,"%d",&n);
	fscanf(fp,"%d",&m);
	printf("nodes & edges in  given graph are %d %d \n",n,m);
	int **adj=NULL;
	struct graph *g=initial(n);
	adj=in(n,m);
	int degree[n],degree1[n];
	int visit[n];
	for(int i=0;i<n;i++)
	{
		degree[i]=0;
                degree1[i]=0;
                visit[i]=0;
			}
	for(int i=0;i<m;i++)
	{
		int s,d;
		fscanf(fp,"%d",&s);
		fscanf(fp,"%d",&d);
                printf("s and d are %d %d \n",s,d); 
		adj[s][d]=1;
		adj[d][s]=1;
		degree[s]+=1;
		degree[d]+=1;
                degree1[s]+=1;
                degree1[d]+=1;
		g=addedge(g,s,d);       


	}
for(int i=0;i<n;i++)
{
  printf("degree i %d\n",degree1[i]);}

	//printf("adjacency matrix is: \n");
	//printmatrix(n,adj);
         printlist(g,n);
         greedy(g,n,degree,visit,m,adj,degree1);
	
}
}
